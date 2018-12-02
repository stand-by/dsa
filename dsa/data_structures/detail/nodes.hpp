#pragma once

namespace dsa 
{

    namespace detail
    {

        template<typename T>
        struct node 
        {
            node(const T& val, node<T>* next=nullptr): data_(val), next_(next) {}

            T data_;
            node<T>* next_ = nullptr;	
        };

        template<typename T>
        struct bidirectional_node 
        {
            bidirectional_node(const T& val, bidirectional_node<T>* left=nullptr, bidirectional_node<T>* right=nullptr): data_(val), left_(left), right_(right) {}

            T data_;
            bidirectional_node<T>* left_ = nullptr;
            bidirectional_node<T>* right_ = nullptr;
        };

    }

}
