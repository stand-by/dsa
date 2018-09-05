#pragma once
#include <config.hpp>

namespace dsa 
{

    namespace algorithms 
    {

        namespace detail 
        {

            template <typename RandomAccessIterator>
            inline std::pair<bool,RandomAccessIterator> binary_search_impl(RandomAccessIterator begin, RandomAccessIterator end,
                                                                           const typename std::iterator_traits<RandomAccessIterator>::value_type& value)
            {
                RandomAccessIterator candidate_it = begin + (end-begin)/2;
                const auto& candidate = *candidate_it;

                if((end-begin) == 1 && candidate != value)
                    return {false,candidate_it};

                if(candidate > value) 
                    return binary_search_impl(begin, candidate_it, value);
                else if(candidate < value) 
                    return binary_search_impl(candidate_it, end, value);
                 else
                    return {true, candidate_it};
            }

        }

        template <typename InputIterator>
        InputIterator linear_search(InputIterator begin, InputIterator end, const typename std::iterator_traits<InputIterator>::value_type& value)
        {
            using it_cat = typename std::iterator_traits<InputIterator>::iterator_category;
            static_assert(std::is_base_of<std::input_iterator_tag, it_cat>::value, "linear_search accepts input iterator");

            for(; begin != end; ++begin)
                if(*begin == value) 
                    return begin;
            return end;
        }

        template <typename RandomAccessIterator>
        RandomAccessIterator binary_search(RandomAccessIterator begin, RandomAccessIterator end, const typename std::iterator_traits<RandomAccessIterator>::value_type& value)
        {
            using it_cat = typename std::iterator_traits<RandomAccessIterator>::iterator_category;
            static_assert(std::is_same<it_cat, std::random_access_iterator_tag>::value, "binary_search can accept only random access iterator");

            auto [found,it] = detail::binary_search_impl(begin, end, value);
            return found ? it : end;
        }

    }

}