#pragma once
#include <config.hpp>
#include <data_structures/heap.hpp>

namespace dsa
{
    
    namespace data_structures
    {
        
        template<typename T, typename C = std::greater<T>>
        class priority_queue
        {
        public:
            typedef T value_type;
            typedef C compare_type;
            
            priority_queue() = default;
            
            template <typename I>
            priority_queue(I begin, I end) : max_heap_{ build_max_heap(begin, end) } {}
            
            bool empty() const
            {
                return max_heap_.empty();
            }
            
            auto size() const
            {
                return max_heap_.size();
            }
            
            value_type top() const
            {
                return max_heap_.top();
            }
            
            value_type pop()
            {
                return max_heap_.pop_top();
            }
            
            void push(const value_type& val)
            {
                max_heap_.add(val);
            }
            
        private:
            heap<value_type, compare_type> max_heap_;
            
        };
        
    }
    
}
