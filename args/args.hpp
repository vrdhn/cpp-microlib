#include "tuple"
#include "vector"

class args {
      public:
	template <const char *_name, typename T> class opt {
		T _value;

	      public:
		const char *name() { return _name; }

		T &value() { return _value; }
	};

	template <typename... F>
	static bool parse(int argc, char const *const *argv,
			  std::tuple<F...> &out) {
		std::vector<const char *> args =
		    std::vector(argv + 1, argv + argc);
		return parse<0, F...>(args, out);
	}
	//
	static int _find(std::vector<const char *> args, int i,
			 const char *key) {
		std::string k = "--";
		k += key;
		while (i < int(args.size())) {
			if (k == args[i])
				return i;
		}
		return -1;
	}

	static int _store(std::vector<const char *> args, int i, int &v) {
		v = std::atoi(args[i + 1]);
		return 2;
	}

	template <int idx, typename... F>
	static bool parse(std::vector<const char *> args,
			  std::tuple<F...> &out) {
		int i = _find(args, 0, std::get<idx>(out).name());
		while (i >= 0) {
			int todel = _store(args, i, std::get<idx>(out).value());
			args.erase(args.begin() + i, args.begin() + i + todel);
			i = _find(args, i + 1, std::get<idx>(out).name());
		}
		if constexpr (idx <
			      std::tuple_size<std::tuple<F...>>::value - 1)
			return parse<idx + 1, F...>(args, out);
		else
			return true;
	}
};
