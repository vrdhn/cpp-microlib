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

