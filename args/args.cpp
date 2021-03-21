
#include <cassert>
#include <string>
#include <vector>

#include "args.hpp"

int main() {

	{
		static char verbose[] = "verbose";

		const char *arg[] = {"exe", "--verbose", "10", nullptr};

		std::tuple<args::opt<verbose, int>> opts;

		args::parse(3, arg, opts);

		assert(std::get<0>(opts).value() == 10);
	}
}
