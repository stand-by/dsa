#include <boost/test/unit_test.hpp>
#include <data_structures/set.hpp>
#include <iostream>

using namespace dsa;

BOOST_AUTO_TEST_SUITE(test_set)

BOOST_AUTO_TEST_CASE(use_case)
{
    structs::set<int> empty_s;
    BOOST_CHECK(empty_s.empty());
    BOOST_CHECK(empty_s.size() == 0);
    empty_s.clear();
    BOOST_CHECK(empty_s.size() == 0);
    BOOST_CHECK(!empty_s.contains(1));
    BOOST_CHECK(!empty_s.contains(0));
    
    std::deque<int> deq = {10,7,8,3,5,1};
    structs::set<int> s{deq.begin(), deq.end()};
    
    BOOST_CHECK(!s.empty());
    BOOST_CHECK(s.size() == 6);
    BOOST_CHECK(s.max() == 10);
    BOOST_CHECK(s.min() == 1);
    
    BOOST_CHECK(s.contains(1));
    BOOST_CHECK(s.contains(3));
    BOOST_CHECK(s.contains(5));
    BOOST_CHECK(s.contains(7));
    BOOST_CHECK(s.contains(8));
    BOOST_CHECK(s.contains(10));
    
    s.insert(9);
    BOOST_CHECK(s.contains(9));
    BOOST_CHECK(s.size() == 7);
    s.remove(3);
    BOOST_CHECK(!s.contains(3));
    s.insert(3);
    BOOST_CHECK(s.contains(3));
    
    s.remove(3);
    s.remove(1);
    BOOST_CHECK(!s.contains(1));
    BOOST_CHECK(s.max() == 10);
    BOOST_CHECK(s.min() == 5);
    BOOST_CHECK(s.size() == 5);
    
    s.insert(0);
    s.insert(100);
    s.insert(101);
    s.insert(50);
    s.remove(100);
    s.insert(66);
    s.insert(77);
    s.remove(9);
    s.insert(55);
    s.remove(0);
    
    BOOST_CHECK(s.contains(5));
    BOOST_CHECK(s.contains(7));
    BOOST_CHECK(s.contains(8));
    BOOST_CHECK(s.contains(10));
    BOOST_CHECK(s.contains(101));
    BOOST_CHECK(s.contains(50));
    BOOST_CHECK(s.contains(66));
    BOOST_CHECK(s.contains(77));
    BOOST_CHECK(s.contains(55));
    BOOST_CHECK(s.max() == 101);
    BOOST_CHECK(s.min() == 5);
    BOOST_CHECK(s.size() == 9);
    
    s.clear();
    BOOST_CHECK(s.empty());
    BOOST_CHECK(s.size() == 0);
    BOOST_CHECK(!s.contains(0));
    
    s.insert(42);
    s.insert(21);
    BOOST_CHECK(s.contains(21));
    BOOST_CHECK(s.contains(42));
    BOOST_CHECK(s.size() == 2);
}

BOOST_AUTO_TEST_SUITE_END()
