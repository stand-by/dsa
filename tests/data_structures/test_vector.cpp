#include <boost/test/unit_test.hpp>
#include <data_structures/vector.hpp>
#include <iostream>

using namespace dsa;

BOOST_AUTO_TEST_SUITE( test_vector )

BOOST_AUTO_TEST_CASE( use_case )
{
    structs::vector<int> vec_empty;
    structs::vector<int> vec_def(5);
    structs::vector<int> vec = {1,2,3};
    structs::vector<int> vec_copy(vec);

    BOOST_CHECK(vec_empty.empty());
    BOOST_CHECK(vec_copy == vec);

    for(auto& e: vec_def)
        BOOST_CHECK(e == 0);
    BOOST_CHECK(vec[0] == 1);
    BOOST_CHECK(vec[1] == 2);
    BOOST_CHECK(vec[2] == 3);
    BOOST_CHECK(vec_copy[0] == 1);
    BOOST_CHECK(vec_copy[1] == 2);
    BOOST_CHECK(vec_copy[2] == 3);

    BOOST_CHECK(vec_empty.size() == 0);
    BOOST_CHECK(vec_empty.get_capacity() == 0);
    BOOST_CHECK(vec_def.size() == 5);
    BOOST_CHECK(vec_copy.size() == 3);
    BOOST_CHECK(vec.get_capacity() == 3);

    vec.reserve(5);
    vec_empty.reserve(5);
    BOOST_CHECK(vec.get_capacity() == 5);
    BOOST_CHECK(vec.size() == 3);
    BOOST_CHECK(vec_empty.get_capacity() == 5);
    BOOST_CHECK(vec_empty.size() == 0);

    vec.shrink();
    BOOST_CHECK(vec.get_capacity() == 3);
    BOOST_CHECK(vec.size() == 3);
    BOOST_CHECK(vec[0] == 1);
    BOOST_CHECK(vec[1] == 2);
    BOOST_CHECK(vec[2] == 3);

    BOOST_CHECK(vec.data() == &vec[0]);
    BOOST_CHECK(vec.front() == 1);
    BOOST_CHECK(vec.back() == 3);

    vec_empty = vec_def;
    for(auto& e: vec_empty)
        BOOST_CHECK(e == 0);
    BOOST_CHECK(vec_empty.size() == 5);
    BOOST_CHECK(vec_empty == vec_def);
    BOOST_CHECK(vec_empty != vec);
    BOOST_CHECK(!vec_empty.empty());

    BOOST_CHECK(vec.contains(1));
    BOOST_CHECK(vec.contains(2));
    BOOST_CHECK(vec.contains(3));
    BOOST_CHECK(!vec.contains(5));
    BOOST_CHECK(vec_def.contains(0));
    BOOST_CHECK(!vec_def.contains(1));

    BOOST_CHECK(vec.count(5) == 0);
    BOOST_CHECK(vec.count(2) == 1);
    BOOST_CHECK(vec_def.count(0) == 5);

    BOOST_CHECK(vec.find_index_of(1,1) == -1);
    BOOST_CHECK(vec.find_index_of(1) == 0);
    BOOST_CHECK(vec.find_index_of(3,1) == 2);
    BOOST_CHECK(vec.find_index_of(2) == 1);
    BOOST_CHECK(vec_def.find_index_of(2) == -1);
    BOOST_CHECK(vec_def.find_index_of(0) == 0);
    BOOST_CHECK(vec_def.find_index_of(0,2) == 2);

    vec_empty = vec;
    vec_empty.reverse();
    BOOST_CHECK(vec_empty[0] == 3);
    BOOST_CHECK(vec_empty[1] == 2);
    BOOST_CHECK(vec_empty[2] == 1);
    vec_empty.sort();
    BOOST_CHECK(vec_empty[0] == 1);
    BOOST_CHECK(vec_empty[1] == 2);
    BOOST_CHECK(vec_empty[2] == 3);

    vec_empty.erase();    
    BOOST_CHECK(vec_empty.size() == 0);

    vec_copy.remove_by_index(0);
    BOOST_CHECK(vec_copy.size() == 2);
    BOOST_CHECK(vec_copy[0] == 2);
    BOOST_CHECK(vec_copy[1] == 3);

    vec_copy.remove_by_index(1);
    BOOST_CHECK(vec_copy.size() == 1);
    BOOST_CHECK(vec_copy[0] == 2);

    vec_copy.push_back(5);
    BOOST_CHECK(vec_copy.size() == 2);
    BOOST_CHECK(vec_copy[0] == 2);
    BOOST_CHECK(vec_copy[1] == 5);
    vec_copy.push_back(5);
    BOOST_CHECK(vec_copy.size() == 3);
    BOOST_CHECK(vec_copy[0] == 2);
    BOOST_CHECK(vec_copy[1] == 5);
    BOOST_CHECK(vec_copy[2] == 5);

    vec_empty.push_back(1);
    BOOST_CHECK(vec_empty[0] == 1);
    BOOST_CHECK(vec_empty.size() == 1);
    BOOST_CHECK(vec_empty.get_capacity() > vec_empty.size());

    BOOST_CHECK(vec_copy.pop_back() == 5);
    BOOST_CHECK(vec_copy.size() == 2);
    BOOST_CHECK(vec_copy.pop_front() == 2);
    BOOST_CHECK(vec_copy.size() == 1);
    
    // 1 2 3
    vec.insert(0,0); // 0 1 2 3
    vec.insert(2,10); // 0 1 10 2 3
    vec.insert(3,0); // 0 1 10 0 2 3
    BOOST_CHECK(vec[0] == 0);
    BOOST_CHECK(vec[1] == 1);
    BOOST_CHECK(vec[2] == 10);
    BOOST_CHECK(vec[3] == 0);
    BOOST_CHECK(vec[4] == 2);
    BOOST_CHECK(vec[5] == 3);
}

BOOST_AUTO_TEST_SUITE_END()
