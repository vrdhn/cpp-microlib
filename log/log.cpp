#include "log.hpp"

Log LOG;

int main() {

	int j = 10;
	const char *str = "hi";

	LOG.debug("by default, debug is off ", j, str);
	LOG.info("but info is never off");
	LOG.enable_debug();
	LOG.debug("now this goes to screen", "var is ", j, " and ", str);
}
