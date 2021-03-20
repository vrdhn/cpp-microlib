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


