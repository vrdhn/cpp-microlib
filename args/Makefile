
HEADER = args.hpp
TESTER = args.cpp

export CXX = g++  -g --std=c++17 -Wall -Wpedantic -Wextra  -Wfatal-errors -Werror
#CXX = clang++  -g --std=c++17 -Wall -Wpedantic -Wextra  -Wfatal-errors -Werror 
export FMT = @clang-format -i  --style="{BasedOnStyle: llvm, IndentWidth: 8, UseTab: Always}"

default: _clean _fmt _test _clean

.PHONY: _clean
_clean:
	@rm -f test.exe *~


.PHONY: _test
_test: test.exe
	@./test.exe

.PHONY: _fmt
_fmt:
	$(FMT) $(HEADER) $(TESTER)

test.exe:  $(TESTER) $(HEADER) 
	@$(CXX) -o $@  $(TESTER)


