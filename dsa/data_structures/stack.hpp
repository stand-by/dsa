#pragma once
#include <config.hpp>
#include "linked_list.hpp"

namespace dsa 
{

    namespace data_structures 
    {

        template<typename T>
        class stack 
        {
        public:

            config::size_type size() const {
                return list.size();
            }

            bool empty() const {
                return list.empty();
            }

            T peek() const {
                if(list.size() == 0) 
                    throw std::length_error("stack has zero length");
                return list.front();
            }

            void erase() {
                list.erase();
            }

            void push(const T& item) {
                list.push_front(item);
            }

            T pop() {
                return list.pop_front();
            }

        private:
            linked_list<T> list;

        };

    }
}
