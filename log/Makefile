
HEADER = log.hpp
TESTER = log.cpp



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


