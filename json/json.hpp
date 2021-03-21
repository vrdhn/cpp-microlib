
#include <cassert>
#include <cctype>
#include <charconv>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

/*
 * Schema based json parsing is simpler than using a library (-:
 */

//   this code handle utf8 by not handling it ..
//   but it hides that impl ...
class json {

	class stream {
	      private:
		const char *str;
		int next{0};
		bool errored{false};
		const char *error_message{""};

	      public:
		stream(const char *s) : str{s} {}

		bool error(const char *msg) {
			errored = true;
			error_message = msg;
			return false;
		}

		bool array_begin() { return is_char('['); }
		bool array_finish() { return is_char(']'); }
		bool map_begin() { return is_char('{'); }
		bool map_finish() { return is_char('}'); }
		bool is_comma() { return is_char(','); }
		bool is_colon() { return is_char(':'); }
		bool is_char(char ch) {
			if (!skip_ws())
				return false;
			if (ch == str[next]) {
				next++;
				return true;
			}
			return false;
		}

		bool skip_ws() {
			if (errored || str[next] == 0)
				return false;
			while (str[next] != 0) {
				if (!std::isspace(str[next]))
					return true;
				next++;
			}
			return false;
		}
		bool get_digit(int &ch) {
			if (errored || str[next] == 0)
				return false;
			if (std::isdigit(str[next])) {
				ch = str[next];
				next++;
				return true;
			}
			return false;
		}
		bool get_char(int &ch) {
			if (errored || str[next] == 0)
				return false;
			ch = str[next];
			next++;
			return true;
		}
	};

      public:
	template <const char *_name, typename T> class field {
		T _value;

	      public:
		const char *name() { return _name; }

		T &value() { return _value; }
	};

	template <typename T> static bool parse(const char *str, T &out) {
		stream s(str);
		return _parse(s, out);
	}

      private:
	// stream() should provide a better api so that  std::from_chars can
	// be used
	static bool _parse(stream &s, int &out) {
		s.skip_ws();
		out = 0;
		int len = 0;
		int ch;
		bool neg = s.is_char('-');
		if (neg)
			s.skip_ws();
		while (s.get_digit(ch)) {
			out = out * 10 + ch - '0';
			len++;
		}
		if (len == 0) {
			return s.error("Expecting integer");
		}
		if (neg)
			out = -out;
		return true;
	}

	// stream() should provide a better api so that  std::from_chars can
	// be used
	static bool _parse(stream &s, double &out) {
		s.skip_ws();
		out = 0;
		int len = 0;
		int ch;
		bool neg = s.is_char('-');
		if (neg)
			s.skip_ws();
		while (s.get_digit(ch)) {
			out = out * 10 + ch - '0';
			len++;
		}
		if (len == 0) {
			return s.error("Expecting float");
		}
		double postdecimal = 10;
		if (s.is_char('.')) {
			while (s.get_digit(ch)) {
				out += (ch - '0') / postdecimal;
				postdecimal *= 10;
			}
		}

		if (neg)
			out = -out;
		return true;
	}

	static bool _parse(stream &s, std::string &out) {
		s.skip_ws();
		if (!s.is_char('"'))
			return s.error("Expecting string");
		out.clear();
		int ch;
		while (s.get_char(ch)) {
			if (ch == '"')
				return true;
			out.push_back(ch);
		}
		return s.error("String not terminated");
	}

	template <typename E>
	static bool _parse(stream &s, std::vector<E> &out) {
		out.clear();
		if (!s.array_begin())
			return false;
		// check empty array first ...
		if (s.array_finish())
			return true;
		do {
			E ele;
			if (!_parse(s, ele))
				return false;
			out.push_back(ele);
		} while (s.is_comma());

		if (s.array_finish())
			return true;

		return false;
	}

	template <typename... F>
	static bool _parse(stream &s, std::tuple<F...> &out) {
		if (!s.map_begin())
			return false;
		// check empty map first ...
		if (s.map_finish())
			return true;

		do {
			std::string key;
			if (!_parse(s, key))
				return false;
			if (!s.is_colon())
				return false;
			if (!_parse<std::tuple_size<std::tuple<F...>>::value -
					1,
				    F...>(s, key, out))
				return false;
		} while (s.is_comma());

		if (s.map_finish())
			return true;

		return false;
	}

	template <int idx, typename... F>
	static bool _parse(stream &s, std::string &key, std::tuple<F...> &out) {
		if (std::get<idx>(out).name() == key) {
			return _parse(s, std::get<idx>(out).value());
		}
		if constexpr (idx == 0)
			return false;
		else
			return _parse<idx - 1, F...>(s, key, out);
	}
};
