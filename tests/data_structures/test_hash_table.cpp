#include <boost/test/unit_test.hpp>
#include <data_structures/hash_table.hpp>
#include <iostream>

using namespace dsa;

template<typename H>
void validate_int_to_string_mapping(H hash_func)
{
    auto map = structs::make_hash_table<int, std::string>(5, std::move(hash_func));
    
    BOOST_CHECK(map.empty());
    BOOST_CHECK(map.slots() == 5);
    BOOST_CHECK(map.size() == 0);
    BOOST_CHECK(map.load_factor() == 0);
    
    BOOST_CHECK(!map.has_key(42));
    map.add(11, "one");
    map.add(5, "zero");
    map.add(52, "two");
    BOOST_CHECK(!map.empty());
    BOOST_CHECK(map.size() == 3);
    map.add(23, "three");
    map.add(64, "four");
    BOOST_CHECK(map.slots() == map.size());
    BOOST_CHECK(map.size() == 5);
    BOOST_CHECK(map.load_factor() == 1.0);
    
    BOOST_CHECK(!map.has_key(42));
    BOOST_CHECK(!map.has_key(0));
    BOOST_CHECK(!map.has_key(1));
    BOOST_CHECK(!map.has_key(2));
    BOOST_CHECK(!map.has_key(3));
    BOOST_CHECK(!map.has_key(4));
    BOOST_CHECK(!map.has_key(10));
    BOOST_CHECK(!map.has_key(65));
    
    BOOST_CHECK(map.has_key(5));
    BOOST_CHECK(map.has_key(11));
    BOOST_CHECK(map.has_key(23));
    BOOST_CHECK(map.has_key(52));
    BOOST_CHECK(map.has_key(64));
    
    BOOST_CHECK(map.at(5) == "zero");
    BOOST_CHECK(map.at(11) == "one");
    BOOST_CHECK(map.at(23) == "three");
    BOOST_CHECK(map.at(23) != "tree");
    BOOST_CHECK(map.at(52) == "two");
    BOOST_CHECK(map.at(52) != "to");
    BOOST_CHECK(map.at(64) == "four");
    BOOST_CHECK(map.at(64) != "zero");
    
    map.update(52, "to");
    map.update(23, "tree");
    BOOST_CHECK(map.at(11) == "one");
    BOOST_CHECK(map.at(23) != "three");
    BOOST_CHECK(map.at(23) == "tree");
    BOOST_CHECK(map.at(52) != "two");
    BOOST_CHECK(map.at(52) == "to");
    BOOST_CHECK(map.at(64) == "four");
    
    map.update(101, "one-o-one");
    BOOST_CHECK(map.size() == 6);
    BOOST_CHECK(map.load_factor() == 6.0/5.0);
    BOOST_CHECK(map.has_key(101));
    BOOST_CHECK(map.has_key(5));
    BOOST_CHECK(map.has_key(11));
    BOOST_CHECK(map.at(11) == "one");
    BOOST_CHECK(map.at(5) == "zero");
    BOOST_CHECK(map.at(101) == "one-o-one");
    
    map[203] = "two-o-three";
    BOOST_CHECK(map.size() == 7);
    BOOST_CHECK(map.load_factor() == 7.0/5.0);
    BOOST_CHECK(map.has_key(203));
    map[52] = "two";
    map[23] = "three";
    
    BOOST_CHECK(map.at(5) == "zero");
    BOOST_CHECK(map.at(11) == "one");
    BOOST_CHECK(map.at(23) == "three");
    BOOST_CHECK(map.at(52) == "two");
    BOOST_CHECK(map.at(64) == "four");
    BOOST_CHECK(map.at(203) == "two-o-three");
    BOOST_CHECK(map.at(101) == "one-o-one");
    
    BOOST_CHECK(map.slots() == 5);
    map.remove(52);
    BOOST_CHECK(map.size() == 6);
    map.remove(203);
    BOOST_CHECK(map.size() == 5);
    BOOST_CHECK(map.slots() == 5);
    BOOST_CHECK(!map.has_key(52));
    BOOST_CHECK(!map.has_key(203));
    
    BOOST_CHECK(map.at(5) == "zero");
    BOOST_CHECK(map.at(11) == "one");
    BOOST_CHECK(map.at(23) == "three");
    BOOST_CHECK(map.at(64) == "four");
    BOOST_CHECK(map.at(101) == "one-o-one");
    BOOST_CHECK(map.load_factor() == 1.0);
    
    map.resize(2);
    BOOST_CHECK(!map.empty());
    BOOST_CHECK(map.size() == 5);
    BOOST_CHECK(map.slots() == 2);
    BOOST_CHECK(map.load_factor() == 5.0/2.0);
    BOOST_CHECK(!map.has_key(52));
    BOOST_CHECK(!map.has_key(203));
    BOOST_CHECK(!map.has_key(1));
    BOOST_CHECK(map.has_key(5));
    BOOST_CHECK(map.has_key(11));
    BOOST_CHECK(map.has_key(23));
    BOOST_CHECK(map.has_key(64));
    BOOST_CHECK(map.has_key(101));
    BOOST_CHECK(map.at(5) == "zero");
    BOOST_CHECK(map.at(11) == "one");
    BOOST_CHECK(map.at(23) == "three");
    BOOST_CHECK(map.at(64) == "four");
    BOOST_CHECK(map.at(101) == "one-o-one");
    
    map.clear();
    BOOST_CHECK(map.slots() == 0);
    BOOST_CHECK(map.size() == 0);
    BOOST_CHECK(map.empty());
}

BOOST_AUTO_TEST_SUITE(test_hash_table)

BOOST_AUTO_TEST_CASE(test_modulo_hash)
{
    validate_int_to_string_mapping(
        [](auto key, config::size_type size) { return key % size; }
    );
}

BOOST_AUTO_TEST_CASE(test_convolution_hash)
{
    validate_int_to_string_mapping(
        [](auto key, config::size_type size)
        {
            decltype(key) sum = 0;
            while(key != 0)
            {
                sum += key % 10;
                key /= 10;
            }
            return sum % size;
        }
    );
}

BOOST_AUTO_TEST_CASE(test_string_hash)
{
    auto string_hash = [](auto key, config::size_type size)
    {
        config::index_type sum = 0;
        for(int i = 0; i < key.size(); ++i)
            sum += i * static_cast<config::index_type>(key[i]);
        return sum % size;
        
    };
    auto map = structs::make_hash_table<std::string, int>(6, std::move(string_hash));
    
    map["one"] = 1;
    map["ten"] = 10;
    map["hundred"] = 100;
    
    BOOST_CHECK(map.size() == 3);
    BOOST_CHECK(map.slots() == 6);
    
    BOOST_CHECK(map.has_key("one"));
    BOOST_CHECK(map.has_key("ten"));
    BOOST_CHECK(map.has_key("hundred"));
    BOOST_CHECK(!map.has_key("thousand"));
    BOOST_CHECK(map.at("one") == 1);
    BOOST_CHECK(map.at("ten") == 10);
    BOOST_CHECK(map.at("hundred") == 100);
    BOOST_CHECK(map["one"] == 1);
    BOOST_CHECK(map["ten"] == 10);
    BOOST_CHECK(map["hundred"] == 100);
    
    map["thousand"];
    BOOST_CHECK(map.has_key("thousand"));
    BOOST_CHECK(map.at("thousand") == 0);
    map.update("thousand", 1000);
    BOOST_CHECK(map.at("thousand") == 1000);
    
    map.add("two", 2);
    map.remove("thousand");
    BOOST_CHECK(map.size() == 4);
    
    map.update("three", 3);
    map["five"] = 5;
    map["six"] = 6;
    BOOST_CHECK(map.size() == 7);
    BOOST_CHECK(map.slots() == 6);
    
    BOOST_CHECK(map.at("one") == 1);
    BOOST_CHECK(map.at("ten") == 10);
    BOOST_CHECK(map.at("hundred") == 100);
    BOOST_CHECK(!map.has_key("thousand"));
    BOOST_CHECK(map.at("two") == 2);
    BOOST_CHECK(map.at("three") == 3);
    BOOST_CHECK(map.at("five") == 5);
    BOOST_CHECK(map.at("six") == 6);
    
    map["101"] = 101;
    map["100"] = 100;
    
    BOOST_CHECK(map.size() == 9);
    BOOST_CHECK(map["101"] == 101);
    BOOST_CHECK(map["100"] == 100);
    BOOST_CHECK(map.at("two") == 2);
    BOOST_CHECK(map.at("ten") == 10);
    BOOST_CHECK(map.at("hundred") == 100);
    
    map.resize(2);
    BOOST_CHECK(map.slots() == 2);
    BOOST_CHECK(map.size() == 9);
    BOOST_CHECK(map.at("one") == 1);
    BOOST_CHECK(map.at("ten") == 10);
    BOOST_CHECK(map.at("hundred") == 100);
    BOOST_CHECK(map.at("two") == 2);
    BOOST_CHECK(map.at("three") == 3);
    BOOST_CHECK(map.at("five") == 5);
    BOOST_CHECK(map.at("six") == 6);
    BOOST_CHECK(map.at("100") == 100);
    BOOST_CHECK(map.at("101") == 101);
}

BOOST_AUTO_TEST_SUITE_END()
