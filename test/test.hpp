
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Test {};

class TestSuite {

#define RST "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KBLU "\x1B[34m"

      private:
	typedef bool (*func_t)(std::ostream &log);

      public:
	static int success;
	static int failure;

      private:
	static void tell(std::string name, bool pass, std::stringstream &log) {
		if (pass) {
			success++;
			std::cout << KGRN << ".. PASS " << name << RST
				  << std::endl;
		} else {
			std::cout << KRED << "** FAIL " << name << KBLU
				  << std::endl
				  << "--" << std::endl
				  << log.str() << std::endl
				  << "--" << RST << std::endl;
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
			std::cout << KRED
				  << "** Test case malfunction, no tests found"
				  << RST << std::endl;
			return 1;
		}

		std::cout << (failure ? KRED : KGRN) << "Total "
			  << success + failure << ",  PASS: " << success
			  << ", FAIL: " << failure << RST << std::endl;
		return failure;
	}
};

extern TestSuite TESTSUITE;

// What is c++ without some macro abuse.
#define TEST_PASS(x) static Test x = TESTSUITE.pass(#x,[](std::ostream &log)
#define TEST_FAIL(x) static Test x = TESTSUITE.fail(#x,[](std::ostream &log)
#define TEST_END     )
