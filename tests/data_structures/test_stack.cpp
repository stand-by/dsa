#include <boost/test/unit_test.hpp>
#include <data_structures/stack.hpp>
#include <iostream>

using namespace dsa;

BOOST_AUTO_TEST_SUITE(test_stack)

BOOST_AUTO_TEST_CASE(use_case)
{
	structs::stack<int> s;

	BOOST_CHECK(s.size() == 0);
	BOOST_CHECK(s.empty());

	s.push(5);
	BOOST_CHECK(s.size() == 1);
	BOOST_CHECK(s.peek() == 5);
	s.push(4);
	BOOST_CHECK(s.peek() == 4);
	s.push(3);
	BOOST_CHECK(s.peek() == 3);
	BOOST_CHECK(s.size() == 3);

	BOOST_CHECK(s.pop() == 3);
	BOOST_CHECK(s.peek() == 4);
	BOOST_CHECK(s.pop() == 4);
	BOOST_CHECK(s.peek() == 5);
	BOOST_CHECK(s.size() == 1);

	BOOST_CHECK(!s.empty());
	s.erase();
	BOOST_CHECK(s.empty());
}

BOOST_AUTO_TEST_SUITE_END()
