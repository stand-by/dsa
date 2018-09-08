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

    }

}