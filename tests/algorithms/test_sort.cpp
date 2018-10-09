#include <boost/test/unit_test.hpp>
#include <algorithms/sort.hpp>
#include <iostream>
#include <random>

using namespace dsa;

template<bool forward_iterator_available = true, typename F>
void sort_test(F sort_algo)
{
    std::vector<int> v = {5,4,4,3,2,1};
    BOOST_CHECK(!std::is_sorted(v.begin(), v.end()));
    sort_algo(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));
    sort_algo(v.begin(), v.end());
    BOOST_CHECK(std::is_sorted(v.begin(), v.end()));

    if constexpr (forward_iterator_available)
    {
        std::list<int> l = {4,3,2,1};
        BOOST_CHECK(!std::is_sorted(l.begin(), l.end()));
        sort_algo(l.begin(), l.end());
        BOOST_CHECK(std::is_sorted(l.begin(), l.end()));
    }

    std::vector<double> d = {3.14};
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));
    sort_algo(d.begin(), d.end());
    BOOST_CHECK(std::is_sorted(d.begin(), d.end()));

    std::deque<double> dd = {3.14, -1, 42, 0.0, 0.0, 101, 64.66, 0.0};
    BOOST_CHECK(!std::is_sorted(dd.begin(), dd.end()));
    sort_algo(dd.begin(), dd.end());
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
        sort_algo(vi.begin(), current_end);
        BOOST_CHECK(std::is_sorted(vi.begin(), current_end));
        BOOST_CHECK(!std::is_sorted(vi.begin(), vi.end()));
    }
}

BOOST_AUTO_TEST_SUITE(test_sort)

BOOST_AUTO_TEST_CASE(random_access_iterator_sorts)
{
    sort_test(
            [](auto begin, auto end){ algos::bubble_sort(begin, end); }
    );

    sort_test(
            [](auto begin, auto end){ algos::selection_sort(begin, end); }
    );

    sort_test(
            [](auto begin, auto end){ algos::insertion_sort(begin, end); }
    );

    sort_test<false>(
            [](auto begin, auto end){ algos::binary_insertion_sort(begin, end); }
    );

    sort_test<false>(
            [](auto begin, auto end){ algos::merge_sort(begin, end); }
    );

    sort_test(
            [](auto begin, auto end){ algos::heap_sort(begin, end); }
    );
}

BOOST_AUTO_TEST_SUITE_END()
