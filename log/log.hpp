
#include <iostream>

#define LOG_RST "\x1B[0m"
#define LOG_KRED "\x1B[31m"
#define LOG_KGRN "\x1B[32m"
#define LOG_KBLU "\x1B[34m"

class Log {

      private:
	bool _debug{false};

	template <typename _FIRST, typename... _REST>
	void _print(const _FIRST &f, const _REST &...r) {
		std::cout << f;
		_print(r...);
	}

	void _print() { std::cout << std::endl; }

      public:
	void enable_debug(bool d = true) { _debug = d; }

	template <typename... _T> void debug(const _T &...r) {
		if (!_debug)
			return;
		_print(LOG_KBLU, "..DEBUG: ", r..., LOG_RST);
	}
	template <typename... _T> void error(const _T &...r) {
		_print(LOG_KRED, "**ERROR: ", r..., LOG_RST);
	}
	template <typename... _T> void info(const _T &...r) {
		_print(LOG_KGRN, "++INFO : ", r..., LOG_RST);
	}
};

extern Log LOG;
