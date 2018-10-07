#include <boost/test/unit_test.hpp>
#include <data_structures/heap.hpp>
#include <iostream>
#include <random>

using namespace dsa;

BOOST_AUTO_TEST_SUITE(test_heap)

BOOST_AUTO_TEST_CASE(use_case)
{
    std::vector<int> v = {2,8,4,0,10,12};

    structs::max_heap<int> max_h;
    structs::min_heap<int> min_h{v.begin(), v.end()};
    structs::min_heap<int> min_h_copy(min_h);

    BOOST_CHECK(!min_h.empty());
    BOOST_CHECK(max_h.empty());
    BOOST_CHECK(min_h.size() == 6);
    BOOST_CHECK(min_h == min_h_copy);

    BOOST_CHECK(min_h_copy.top() == 0);
    min_h_copy.top() = 1;
    BOOST_CHECK(min_h_copy.top() == 1);
    BOOST_CHECK(min_h != min_h_copy);

    BOOST_CHECK(min_h.top() == 0);
    min_h.add(-1);
    BOOST_CHECK(min_h.top() == -1);
    BOOST_CHECK(min_h.size() == 7);
    min_h.add(14);
    BOOST_CHECK(min_h.top() == -1);
    BOOST_CHECK(min_h.size() == 8);
    min_h.add(10);
    BOOST_CHECK(min_h.top() == -1);
    BOOST_CHECK(min_h.size() == 9);

    BOOST_CHECK(min_h.pop_top() == -1);
    BOOST_CHECK(min_h.pop_top() == 0);
    BOOST_CHECK(min_h.pop_top() == 2);
    BOOST_CHECK(min_h.pop_top() == 4);
    BOOST_CHECK(min_h.pop_top() == 8);
    BOOST_CHECK(min_h.pop_top() == 10);
    BOOST_CHECK(min_h.pop_top() == 10);
    BOOST_CHECK(min_h.pop_top() == 12);
    BOOST_CHECK(min_h.pop_top() == 14);
    BOOST_CHECK(min_h.empty());

    v.resize(1000);
    std::iota(v.begin(),v.end(), 1);
    std::shuffle(v.begin(), v.end(), std::default_random_engine{});

    for(int e: v)
        max_h.add(e);
    BOOST_CHECK(max_h.size() == 1000);

    int prev_max = max_h.pop_top();
    BOOST_CHECK(prev_max == *std::max_element(v.begin(), v.end()));

    while(!max_h.empty())
    {
        int curr_max = max_h.pop_top();
        BOOST_CHECK(curr_max < prev_max);
        prev_max = curr_max;
    }
    BOOST_CHECK(prev_max == *std::min_element(v.begin(), v.end()));
}

BOOST_AUTO_TEST_SUITE_END()
