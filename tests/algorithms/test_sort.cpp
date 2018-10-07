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

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(5,20);

    std::vector<int> vi;
    vi.resize(100);
    std::iota(vi.begin(),vi.end(), 1);
    for(int i = 0; i < 100; ++i)
    {
        auto current_end = vi.end() - dist(rng);
        std::shuffle(vi.begin(), vi.end(), std::default_random_engine{});
        BOOST_CHECK(!std::is_sorted(vi.begin(), current_end));
        algos::bubble_sort(vi.begin(), current_end);
        BOOST_CHECK(std::is_sorted(vi.begin(), current_end));
        BOOST_CHECK(!std::is_sorted(vi.begin(), vi.end()));
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

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(5,20);

    std::vector<int> vi;
    vi.resize(100);
    std::iota(vi.begin(),vi.end(), 1);
    for(int i = 0; i < 100; ++i)
    {
        auto current_end = vi.end() - dist(rng);
        std::shuffle(vi.begin(), vi.end(), std::default_random_engine{});
        BOOST_CHECK(!std::is_sorted(vi.begin(), current_end));
        algos::selection_sort(vi.begin(), current_end);
        BOOST_CHECK(std::is_sorted(vi.begin(), current_end));
        BOOST_CHECK(!std::is_sorted(vi.begin(), vi.end()));
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

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(5,20);

    std::vector<int> vi;
    vi.resize(100);
    std::iota(vi.begin(),vi.end(), 1);
    for(int i = 0; i < 100; ++i)
    {
        auto current_end = vi.end() - dist(rng);
        std::shuffle(vi.begin(), vi.end(), std::default_random_engine{});
        BOOST_CHECK(!std::is_sorted(vi.begin(), current_end));
        algos::insertion_sort(vi.begin(), current_end);
        BOOST_CHECK(std::is_sorted(vi.begin(), current_end));
        BOOST_CHECK(!std::is_sorted(vi.begin(), vi.end()));
    }
}

BOOST_AUTO_TEST_CASE(binary_insertion_sort)
{
    std::vector<int> v = {5,4,4,3,2,1};
    BOOST_CHECK(!std::is_sorted(v.begin(), v.end()));
    algos::binary_insertion_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));
    algos::binary_insertion_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));

    std::vector<double> d = {3.14};
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));
    algos::binary_insertion_sort(d.begin(), d.end());
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));

    std::deque<double> dd = {3.14, -1, 42, 0.0, 0.0, 101, 64.66, 0.0};
    BOOST_CHECK(!std::is_sorted(dd.begin(), dd.end()));
    algos::binary_insertion_sort(dd.begin(), dd.end());
    BOOST_CHECK(std::is_sorted(dd.begin(), dd.end()));

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(5,20);

    std::vector<int> vi;
    vi.resize(100);
    std::iota(vi.begin(),vi.end(), 1);
    for(int i = 0; i < 100; ++i)
    {
        auto current_end = vi.end() - dist(rng);
        std::shuffle(vi.begin(), vi.end(), std::default_random_engine{});
        BOOST_CHECK(!std::is_sorted(vi.begin(), current_end));
        algos::binary_insertion_sort(vi.begin(), current_end);
        BOOST_CHECK(std::is_sorted(vi.begin(), current_end));
        BOOST_CHECK(!std::is_sorted(vi.begin(), vi.end()));
    }
}

BOOST_AUTO_TEST_CASE(merge_sort)
{
    std::vector<int> v = {5,4,3,2,1};
    BOOST_CHECK(!std::is_sorted(v.begin(), v.end()));
    algos::merge_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));
    algos::merge_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));

    std::vector<double> d = {3.14};
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));
    algos::merge_sort(d.begin(), d.end());
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));

    std::deque<double> dd = {3.14, -1, 42, 0.0, 0.0, 101, 64.66, 0.0};
    BOOST_CHECK(!std::is_sorted(dd.begin(), dd.end()));
    algos::merge_sort(dd.begin(), dd.end());
    BOOST_CHECK(std::is_sorted(dd.begin(), dd.end()));

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(5,20);

    std::vector<int> vi;
    vi.resize(100);
    std::iota(vi.begin(),vi.end(), 1);
    for(int i = 0; i < 100; ++i)
    {
        auto current_end = vi.end() - dist(rng);
        std::shuffle(vi.begin(), vi.end(), std::default_random_engine{});
        BOOST_CHECK(!std::is_sorted(vi.begin(), current_end));
        algos::merge_sort(vi.begin(), current_end);
        BOOST_CHECK(std::is_sorted(vi.begin(), current_end));
        BOOST_CHECK(!std::is_sorted(vi.begin(), vi.end()));
    }
}

BOOST_AUTO_TEST_CASE(heap_sort)
{
    std::vector<int> v = {5,4,4,3,2,1};
    BOOST_CHECK(!std::is_sorted(v.begin(), v.end()));
    algos::heap_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));
    algos::heap_sort(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));

    std::list<int> l = {4,3,2,1};
    BOOST_CHECK(!std::is_sorted(l.begin(), l.end()));
    algos::heap_sort(l.begin(), l.end());
    BOOST_CHECK(std::is_sorted(l.begin(), l.end()));

    std::vector<double> d = {3.14};
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));
    algos::heap_sort(d.begin(), d.end());
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));

    std::deque<double> dd = {3.14, -1, 42, 0.0, 0.0, 101, 64.66, 0.0};
    BOOST_CHECK(!std::is_sorted(dd.begin(), dd.end()));
    algos::heap_sort(dd.begin(), dd.end());
    BOOST_CHECK(std::is_sorted(dd.begin(), dd.end()));

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(5,20);

    std::vector<int> vi;
    vi.resize(100);
    std::iota(vi.begin(),vi.end(), 1);
    for(int i = 0; i < 100; ++i)
    {
        auto current_end = vi.end() - dist(rng);
        std::shuffle(vi.begin(), vi.end(), std::default_random_engine{});
        BOOST_CHECK(!std::is_sorted(vi.begin(), current_end));
        algos::heap_sort(vi.begin(), current_end);
        BOOST_CHECK(std::is_sorted(vi.begin(), current_end));
        BOOST_CHECK(!std::is_sorted(vi.begin(), vi.end()));
    }
}

BOOST_AUTO_TEST_SUITE_END()
