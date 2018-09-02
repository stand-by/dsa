#pragma once
#include <config.hpp>
#include <data_structures/detail/nodes.hpp>

namespace dsa 
{

    namespace data_structures
    {

        template<typename T>
        class linked_list 
        {
        public:

            linked_list(): head_ptr(nullptr), length(0) {}

            linked_list(config::size_type amount) {
                if(amount <= 0) 
                    throw std::length_error("length can not be zero or negative");

                detail::node<T> *walker = new detail::node<T>;
                head_ptr = walker;

                for(int i = 0; i < amount-1; ++i) {
                    walker->next_ = new detail::node<T>;
                    walker = walker->next_;
                }

                length = amount;
            }

            linked_list(T item, config::size_type amount) {
                if(amount <= 0) 
                    throw std::length_error("length can not be zero or negative");

                detail::node<T> *walker = new detail::node<T>(item);
                head_ptr = walker;

                for(int i = 0; i < amount-1; ++i) {
                    walker->next_ = new detail::node<T>(item);
                    walker = walker->next_;
                }

                length = amount;
            }

            linked_list(std::initializer_list<T> init_list)  {
                typename std::initializer_list<T>::const_iterator it = init_list.begin();
                length = init_list.size();

                detail::node<T> *walker = new detail::node<T>(*it++);
                head_ptr = walker;

                for(int i = 0; i < length-1; ++i) {
                    walker->next_ = new detail::node<T>(*it++);
                    walker = walker->next_;
                }
            }

            linked_list(const linked_list& obj) {
                if(obj.length==0) {
                    head_ptr = nullptr;
                    length = 0;
                    return;
                }

                detail::node<T> *copy_walker = obj.head_ptr;

                detail::node<T> *walker = new detail::node<T>(copy_walker->data_);
                head_ptr = walker;

                for(int i = 0, len = obj.length-1; i < len; i++) {
                    copy_walker = copy_walker->next_;
                    walker->next_ = new detail::node<T>(copy_walker->data_);
                    walker = walker->next_;
                }

                length = obj.length;
            }

            ~linked_list() { erase(); }

            linked_list<T>& operator=(const linked_list& obj) {
                if(this == &obj)
                    return *this;

                erase();

                if(obj.length==0) {
                    head_ptr = nullptr;
                    length = 0;
                    return *this;
                }

                detail::node<T> *copy_walker = obj.head_ptr;

                detail::node<T> *walker = new detail::node<T>(copy_walker->data_);
                head_ptr = walker;

                for(int i = 0, len = obj.length-1; i < len; i++) {
                    copy_walker = copy_walker->next_;
                    walker->next_ = new detail::node<T>(copy_walker->data_);
                    walker = walker->next_;
                }

                length = obj.length;
                return *this;
            }

            bool operator==(const linked_list& obj) const {
                if(this == &obj)
                    return true;

                if(length != obj.length) 
                    return false;

                detail::node<T> *walker = head_ptr;
                detail::node<T> *compare_walker = obj.head_ptr;

                for(int i = 0, len = length; i < len; i++) {
                    if(walker->data_ != compare_walker->data_)
                        return false;
                    walker = walker->next_;
                    compare_walker = compare_walker->next_;
                }

                return true;
            }

            bool operator!=(const linked_list& obj) const {
                return !(*this == obj);
            }

            T front() const {
                if(length == 0) 
                    throw std::length_error("linked_list has zero length");
                return head_ptr->data_;
            }

            T back() const {
                if(length == 0) 
                    throw std::length_error("linked_list has zero length");

                detail::node<T> *walker = head_ptr;
                for(int i = 0, len = length; i < len-1; i++)
                    walker = walker->next_;

                return walker->data_;
            }

            config::size_type size() const { return length; }

            const detail::node<T>* head() const { return head_ptr; }

            bool empty() const {
                if(length == 0)
                    return true;
                return false;
            }

            bool contains(const T& item) const {
                if(length == 0) 
                    return false;

                detail::node<T> *walker = head_ptr;

                if(walker->data_ == item) 
                    return true;

                for(int i = 0, len = length; i < len-1; i++) {
                    walker = walker->next_;
                    if(walker->data_ == item) 
                        return true;
                }

                return false;
            }

            config::size_type count(const T& item) const {
                int amount = 0;
                if(length == 0) 
                    return amount;

                detail::node<T> *walker = head_ptr;

                if(walker->data_ == item) 
                    ++amount;

                for(int i = 0, len = length; i < len-1; i++) {
                    walker = walker->next_;
                    if(walker->data_ == item) ++amount;
                }

                return amount;
            }

            config::index_type find_index_of(const T& item) const {
                if(length == 0) 
                    return -1;

                detail::node<T> *walker = head_ptr;

                if(walker->data_ == item) 
                    return 0;

                for(int i = 1, len = length; i < len; i++) {
                    walker = walker->next_;
                    if(walker->data_ == item) 
                        return i;
                }

                return -1;
            }

            void erase() {
                detail::node<T> *eraser;

                for(int i = 0, len = length; i < len; ++i) {
                    eraser = head_ptr;
                    head_ptr = head_ptr->next_;
                    delete eraser;
                }

                head_ptr = nullptr;
                length = 0;
            }

            void insert(config::index_type position, const T& item) {
                if(position >= length || position < 0) 
                    throw std::out_of_range("linked_list index range was exceeded");

                detail::node<T> *new_node = new detail::node<T>(item);

                if(position == 0) {
                    new_node->next_ = head_ptr;
                    head_ptr = new_node;

                } else {
                    detail::node<T> *walker = head_ptr;

                    for(int i = position-1; i > 0; --i)
                        walker = walker->next_;

                    new_node->next_ = walker->next_;
                    walker->next_ = new_node;
                }

                ++length;
            }

            void push_back(const T& item) {
                detail::node<T> *new_node = new detail::node<T>(item);
                detail::node<T> *walker  = head_ptr;

                if (length == 0) 
                    head_ptr = new_node;
                else {
                    for(int i = 0, len = length-1; i < len; i++)
                        walker = walker->next_;
                    walker->next_ = new_node;
                }

                ++length;
            }

            void push_front(const T& item) {
                detail::node<T> *new_node = new detail::node<T>(item);

                new_node->next_ = head_ptr;
                head_ptr = new_node;

                ++length;
            }

            T pop_by_index(config::index_type index) {
                if(index >= length || index < 0) 
                    throw std::out_of_range("linked_list index range was exceeded");

                T pop_item;
                detail::node<T> *delete_node;
                detail::node<T> *walker = head_ptr;

                if(index == 0) {
                    pop_item = head_ptr->data_;
                    delete_node = head_ptr;
                    head_ptr = head_ptr->next_;

                    delete delete_node;
                    --length;

                    return pop_item;
                }

                for(int i = 0; i < index-1; ++i)
                    walker = walker->next_;

                delete_node = walker->next_;
                walker->next_ = walker->next_->next_;
                pop_item = delete_node->data_;
                delete delete_node;
                --length;

                return pop_item;
            }

            T pop_back() {
                if(length == 0) 
                    throw std::length_error("linked_list has zero length");
                return pop_by_index(length-1);
            }

            T pop_front() {
                if(length == 0) 
                    throw std::length_error("linked_list has zero length");
                return pop_by_index(0);
            }

            void reverse() {
                detail::node<T> *prev_node = head_ptr;
                if(length == 0 || prev_node == nullptr || prev_node->next_ == nullptr) 
                    return;

                detail::node<T> *curr_node = head_ptr->next_;
                if(curr_node->next_ == nullptr) {
                    prev_node->next_ = nullptr;
                    curr_node->next_ = prev_node;
                    head_ptr = curr_node;
                    return;
                }

                detail::node<T> *next__node = head_ptr->next_->next_;
                prev_node->next_ = nullptr;
                do {
                    curr_node->next_ = prev_node;

                    prev_node = curr_node;
                    curr_node = next__node;
                    if(next__node->next_ != nullptr) next__node = next__node->next_;

                    if(curr_node->next_ == nullptr) {
                        curr_node->next_ = prev_node;
                        break;
                    }
                } while(true);
                head_ptr = curr_node;
            }

        private:
            detail::node<T>* head_ptr;
            config::size_type length;

        };

    }

}
