#pragma once

namespace dsa 
{

    namespace detail
    {

        template<typename T>
        struct node 
        {
            node() = default;
            node(const T& val, node<T>* next=nullptr): data_(val), next_(next) {}

            T data() const { return this->data_; }
            const node<T>* next() const { return this->next_; }
            node<T>* next() { return this->next_; }	

            T data_ = {};
            node<T>* next_ = nullptr;	
        };

        template<typename T>
        struct bidirectional_node 
        {
            bidirectional_node() = default;
            bidirectional_node(const T& val, bidirectional_node<T>* left=nullptr, bidirectional_node<T>* right=nullptr): data_(val), left_(left), right_(right) {}

            T data() const { return this->data_; }
            const bidirectional_node<T>* left() const { return this->left_; }
            bidirectional_node<T>* left() { return this->left_; }
            const bidirectional_node<T>* right() const { return this->right_; }
            bidirectional_node<T>* right() { return this->right_; }
            
            void set_left(bidirectional_node<T>* new_left) { this->left_ = new_left; }
            void set_right(bidirectional_node<T>* new_right) { this->right_ = new_right; }

            T data_ = {};
            bidirectional_node<T>* left_ = nullptr;
            bidirectional_node<T>* right_ = nullptr;
        };

    }

}
