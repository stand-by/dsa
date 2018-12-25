#pragma once
#include <config.hpp>
#include <data_structures/binary_search_tree.hpp>

namespace dsa
{
    
    namespace data_structures
    {
        
        template<typename T, typename C = std::less<T>>
        class set
        {
        public:
            
            typedef T value_type;
            typedef C compare_type;

            set() = default;

            template<typename I>
            set(I begin, I end)
            {
                for(; begin != end; ++begin)
                    bst_.add(*begin);
            }

            bool empty() const
            {
                return bst_.empty();
            }
            
            auto size() const
            {
                return bst_.size();
            }
            
            value_type min() const
            {
                return bst_.min();
            }
            
            value_type max() const
            {
                return bst_.max();
            }
            
            bool contains(const value_type& val) const
            {
                return bst_.contains(val);
            }
            
            void insert(const value_type& val)
            {
                bst_.add(val);
            }
            
            void remove(const value_type& val)
            {
                bst_.remove(val);
            }
            
            void clear()
            {
                while(!bst_.empty())
                    bst_.remove(bst_.min());
            }
            
        private:
            binary_search_tree<value_type> bst_;
            
        };
        
    }
    
}
