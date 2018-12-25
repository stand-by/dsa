#include <boost/test/unit_test.hpp>
#include <data_structures/binary_search_tree.hpp>
#include <iostream>

using namespace dsa;

BOOST_AUTO_TEST_SUITE(test_bst)

BOOST_AUTO_TEST_CASE(use_case)
{
    structs::binary_search_tree<int, std::less<int>> bst(10);
    structs::binary_search_tree<int, std::less<int>> bst_empty;
    structs::binary_search_tree<int, std::less<int>> bst_copy;

    BOOST_CHECK(bst_empty == bst_copy);
    BOOST_CHECK(bst_empty != bst);
    
    BOOST_CHECK(!bst.empty());
    BOOST_CHECK(bst_empty.empty());
    
    BOOST_CHECK(bst.max() == 10);
    BOOST_CHECK(bst.min() == 10);
    
    BOOST_CHECK(!bst_empty.contains(10));
    BOOST_CHECK(bst.contains(10));
    BOOST_CHECK(!bst.contains(11));
    
    BOOST_CHECK(bst.height() == 1);
    BOOST_CHECK(bst_empty.height() == 0);

    BOOST_CHECK(bst.size() == 1);
    BOOST_CHECK(bst_empty.size() == 0);

    bst.add(15).add(20).add(13).add(11).add(14);
    bst.add(5).add(4).add(7).add(3);
    
    BOOST_CHECK(bst.height() == 4);
    BOOST_CHECK(bst.size() == 10);
    BOOST_CHECK(bst.min() == 3);
    bst.add(2);
    BOOST_CHECK(bst.height() == 5);
    BOOST_CHECK(bst.size() == 11);
    
    BOOST_CHECK(!bst.empty());
    BOOST_CHECK(bst.max() == 20);
    BOOST_CHECK(bst.min() == 2);
    
    BOOST_CHECK(bst.contains(2));
    BOOST_CHECK(bst.contains(4));
    BOOST_CHECK(bst.contains(7));
    BOOST_CHECK(bst.contains(10));
    BOOST_CHECK(bst.contains(15));
    BOOST_CHECK(bst.contains(20));
    BOOST_CHECK(bst.contains(13));
    BOOST_CHECK(bst.contains(14));
    BOOST_CHECK(!bst.contains(1));
    BOOST_CHECK(!bst.contains(0));
    BOOST_CHECK(!bst.contains(21));

    BOOST_CHECK(bst != bst_copy);
    bst_copy = bst;
    BOOST_CHECK(bst == bst_copy);
    BOOST_CHECK(bst.height() == bst_copy.height());
    BOOST_CHECK(bst.size() == bst_copy.size());
    
    bst_copy.remove(2);
    BOOST_CHECK(!bst_copy.contains(2));
    bst_copy.remove(4);
    BOOST_CHECK(!bst_copy.contains(4));
    BOOST_CHECK(bst_copy.contains(3));
    
    bst_copy.remove(15);
    BOOST_CHECK(!bst_copy.contains(15));
    BOOST_CHECK(bst_copy.contains(20));
    BOOST_CHECK(bst_copy.contains(14));

    bst_copy.remove(10);
    BOOST_CHECK(!bst_copy.contains(10));
    
    BOOST_CHECK(bst_copy.contains(20));
    BOOST_CHECK(bst_copy.contains(14));
    BOOST_CHECK(bst_copy.contains(13));
    BOOST_CHECK(bst_copy.contains(11));
    BOOST_CHECK(bst_copy.contains(5));
    BOOST_CHECK(bst_copy.contains(7));
    BOOST_CHECK(bst_copy.contains(3));
    BOOST_CHECK(!bst_copy.contains(1));
    BOOST_CHECK(!bst_copy.contains(0));
    BOOST_CHECK(!bst_copy.contains(21));
    
    BOOST_CHECK(!bst_copy.empty());
    BOOST_CHECK(bst_copy.max() == 20);
    BOOST_CHECK(bst_copy.min() == 3);
    BOOST_CHECK(bst_copy.height() == 4);
    BOOST_CHECK(bst_copy.size() == 7);
    
    BOOST_CHECK(bst_empty.empty());
    bst_empty.add(42);
    BOOST_CHECK(bst_empty.height() == 1);
    BOOST_CHECK(bst_empty.size() == 1);
    BOOST_CHECK(bst_empty.contains(42));
    BOOST_CHECK(!bst_empty.contains(1));
    bst_empty.remove(42);
    BOOST_CHECK(bst_empty.empty());
}

BOOST_AUTO_TEST_SUITE_END()
