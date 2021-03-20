
#include <iostream>

class Log {

      private:
	bool _debug{false};

      public:
	void enable_debug(bool d = true) { _debug = d; }

	template <typename _FIRST, typename... _REST>
	void debug(const _FIRST &f, const _REST &...r) {
		if (!_debug)
			return;
		std::cout << f;
		debug(r...);
	}

	void debug() { std::cout << std::endl; }

	template <typename _FIRST, typename... _REST>
	void info(const _FIRST &f, const _REST &...r) {
		std::cout << f;
		debug(r...);
	}

	void info() { std::cout << std::endl; }
};

extern Log LOG;
