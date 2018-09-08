#include <boost/test/unit_test.hpp>
#include <algorithms/sort.hpp>
#include <iostream>
#include <random>

using namespace dsa;

BOOST_AUTO_TEST_SUITE(test_sort)

BOOST_AUTO_TEST_CASE(bubble_sort)
{
    std::vector<int> v = {5,4,4,3,2,1};
    BOOST_CHECK(!std::is_sorted(v.begin(), v.end()));
    algos::bubble_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));
    algos::bubble_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));

    std::list<int> l = {4,3,2,1};
    BOOST_CHECK(!std::is_sorted(l.begin(), l.end()));
    algos::bubble_sort(l.begin(), l.end());
    BOOST_CHECK(std::is_sorted(l.begin(), l.end()));

    std::vector<double> d = {3.14};
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));
    algos::bubble_sort(d.begin(), d.end());
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));

    std::deque<double> dd = {3.14, -1, 42, 0.0, 0.0, 101, 64.66, 0.0};
    BOOST_CHECK(!std::is_sorted(dd.begin(), dd.end()));
    algos::bubble_sort(dd.begin(), dd.end());
    BOOST_CHECK(std::is_sorted(dd.begin(), dd.end()));

    std::vector<int> vi;
    vi.resize(100);
    std::iota(vi.begin(),vi.end(), 1);
    for(int i = 0; i < 100; ++i)
    {
        std::shuffle(vi.begin(), vi.end(), std::default_random_engine{});
        BOOST_CHECK(!std::is_sorted(vi.begin(), vi.end()));
        algos::bubble_sort(vi.begin(), vi.end());
        BOOST_CHECK(std::is_sorted(vi.begin(), vi.end()));
    }
}

BOOST_AUTO_TEST_CASE(selection_sort)
{
    std::vector<int> v = {5,4,4,3,2,1};
    BOOST_CHECK(!std::is_sorted(v.begin(), v.end()));
    algos::selection_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));
    algos::selection_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));

    std::list<int> l = {4,3,2,1};
    BOOST_CHECK(!std::is_sorted(l.begin(), l.end()));
    algos::selection_sort(l.begin(), l.end());
    BOOST_CHECK(std::is_sorted(l.begin(), l.end()));

    std::vector<double> d = {3.14};
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));
    algos::selection_sort(d.begin(), d.end());
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));

    std::deque<double> dd = {3.14, -1, 42, 0.0, 0.0, 101, 64.66, 0.0};
    BOOST_CHECK(!std::is_sorted(dd.begin(), dd.end()));
    algos::selection_sort(dd.begin(), dd.end());
    BOOST_CHECK(std::is_sorted(dd.begin(), dd.end()));

    std::vector<int> vi;
    vi.resize(100);
    std::iota(vi.begin(),vi.end(), 1);
    for(int i = 0; i < 100; ++i)
    {
        std::shuffle(vi.begin(), vi.end(), std::default_random_engine{});
        BOOST_CHECK(!std::is_sorted(vi.begin(), vi.end()));
        algos::selection_sort(vi.begin(), vi.end());
        BOOST_CHECK(std::is_sorted(vi.begin(), vi.end()));
    }
}

BOOST_AUTO_TEST_CASE(insertion_sort)
{
    std::vector<int> v = {5,4,4,3,2,1};
    BOOST_CHECK(!std::is_sorted(v.begin(), v.end()));
    algos::insertion_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));
    algos::insertion_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));

    std::list<int> l = {4,3,2,1};
    BOOST_CHECK(!std::is_sorted(l.begin(), l.end()));
    algos::insertion_sort(l.begin(), l.end());
    BOOST_CHECK(std::is_sorted(l.begin(), l.end()));

    std::vector<double> d = {3.14};
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));
    algos::insertion_sort(d.begin(), d.end());
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));

    std::deque<double> dd = {3.14, -1, 42, 0.0, 0.0, 101, 64.66, 0.0};
    BOOST_CHECK(!std::is_sorted(dd.begin(), dd.end()));
    algos::insertion_sort(dd.begin(), dd.end());
    BOOST_CHECK(std::is_sorted(dd.begin(), dd.end()));

    std::vector<int> vi;
    vi.resize(100);
    std::iota(vi.begin(),vi.end(), 1);
    for(int i = 0; i < 100; ++i)
    {
        std::shuffle(vi.begin(), vi.end(), std::default_random_engine{});
        BOOST_CHECK(!std::is_sorted(vi.begin(), vi.end()));
        algos::insertion_sort(vi.begin(), vi.end());
        BOOST_CHECK(std::is_sorted(vi.begin(), vi.end()));
    }
}

BOOST_AUTO_TEST_SUITE_END()
