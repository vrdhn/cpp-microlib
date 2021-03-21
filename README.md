cpp-microlib
============

small single header C++17 utilities.

json
----
Reads json with strict schema to a data structure.

```
static char id[] = "id";
static char name[] = "name";
std::vector<std::tuple<json::field<id, int>, json::field<name, std::string>>> val;

bool ret = json::parse("[ { \"id\" : 10, \"name\" : \"abcd\" }, { "
				"\"id\" : 20, \"name\" : \"lmno\" } ] ",
				val);

```

test
----
A very simple unit testing. Runs tests before `main()`.
Has a little abuse of macros for ease of use.

```
TESTSUITE.run("some_name", [](std::ostream &log) {
	// do something blah blah
	log << "I'm doing this ";
	return true;
});


TEST( some_name) {
	// do something blah blah
	log << "I'm doing this ";
	return true;
}
TEST_END;
```

log
---
Simply log to stdout.
```
int j = 10;
LOG.debug("value is ", j, " grams");
```

args
----
Simple argument parser.
```
static char verbose[] = "verbose";
static char rest[] = "";
std::tuple<args::arg<verbose, bool>, args::arg<rest,std::vector<std::string>>> opts;
bool ret = args::parse(argc, argv, opts);
```


sim
---
Simple discreet event simulation engine.
Uses virtual functions , templates are too clumsy for this.
