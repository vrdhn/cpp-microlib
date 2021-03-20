
#include "test.hpp"

TestSuite TESTSUITE;

int TestSuite::success = 0;
int TestSuite::failure = 0;

int main(int,	 // argc
	 char ** // argv
) {
	// all tests have alrady run , just report them.
	return TESTSUITE.report();
}

TEST_PASS(hello_pass) {
	log << "Running test_pass " << std::endl;
	return true;
}
TEST_END;

TEST_FAIL(hello_fail) {
	log << "Running test_fail " << std::endl;
	return false;
}
TEST_END;
