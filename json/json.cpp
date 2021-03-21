
#include "json.hpp"

bool floateq(double a, double b) {
	if (a == b)
		return true;

	if (a == 0 && b != 0)
		return false;

	auto abs = [](double x) { return x < 0 ? -x : x; };
	return abs((a - b) / a) < 0.01;
}

int main() {
	{
		int j;
		bool ret = json::parse("1", j);
		assert(ret);
		assert(j == 1);
	}
	{
		int j;
		bool ret = json::parse(" -100 ", j);
		assert(ret);
		assert(j == -100);
		json::parse(" - 100 ", j);
		assert(j == -100);
	}
	{
		double f;
		bool ret = json::parse(" 10 ", f);
		assert(ret);
		assert(floateq(f, 10.0)); // TODO: delta comparision
	}
	{
		double f;
		bool ret = json::parse(" 10.010203 ", f);
		assert(ret);
		assert(floateq(f, 10.010203)); // TODO: delta comparision
	}
	{
		std::string str;
		bool ret = json::parse(" \"Hello World\" ", str);
		assert(ret);
		assert(str == "Hello World");
	}
	{
		std::vector<int> vec_int;
		bool ret = json::parse(" [ ] ", vec_int);
		assert(ret);
		assert(vec_int.size() == 0);
	}
	{
		std::vector<int> vec_int;
		bool ret = json::parse(" [ 1,-1, 2,-2] ", vec_int);
		assert(ret);
		assert(vec_int.size() == 4);
		assert(vec_int[0] == 1);
		assert(vec_int[1] == -1);
		assert(vec_int[2] == 2);
		assert(vec_int[3] == -2);
	}
	{
		static char id[] = "id";

		std::tuple<json::field<id, std::string>> val;

		bool ret = json::parse("{ \"id\" : \"abcd\" }", val);
		assert(ret);
		assert(std::get<0>(val).value() == "abcd");
	}

	{
		static char id[] = "id";
		static char name[] = "name";
		std::vector<std::tuple<json::field<id, int>,
				       json::field<name, std::string>>>
		    val;

		bool ret =
		    json::parse("[ { \"id\" : 10, \"name\" : \"abcd\" }, { "
				"\"id\" : 20, \"name\" : \"lmno\" } ] ",
				val);
		assert(ret);
		assert(val.size() == 2);
		assert(std::get<0>(val[0]).value() == 10);
		assert(std::get<1>(val[0]).value() == "abcd");
		assert(std::get<0>(val[1]).value() == 20);
		assert(std::get<1>(val[1]).value() == "lmno");
	}

	std::cout << "All good." << std::endl;
}
