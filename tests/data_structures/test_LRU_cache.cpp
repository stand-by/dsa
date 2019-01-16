#include <boost/test/unit_test.hpp>
#include <data_structures/LRU_cache.hpp>
#include <iostream>
#include <unordered_map>

using namespace dsa;

BOOST_AUTO_TEST_SUITE(test_LRU_cache)

BOOST_AUTO_TEST_CASE(use_case)
{
    structs::LRU_cache<std::unordered_map, int, std::string> cache{5};
    
    BOOST_CHECK(cache.size() == 0);
    BOOST_CHECK(cache.max_size() == 5);
    BOOST_CHECK(cache.contains(1) == false);
    
    cache.put(4, "four");
    BOOST_CHECK(cache.size() == 1);
    cache.put(1, "one");
    BOOST_CHECK(cache.size() == 2);
    cache.put(3, "three");
    BOOST_CHECK(cache.size() == 3);
    cache.put(2, "two");
    BOOST_CHECK(cache.size() == 4);
    cache.put(5, "five");
    BOOST_CHECK(cache.size() == 5);
    BOOST_CHECK(cache.size() == cache.max_size());
    
    BOOST_CHECK(cache.contains(0) == false);
    BOOST_CHECK(cache.contains(1) == true);
    BOOST_CHECK(cache.contains(2) == true);
    BOOST_CHECK(cache.contains(3) == true);
    BOOST_CHECK(cache.contains(4) == true);
    BOOST_CHECK(cache.contains(5) == true);
    BOOST_CHECK(cache.contains(6) == false);
    
    BOOST_CHECK(cache.get(4) == "four");
    BOOST_CHECK(cache.size() == 5);
    
    cache.put(0, "zero");
    BOOST_CHECK(cache.size() == 5);
    BOOST_CHECK(cache.contains(1) == false);
    
    BOOST_CHECK(cache.get(2) == "two");
    BOOST_CHECK(cache.size() == 5);

    cache.put(10, "ten");
    cache.put(11, "eleven");
    BOOST_CHECK(cache.size() == 5);
    
    BOOST_CHECK(cache.contains(4) == true);
    BOOST_CHECK(cache.contains(0) == true);
    BOOST_CHECK(cache.contains(2) == true);
    BOOST_CHECK(cache.contains(10) == true);
    BOOST_CHECK(cache.contains(11) == true);
    BOOST_CHECK(cache.contains(1) == false);
    BOOST_CHECK(cache.contains(5) == false);
    BOOST_CHECK(cache.contains(3) == false);
    BOOST_CHECK(cache.contains(6) == false);
    
    BOOST_CHECK(cache.get(2) == "two");
    BOOST_CHECK(cache.get(4) == "four");
    BOOST_CHECK(cache.get(0) == "zero");
    BOOST_CHECK(cache.get(10) == "ten");
    BOOST_CHECK(cache.get(11) == "eleven");
    BOOST_CHECK(cache.size() == 5);
}

BOOST_AUTO_TEST_SUITE_END()
