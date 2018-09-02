#include <boost/test/unit_test.hpp>
#include <data_structures/array.hpp>
#include <iostream>

using namespace dsa;

BOOST_AUTO_TEST_SUITE(test_array)

BOOST_AUTO_TEST_CASE(use_case)
{
    structs::array<int, 3> arr;
    structs::array<int, 3> arr3 = {1,2,3};
    structs::array<int, 3> arr33(arr3);

    BOOST_CHECK(arr33 == arr3);

    for(auto& e: arr)
    	BOOST_CHECK(e == 0);
    BOOST_CHECK(arr3[0] == 1);
    BOOST_CHECK(arr3[1] == 2);
    BOOST_CHECK(arr3[2] == 3);
    BOOST_CHECK(arr33[0] == 1);
    BOOST_CHECK(arr33[1] == 2);
    BOOST_CHECK(arr33[2] == 3);

    arr33 = arr;
    for(auto& e: arr33)
    	BOOST_CHECK(e == 0);
    BOOST_CHECK(arr33 != arr3);
    BOOST_CHECK(arr33 == arr);
		
    BOOST_CHECK(arr33.data() != arr.data());
    BOOST_CHECK(arr33.data() != arr3.data());
    BOOST_CHECK(arr3.data() == &arr3[0]);

    BOOST_CHECK(arr3.front() == 1);
    BOOST_CHECK(arr3.back() == 3);

    BOOST_CHECK(arr3.size() == 3);
    structs::array<int, 1> t;
    BOOST_CHECK(arr3.size() != t.size());

    arr33.fill(42);
    for(auto& e: arr33)
    	BOOST_CHECK(e == 42);
}

BOOST_AUTO_TEST_SUITE_END()
