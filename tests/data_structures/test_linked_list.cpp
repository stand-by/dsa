#include <boost/test/unit_test.hpp>
#include <data_structures/linked_list.hpp>
#include <iostream>

using namespace dsa;

BOOST_AUTO_TEST_SUITE( test_linked_list )

BOOST_AUTO_TEST_CASE( use_case )
{
    structs::linked_list<int> li_empty;
    structs::linked_list<int> li_def(1,3);
    structs::linked_list<int> li = {1,2,3,4,5};
    structs::linked_list<int> li_copy(li);

    BOOST_CHECK(li_empty.empty());
    BOOST_CHECK(!li_def.empty());

    BOOST_CHECK(li_empty.size() == 0);
    BOOST_CHECK(li_def.size() == 3);
    BOOST_CHECK(li.size() == 5);

    BOOST_CHECK(li_def == li_def);
    BOOST_CHECK(li == li_copy);
    BOOST_CHECK(li_def != li);

    li_empty = li_def;
    BOOST_CHECK(!li_empty.empty());
    BOOST_CHECK(li_empty == li_def);
    BOOST_CHECK(li_empty != li);

    li_empty.erase();
    BOOST_CHECK(li_empty.empty());
    BOOST_CHECK(li_empty.head() == nullptr);

    BOOST_CHECK(li_def.front() == 1);
    BOOST_CHECK(li_def.back() == 1);
    BOOST_CHECK(li.front() == 1);
    BOOST_CHECK(li.back() == 5);

    BOOST_CHECK(li_empty.count(0) == 0);
    BOOST_CHECK(li_def.count(-1) == 0);
    BOOST_CHECK(li_def.count(1) == 3);
    BOOST_CHECK(li.count(1) == 1);
    BOOST_CHECK(li.count(3) == 1);
    BOOST_CHECK(li.count(5) == 1);
    BOOST_CHECK(li.count(6) == 0);

    BOOST_CHECK(!li_empty.contains(0));
    BOOST_CHECK(!li_def.contains(-1));
    BOOST_CHECK(li_def.contains(1));
    BOOST_CHECK(li.contains(1));
    BOOST_CHECK(li.contains(3));
    BOOST_CHECK(li.contains(5));
    BOOST_CHECK(!li.contains(6));

    BOOST_CHECK(li_empty.find_index_of(0) == -1);
    BOOST_CHECK(li_def.find_index_of(-1) == -1);
    BOOST_CHECK(li_def.find_index_of(1) == 0);
    BOOST_CHECK(li.find_index_of(1) == 0);
    BOOST_CHECK(li.find_index_of(3) == 2);
    BOOST_CHECK(li.find_index_of(5) == 4);
    BOOST_CHECK(li.find_index_of(6) == -1);

    li_empty.reverse();
    li_copy.reverse();
    BOOST_CHECK(li_copy.find_index_of(1) == 4);
    BOOST_CHECK(li_copy.find_index_of(3) == 2);
    BOOST_CHECK(li_copy.find_index_of(5) == 0);
    BOOST_CHECK(li_copy.find_index_of(6) == -1);

    li.insert(0,-1); // -1 1 2 3 4 5
    li.insert(3,10); // -1 1 2 10 3 4 5
    li.insert(6,42); // -1 1 2 10 3 4 42 5
    BOOST_CHECK(li.find_index_of(-1) == 0);
    BOOST_CHECK(li.find_index_of(1) == 1);
    BOOST_CHECK(li.find_index_of(2) == 2);
    BOOST_CHECK(li.find_index_of(10) == 3);
    BOOST_CHECK(li.find_index_of(3) == 4);
    BOOST_CHECK(li.find_index_of(4) == 5);
    BOOST_CHECK(li.find_index_of(42) == 6);
    BOOST_CHECK(li.find_index_of(5) == 7);

    BOOST_CHECK(li_copy.pop_front() == 5);
    BOOST_CHECK(li_copy.pop_back() == 1);
    BOOST_CHECK(li_copy.pop_front() == 4);
    BOOST_CHECK(li_copy.size() == 2);
    BOOST_CHECK(li_copy.contains(3));
    BOOST_CHECK(li_copy.contains(2));
    BOOST_CHECK(!li_copy.contains(4));
    BOOST_CHECK(!li_copy.contains(5));

    li_empty.push_back(2);
    li_empty.push_front(1);
    li_empty.push_front(0);
    li_empty.push_back(3);
    BOOST_CHECK(li_empty.size() == 4);
    BOOST_CHECK(li_empty.find_index_of(0) == 0);
    BOOST_CHECK(li_empty.find_index_of(1) == 1);
    BOOST_CHECK(li_empty.find_index_of(2) == 2);
    BOOST_CHECK(li_empty.find_index_of(3) == 3);
    BOOST_CHECK(li_empty.find_index_of(4) == -1);

    li_def.push_back(5);
    li_def.push_back(10);
    BOOST_CHECK(li_def.count(1) == 3);
    BOOST_CHECK(li_def.count(5) == 1);
    BOOST_CHECK(li_def.count(10) == 1);
    BOOST_CHECK(li_def.pop_by_index(4) == 10);
    BOOST_CHECK(li_def.pop_by_index(2) == 1);
    BOOST_CHECK(li_copy.pop_by_index(1) == 2);
    BOOST_CHECK(li_copy.pop_by_index(0) == 3);
    BOOST_CHECK(li_copy.empty());
}

BOOST_AUTO_TEST_SUITE_END()
