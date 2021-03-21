
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Test {};

class TestSuite {

#define TEST_RST "\x1B[0m"
#define TEST_KRED "\x1B[31m"
#define TEST_KGRN "\x1B[32m"
#define TEST_KBLU "\x1B[34m"

      private:
	typedef bool (*func_t)(std::ostream &log);

      public:
	static int success;
	static int failure;

      private:
	static void tell(std::string name, bool pass, std::stringstream &log) {
		if (pass) {
			success++;
			std::cout << TEST_KGRN << ".. PASS " << name << TEST_RST
				  << std::endl;
		} else {
			std::cout << TEST_KRED << "** FAIL " << name
				  << TEST_KBLU << std::endl
				  << "--" << std::endl
				  << log.str() << std::endl
				  << "--" << TEST_RST << std::endl;
			failure++;
		}
	}

      public:
	static Test pass(std::string name, func_t fn) {
		std::stringstream ostr;
		tell(name, fn(ostr), ostr);
		return {};
	}

	static Test fail(std::string name, func_t fn) {
		std::stringstream ostr;
		tell(name, !fn(ostr), ostr);
		return {};
	}

	static int report() {
		if (success + failure == 0) {
			std::cout << TEST_KRED
				  << "** Test case malfunction, no tests found"
				  << TEST_RST << std::endl;
			return 1;
		}

		std::cout << (failure ? TEST_KRED : TEST_KGRN) << "Total "
			  << success + failure << ",  PASS: " << success
			  << ", FAIL: " << failure << TEST_RST << std::endl;
		return failure;
	}
};

extern TestSuite TESTSUITE;

// What is c++ without some macro abuse.
#define TEST_PASS(x) static Test x = TESTSUITE.pass(#x,[](std::ostream &log)
#define TEST_FAIL(x) static Test x = TESTSUITE.fail(#x,[](std::ostream &log)
#define TEST_END     )
