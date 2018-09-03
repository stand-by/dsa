#include <boost/test/unit_test.hpp>
#include <data_structures/queue.hpp>
#include <iostream>

using namespace dsa;

BOOST_AUTO_TEST_SUITE(test_queue)

BOOST_AUTO_TEST_CASE(use_case)
{
    structs::queue<int> q;

    BOOST_CHECK(q.size() == 0);
    BOOST_CHECK(q.empty());

    q.enqueue(5);
    BOOST_CHECK(q.size() == 1);
    BOOST_CHECK(q.front() == 5);
    BOOST_CHECK(q.back() == 5);
    q.enqueue(4);
    BOOST_CHECK(q.front() == 5);
    BOOST_CHECK(q.back() == 4);
    q.enqueue(3);
    BOOST_CHECK(q.front() == 5);
    BOOST_CHECK(q.back() == 3);
    BOOST_CHECK(q.size() == 3);

    BOOST_CHECK(q.dequeue() == 5);
    BOOST_CHECK(q.front() == 4);
    BOOST_CHECK(q.back() == 3);
    BOOST_CHECK(q.dequeue() == 4);
    BOOST_CHECK(q.front() == 3);
    BOOST_CHECK(q.back() == 3);
    BOOST_CHECK(q.size() == 1);

    BOOST_CHECK(!q.empty());
    q.erase();
    BOOST_CHECK(q.empty());
}

BOOST_AUTO_TEST_SUITE_END()
