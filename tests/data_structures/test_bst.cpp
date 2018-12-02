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
    
    BOOST_CHECK(!bst_empty.contain(10));
    BOOST_CHECK(bst.contain(10));
    BOOST_CHECK(!bst.contain(11));
    
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
    
    BOOST_CHECK(bst.contain(2));
    BOOST_CHECK(bst.contain(4));
    BOOST_CHECK(bst.contain(7));
    BOOST_CHECK(bst.contain(10));
    BOOST_CHECK(bst.contain(15));
    BOOST_CHECK(bst.contain(20));
    BOOST_CHECK(bst.contain(13));
    BOOST_CHECK(bst.contain(14));
    BOOST_CHECK(!bst.contain(1));
    BOOST_CHECK(!bst.contain(0));
    BOOST_CHECK(!bst.contain(21));

    BOOST_CHECK(bst != bst_copy);
    bst_copy = bst;
    BOOST_CHECK(bst == bst_copy);
    BOOST_CHECK(bst.height() == bst_copy.height());
    BOOST_CHECK(bst.size() == bst_copy.size());
    
    bst_copy.remove(2);
    BOOST_CHECK(!bst_copy.contain(2));
    bst_copy.remove(4);
    BOOST_CHECK(!bst_copy.contain(4));
    BOOST_CHECK(bst_copy.contain(3));
    
    bst_copy.remove(15);
    BOOST_CHECK(!bst_copy.contain(15));
    BOOST_CHECK(bst_copy.contain(20));
    BOOST_CHECK(bst_copy.contain(14));

    bst_copy.remove(10);
    BOOST_CHECK(!bst_copy.contain(10));
    
    BOOST_CHECK(bst_copy.contain(20));
    BOOST_CHECK(bst_copy.contain(14));
    BOOST_CHECK(bst_copy.contain(13));
    BOOST_CHECK(bst_copy.contain(11));
    BOOST_CHECK(bst_copy.contain(5));
    BOOST_CHECK(bst_copy.contain(7));
    BOOST_CHECK(bst_copy.contain(3));
    BOOST_CHECK(!bst_copy.contain(1));
    BOOST_CHECK(!bst_copy.contain(0));
    BOOST_CHECK(!bst_copy.contain(21));
    
    BOOST_CHECK(!bst_copy.empty());
    BOOST_CHECK(bst_copy.max() == 20);
    BOOST_CHECK(bst_copy.min() == 3);
    BOOST_CHECK(bst_copy.height() == 4);
    BOOST_CHECK(bst_copy.size() == 7);
    
    BOOST_CHECK(bst_empty.empty());
    bst_empty.add(42);
    BOOST_CHECK(bst_empty.height() == 1);
    BOOST_CHECK(bst_empty.size() == 1);
    BOOST_CHECK(bst_empty.contain(42));
    BOOST_CHECK(!bst_empty.contain(1));
    bst_empty.remove(42);
    BOOST_CHECK(bst_empty.empty());
}

BOOST_AUTO_TEST_SUITE_END()
