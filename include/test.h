#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include <format>
#include <stdexcept>

#define assert(statement, msg) test::assert_impl(__FILE__, __LINE__, statement, msg);

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
}

#endif