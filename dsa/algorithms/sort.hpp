#pragma once
#include <config.hpp>
#include <data_structures/heap.hpp>

namespace dsa 
{

    namespace algorithms 
    {
    
        template <typename I>
        void bubble_sort(I begin, I end)
        {
            using it_cat = typename std::iterator_traits<I>::iterator_category;
            static_assert(std::is_base_of<std::bidirectional_iterator_tag, it_cat>::value,
                         "bubble_sort accepts bidirectional iterator");
            
            for(int i = 0, l = std::distance(begin, end); i < l; ++i)
            {
                auto next_it = begin;
                auto curr_it = next_it++;

                while(next_it != end)
                {
                    if(*curr_it > *next_it)
                        std::swap(*curr_it,*next_it);
                    ++curr_it;
                    ++next_it;
                }
                --end;
            }
        }

        template <typename I>
        void selection_sort(I begin, I end)
        {
            using it_cat = typename std::iterator_traits<I>::iterator_category;
            static_assert(std::is_base_of<std::forward_iterator_tag, it_cat>::value,
                         "selection_sort accepts forward iterator");

            while(begin != end)
            {
                auto inner_it = begin;
                ++inner_it;

                while(inner_it != end)
                {
                    if(*inner_it < *begin)
                        std::swap(*inner_it, *begin);
                    ++inner_it;
                }
                ++begin;
            }
        }

        template <typename I>
        void insertion_sort(I begin, I end)
        {
            using it_cat = typename std::iterator_traits<I>::iterator_category;
            static_assert(std::is_base_of<std::forward_iterator_tag, it_cat>::value,
                         "insertion_sort accepts forward iterator");

            auto it = begin;
            ++it;

            while(it != end)
            {
                auto inner_it = begin;

                while(*inner_it < *it && inner_it != it)
                    ++inner_it;

                if(inner_it != it)
                    std::rotate(inner_it,it,++it);
                else
                    ++it;
            }
        }

        template <typename I>
        void binary_insertion_sort(I begin, I end)
        {
            using it_cat = typename std::iterator_traits<I>::iterator_category;
            static_assert(std::is_base_of<std::random_access_iterator_tag, it_cat>::value,
                         "binary_insertion_sort accepts random access iterator");

            auto it = begin;
            ++it;

            while(it != end)
            {
                auto inner_it = std::upper_bound(begin, it, *it);

                if(inner_it != it)
                    std::rotate(inner_it,it,++it);
                else
                    ++it;
            }
        }

        namespace detail
        {
            template <typename I, typename IS>
            void merge(I begin, I middle, I end, IS storage_begin)
            {
                auto left_begin = begin;
                auto right_begin = middle;
                auto storage_it = storage_begin;

                while(left_begin != middle && right_begin != end)
                {
                    if(*left_begin < *right_begin)
                    {
                        *storage_it = *left_begin;
                        ++left_begin;
                    } else {
                        *storage_it = *right_begin;
                        ++right_begin;
                    }
                    ++storage_it;
                }

                if(left_begin != middle)
                    std::copy(left_begin, left_begin + std::distance(left_begin, middle), storage_it);
                if(right_begin != end)
                    std::copy(right_begin, right_begin + std::distance(right_begin, end), storage_it);
                std::copy(storage_begin, storage_begin + std::distance(begin, end), begin);
            }
            template <typename I, typename IS>
            void merge_sort_impl(I begin, I end, IS storage_begin)
            {
                if(begin+1 == end)
                    return;

                auto middle = begin + std::distance(begin, end) / 2;

                merge_sort_impl(begin, middle, storage_begin);
                merge_sort_impl(middle, end, storage_begin);

                merge(begin, middle, end, storage_begin);
            }
        }
        template <typename I>
        void merge_sort(I begin, I end)
        {            
            using it_cat = typename std::iterator_traits<I>::iterator_category;
            static_assert(std::is_base_of<std::random_access_iterator_tag, it_cat>::value,
                         "merge_sort accepts random access iterator");

            std::vector<typename I::value_type> storage;
            storage.resize(std::distance(begin, end));

            detail::merge_sort_impl(begin, end, storage.begin());
        }

        template <typename I>
        void heap_sort(I begin, I end)
        {
            using it_cat = typename std::iterator_traits<I>::iterator_category;
            static_assert(std::is_base_of<std::forward_iterator_tag, it_cat>::value,
                         "heap_sort accepts forward iterator");

            auto h = structs::build_min_heap(begin, end);

            while(!h.empty()) {
                *begin = h.pop_top();
                ++begin;
            }
        }

    }

}