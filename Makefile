

MOD=test json log

export CXX = g++  -g --std=c++17 -Wall -Wpedantic -Wextra  -Wfatal-errors -Werror
#CXX = clang++  -g --std=c++17 -Wall -Wpedantic -Wextra  -Wfatal-errors -Werror 
export FMT = @clang-format -i  --style="{BasedOnStyle: llvm, IndentWidth: 8, UseTab: Always}"


default: _clean _fmt _test _clean

.PHONY: _clean
_clean:
	$(foreach v, $(MOD),	$(MAKE) -C $v _clean &&) true

.PHONY: _fmt
_fmt:
	$(foreach v, $(MOD),	$(MAKE) -C $v _fmt &&) true

.PHONY: _test
_test: 
	$(foreach v, $(MOD),	$(MAKE) -C $v _test &&) true

