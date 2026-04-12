#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include <format>
#include <stdexcept>

#define assert(statement, msg) test::assert_impl(__FILE__, __LINE__, statement, msg);
#define assert_eq(x, y, msg) test::assert_impl(__FILE__, __LINE__, statement);

namespace test
{
	void report(const std::string& msg)
	{
		std::cout << msg << std::endl;
	}

	void assert_impl(std::string file, int line, bool statement, std::string msg)
	{
        if (!statement)
            report(file + ", line " + std::to_string(line) + ": " + msg);
	}

	template<typename X, typename Y>
	void assert_eq_impl(std::string file, int line, X x, Y y)
	{
		if (x != y)
			report(file + ", line " + std::to_string(line) + ": " + std::format("Equality assertion failed ({} != {})", x, y));
	}
}

#endif