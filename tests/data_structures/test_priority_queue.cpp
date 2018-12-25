#include <boost/test/unit_test.hpp>
#include <data_structures/priority_queue.hpp>
#include <iostream>

using namespace dsa;

BOOST_AUTO_TEST_SUITE(test_priority_queue)

BOOST_AUTO_TEST_CASE(use_case)
{
    std::list<int> list = {30,50,10,20,40};
    structs::priority_queue<int> pq(list.begin(), list.end());
    structs::priority_queue<int> pq_copy;
    
    BOOST_CHECK(!pq.empty());
    BOOST_CHECK(pq_copy.empty());
    BOOST_CHECK(pq.size() == 5);
    
    BOOST_CHECK(pq.top() == 50);
    BOOST_CHECK(pq.pop() == 50);
    BOOST_CHECK(pq.size() == 4);
    BOOST_CHECK(pq.top() == 40);
    BOOST_CHECK(pq.pop() == 40);
    BOOST_CHECK(pq.size() == 3);
    
    pq.push(100);
    pq.push(1);
    pq.push(10);
    BOOST_CHECK(pq.size() == 6);
    
    BOOST_CHECK(pq.pop() == 100);
    BOOST_CHECK(pq.pop() == 30);
    BOOST_CHECK(pq.pop() == 20);
    BOOST_CHECK(pq.pop() == 10);
    BOOST_CHECK(pq.pop() == 10);
    BOOST_CHECK(pq.pop() == 1);
    BOOST_CHECK(pq.empty());
    
    pq.push(100);
    pq.push(200);
    pq.push(150);
    
    pq_copy.push(5);
    BOOST_CHECK(pq_copy.top() == 5);
    pq_copy.push(10);
    BOOST_CHECK(pq_copy.top() == 10);
    BOOST_CHECK(pq_copy.size() == 2);
    
    pq_copy = pq;
    BOOST_CHECK(pq.size() == pq_copy.size());
    BOOST_CHECK(pq_copy.top() == pq.top());
    BOOST_CHECK(pq_copy.top() == 200);
    BOOST_CHECK(pq_copy.pop() == 200);
    BOOST_CHECK(pq_copy.pop() == 150);
    BOOST_CHECK(pq_copy.pop() == 100);
    BOOST_CHECK(pq_copy.empty());
}

BOOST_AUTO_TEST_SUITE_END()
