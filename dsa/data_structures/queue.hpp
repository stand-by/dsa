#pragma once
#include <config.hpp>
#include "linked_list.hpp"

namespace dsa 
{

    namespace data_structures 
    {

        template<typename T>
        class queue 
        {
        public:
            
            config::size_type size() const {
                return list.size();
            }

            bool empty() const {
                return list.empty();
            }

            T front() const {
                utils::expect(list.size() != 0, "queue has zero length");
                return list.front();
            }

            T back() const {
                utils::expect(list.size() != 0, "queue has zero length");
                return list.back();
            }

            void erase() {
                list.erase();
            }

            void enqueue(const T& item) {
                list.push_back(item);
            }

            T dequeue() {
                return list.pop_front();
            }

        private:
            linked_list<T> list;

        };

    }

}
