#include <boost/test/unit_test.hpp>
#include <algorithms/search.hpp>
#include <iostream>

using namespace dsa;

BOOST_AUTO_TEST_SUITE(test_search)

BOOST_AUTO_TEST_CASE(linear_search)
{
    std::vector<int> v = {1,2,3,3,4,5};
    std::list<char> l = {'a', 'b', 'c'};
    
    BOOST_CHECK(algos::linear_search(v.begin(),v.end(),-1) == v.end());
    BOOST_CHECK(algos::linear_search(v.begin(),v.end(),6) == v.end());

    auto it_v = algos::linear_search(v.cbegin(),v.cend(),3);
    BOOST_CHECK(*it_v == 3);
    BOOST_CHECK(*(++it_v) == 3);

    it_v = algos::linear_search(v.begin(),v.end(),1);
    BOOST_CHECK(it_v == v.begin());
    BOOST_CHECK(*it_v == 1);
    it_v = algos::linear_search(v.begin(),v.end(),5);
    BOOST_CHECK(it_v == v.end()-1);
    BOOST_CHECK(*it_v == 5);
    
    auto it_c = algos::linear_search(l.begin(),l.end(),'a');
    BOOST_CHECK(it_c == l.begin());
    BOOST_CHECK(*it_c == 'a');
    it_c = algos::linear_search(l.begin(),l.end(),'b');
    BOOST_CHECK(it_c == ++l.begin());
    BOOST_CHECK(*it_c == 'b');
    it_c = algos::linear_search(l.begin(),l.end(),'c');
    BOOST_CHECK(it_c == ++++l.begin());
    BOOST_CHECK(*it_c == 'c');

    BOOST_CHECK(algos::linear_search(l.begin(),l.end(),'d') == l.end());
    BOOST_CHECK(algos::linear_search(l.begin(),l.end(),'e') == l.end());
}

BOOST_AUTO_TEST_CASE(binary_search)
{
    std::vector<int> i = {3};

    BOOST_CHECK(*algos::binary_search(i.begin(), i.end(),3) == 3);
    BOOST_CHECK(algos::binary_search(i.begin(), i.end(),3) == i.begin());
    BOOST_CHECK(algos::binary_search(i.begin(), i.end(),1) == i.end());

    std::vector<int> v = {1,2,3,3,4,5};

    BOOST_CHECK(algos::binary_search(v.begin(),v.end(),-1) == v.end());
    BOOST_CHECK(algos::binary_search(v.begin(),v.end(),6) == v.end());

    auto it_v = algos::binary_search(v.cbegin(),v.cend(),3);
    BOOST_CHECK(*it_v == 3);
    BOOST_CHECK(*(++it_v) == 4);

    it_v = algos::binary_search(v.begin(),v.end(),1);
    BOOST_CHECK(it_v == v.begin());
    BOOST_CHECK(*it_v == 1);
    it_v = algos::binary_search(v.begin(),v.end(),5);
    BOOST_CHECK(it_v == v.end()-1);
    BOOST_CHECK(*it_v == 5);
    it_v = algos::binary_search(v.begin(),v.end(),2);
    BOOST_CHECK(it_v == v.begin()+1);
    BOOST_CHECK(*it_v == 2);
    it_v = algos::binary_search(v.begin(),v.end(),4);
    BOOST_CHECK(it_v == v.end()-2);
    BOOST_CHECK(*it_v == 4);

    std::deque<long> d = {10,20,30,40,50};

    BOOST_CHECK(algos::binary_search(d.begin(),d.end(),1) == d.end());
    BOOST_CHECK(algos::binary_search(d.begin(),d.end(),100) == d.end());
    BOOST_CHECK(algos::binary_search(d.begin(),d.begin()+2,30) == d.begin()+2);
    BOOST_CHECK(algos::binary_search(d.begin(),d.begin()+2,40) == d.begin()+2);
    BOOST_CHECK(*algos::binary_search(d.begin(),d.begin()+2,30) == 30);
    BOOST_CHECK(algos::binary_search(d.begin(),d.begin()+2,20) == d.begin()+1);
    BOOST_CHECK(algos::binary_search(d.begin(),d.begin()+2,10) == d.begin());
    
    auto it_d = algos::binary_search(d.begin(),d.end(),30);
    BOOST_CHECK(it_d == d.begin()+2);
    BOOST_CHECK(*it_d == 30);
    it_d = algos::binary_search(d.begin(),d.end(),20);
    BOOST_CHECK(it_d == d.begin()+1);
    BOOST_CHECK(*it_d == 20);
    it_d = algos::binary_search(d.begin(),d.end(),10);
    BOOST_CHECK(it_d == d.begin());
    BOOST_CHECK(*it_d == 10);
    it_d = algos::binary_search(d.begin(),d.end(),40);
    BOOST_CHECK(it_d == d.end()-2);
    BOOST_CHECK(*it_d == 40);
    it_d = algos::binary_search(d.begin(),d.end(),50);
    BOOST_CHECK(it_d == d.end()-1);
    BOOST_CHECK(it_d == d.begin()+4);
    BOOST_CHECK(*it_d == 50);
}

BOOST_AUTO_TEST_SUITE_END()
