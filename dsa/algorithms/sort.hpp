#pragma once
#include <config.hpp>

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
            template <typename I>
            void merge(I begin, I middle, I end)
            {
                std::vector<typename I::value_type> sorted;
                sorted.reserve(std::distance(begin, end));

                auto left_begin = begin;
                auto right_begin = middle;
                while(left_begin != middle)
                {
                    if(*right_begin < *left_begin && right_begin != end)
                    {
                        sorted.emplace_back(*right_begin);
                        ++right_begin;
                    } else if(left_begin != middle) {
                        sorted.emplace_back(*left_begin);
                        ++left_begin;
                    }
                }
                if(right_begin != end)
                    sorted.emplace_back(*right_begin);

                std::copy(sorted.begin(), sorted.end(), begin);
            }
        }
        template <typename I>
        void merge_sort(I begin, I end)
        {            
            using it_cat = typename std::iterator_traits<I>::iterator_category;
            static_assert(std::is_base_of<std::random_access_iterator_tag, it_cat>::value,
                         "merge_sort accepts random access iterator");

            if(begin+1 == end)
                return;

            auto middle = begin + std::distance(begin, end) / 2;

            merge_sort(begin, middle);
            merge_sort(middle, end);

            detail::merge(begin, middle, end);
        }

    }

}