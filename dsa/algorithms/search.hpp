#pragma once
#include <config.hpp>

namespace dsa 
{

    namespace algorithms 
    {

        namespace detail 
        {

            template <typename InputIterator>
            inline InputIterator linear_search_impl(InputIterator begin, InputIterator end,
                                                    const typename std::iterator_traits<InputIterator>::value_type& value,
                                                    std::input_iterator_tag)
            {
                for(; begin != end; ++begin)
                    if(*begin == value) 
                    return begin;
                return end;
            }

            template <typename RandomAccessIterator>
            inline std::pair<bool,RandomAccessIterator> binary_search_impl(RandomAccessIterator begin, RandomAccessIterator end,
                                                                           const typename std::iterator_traits<RandomAccessIterator>::value_type& value,
                                                                           std::random_access_iterator_tag)
            {
                RandomAccessIterator candidate_it = begin + (end-begin)/2;
                const auto& candidate = *candidate_it;

                if((end-begin) == 1 && candidate != value)
                    return {false,candidate_it};

                if(candidate > value) 
                    return binary_search_impl(begin, candidate_it, value, std::random_access_iterator_tag{});
                else if(candidate < value) 
                    return binary_search_impl(candidate_it, end, value, std::random_access_iterator_tag{});
                 else
                    return {true, candidate_it};
            }

        }

        template <typename InputIterator>
        InputIterator linear_search(InputIterator begin, InputIterator end, const typename std::iterator_traits<InputIterator>::value_type& value)
        {
            return detail::linear_search_impl(begin, end, value, typename std::iterator_traits<InputIterator>::iterator_category{});
        }

        template <typename RandomAccessIterator>
        RandomAccessIterator binary_search(RandomAccessIterator begin, RandomAccessIterator end, const typename std::iterator_traits<RandomAccessIterator>::value_type& value)
        {
            auto [found,it] = detail::binary_search_impl(begin, end, value, typename std::iterator_traits<RandomAccessIterator>::iterator_category{});
            return found ? it : end;
        }

    }

}