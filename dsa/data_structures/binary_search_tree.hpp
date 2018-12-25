#pragma once
#include <config.hpp>
#include <data_structures/detail/nodes.hpp>

namespace dsa
{

    namespace data_structures
    {

        template<typename T, typename C = std::less<T>>
        class binary_search_tree
        {
            template<typename U, typename K>
            friend bool operator==(const binary_search_tree<U,K>& lhs, const binary_search_tree<U,K>& rhs);
            
        public:
            
            typedef T                            value_type;
            typedef C                          compare_type;
            typedef binary_search_tree<T,C>       tree_type;
            typedef detail::bidirectional_node<T> node_type;

            binary_search_tree() = default;
            explicit binary_search_tree(const value_type& root_val): root_{new node_type{root_val}} {}

            ~binary_search_tree()
            {
                auto destroy = [](node_type* node){ delete node; };
                traverse_postorder(this->root_, destroy);
            }
            
            binary_search_tree(tree_type&& obj): root_{obj.root_}
            {
                obj.root_ = nullptr;
            }
            binary_search_tree& operator=(tree_type&& obj)
            {
                this->root_ = obj.root_;
                obj.root_ = nullptr;
                return *this;
            }
            
            binary_search_tree(const tree_type& obj)
            {
                std::function<node_type*(node_type*)> copy_tree;
                copy_tree = [&copy_tree](node_type* origin_node) -> node_type*
                {
                    if(origin_node == nullptr)
                        return nullptr;
                    
                    node_type* node = new node_type{origin_node->data_};
                    node->left_ = copy_tree(origin_node->left_);
                    node->right_ = copy_tree(origin_node->right_);
                    return node;
                };
                
                this->root_ = copy_tree(obj.root_);
            }
            binary_search_tree& operator=(tree_type obj)
            {
                this->root_ = obj.root_;
                obj.root_ = nullptr;
                return *this;
            }

            binary_search_tree& add(const value_type& val)
            {
                if(root_ == nullptr)
                {
                    root_ = new node_type{val};
                    return *this;
                }

                auto [runner,lagged_runner] = find_node(this->root_, val);
                
                if(runner != nullptr)
                    throw std::runtime_error("Value is already present in BST");
                
                if(compare_type{}(val, lagged_runner->data_))
                    lagged_runner->left_ = new node_type{val};
                else
                    lagged_runner->right_ = new node_type{val};

                return *this;
            }

            binary_search_tree& remove(const value_type& val)
            {
                node_type* new_child = nullptr;
                auto [runner,lagged_runner] = find_node(this->root_, val);

                if(runner == nullptr)
                    throw std::runtime_error("Unable to find value");
                
                if(runner->left_ == nullptr && runner->right_ == nullptr)
                    new_child = nullptr;
                else if(runner->left_ == nullptr || runner->right_ == nullptr)
                    new_child = runner->left_ != nullptr ? runner->left_ : runner->right_;
                else
                {
                    auto new_runner = runner->right_;
                    auto new_lagged_runner = runner;
                    
                    while(new_runner != nullptr && new_runner->left_ != nullptr)
                    {
                        new_lagged_runner = new_runner;
                        new_runner = new_runner->left_;
                    }
                    
                    if(new_lagged_runner != nullptr && new_lagged_runner->left_ == new_runner)
                        new_lagged_runner->left_ = nullptr;
                    else if(new_lagged_runner != nullptr)
                        new_lagged_runner->right_ = nullptr;

                    new_child = new_runner; //inorder_successor
                    new_child->left_ = runner->left_;
                    new_child->right_ = runner->right_;
                }
                
                if(lagged_runner != nullptr && lagged_runner->left_ == runner)
                    lagged_runner->left_ = new_child;
                else if(lagged_runner != nullptr)
                    lagged_runner->right_ = new_child;
                else
                    this->root_ = new_child;
                
                delete runner;
                return *this;
            }
            
            bool empty() const
            {
                return root_ == nullptr;
            }
            
            value_type min() const
            {
                if(this->root_ == nullptr)
                    throw std::runtime_error("BST is empty");
                auto min_node = this->root_;
                for(; min_node->left_ != nullptr; min_node = min_node->left_) {}
                return min_node->data_;
            }
            
            value_type max() const
            {
                if(this->root_ == nullptr)
                    throw std::runtime_error("BST is empty");
                auto max_node = this->root_;
                for(; max_node->right_ != nullptr; max_node = max_node->right_) {}
                return max_node->data_;
            }
        
            bool contains(const value_type& val) const
            {
                auto [runner,_] = find_node(this->root_, val);
                return runner != nullptr;
            }
            
            config::size_type height() const
            {
                config::size_type height = 0;
                
                auto count = [&height](node_type* node, int& h) { height = std::max(height, ++h); };
                traverse_preorder(this->root_, count, 0);
                
                return height;
            }
            
            config::size_type size() const
            {
                config::size_type size = 0;
                
                auto count = [&size](node_type* node){ ++size; };
                traverse_inorder(this->root_, count);
                
                return size;
            }

        protected:
            
            template<typename F, typename... Args>
            static void traverse_preorder(node_type* node, /*const*/ F& func, Args... args)
            {
                if(node == nullptr)
                    return;
                
                func(node, args...);
                traverse_preorder(node->left_, func, args...);
                traverse_preorder(node->right_, func, args...);
            }
            
            template<typename F, typename... Args>
            static void traverse_inorder(node_type* node, /*const*/ F& func, Args... args)
            {
                if(node == nullptr)
                    return;
                
                traverse_inorder(node->left_, func, args...);
                func(node, args...);
                traverse_inorder(node->right_, func, args...);
            }
            
            template<typename F, typename... Args>
            static void traverse_postorder(node_type* node, /*const*/ F& func, Args... args)
            {
                if(node == nullptr)
                    return;
                
                traverse_postorder(node->left_, func, args...);
                traverse_postorder(node->right_, func, args...);
                func(node, args...);
            }
            
        private:
            
            static auto find_node(node_type* runner, const value_type& val)
            {
                node_type* lagged_runner = nullptr;
                
                while(runner != nullptr && runner->data_ != val)
                {
                    lagged_runner = runner;
                    if(compare_type{}(val, runner->data_))
                        runner = runner->left_;
                    else
                        runner = runner->right_;
                }
                
                return std::make_tuple(runner, lagged_runner);
            }

            node_type* root_ = nullptr;
        };

        template <typename T, typename C>
        bool operator==(const binary_search_tree<T,C>& lhs, const binary_search_tree<T,C>& rhs)
        {
            typedef typename binary_search_tree<T,C>::node_type node_type;
            
            std::function<bool(node_type*,node_type*)> compare_trees;
            compare_trees = [&compare_trees](node_type* ltree_node, node_type* rtree_node)
            {
                if(ltree_node == nullptr && rtree_node == nullptr)
                    return true;
                else if(ltree_node == nullptr && rtree_node != nullptr)
                    return false;
                else if(ltree_node != nullptr && rtree_node == nullptr)
                    return false;
                
                bool lsubtree_eq = compare_trees(ltree_node->left_, rtree_node->left_);
                bool rsubtree_eq = compare_trees(ltree_node->right_, rtree_node->right_);
                return (ltree_node->data_ == rtree_node->data_) && lsubtree_eq && rsubtree_eq;
            };
            
            return compare_trees(lhs.root_, rhs.root_);
        }
        template <typename T, typename C>
        bool operator!=(const binary_search_tree<T,C>& lhs, const binary_search_tree<T,C>& rhs)
        {
            return !(lhs == rhs);
        }

        
        
        namespace detail
        {
            template<typename K, typename V>
            struct map_less
            {
                constexpr bool operator()(const std::pair<K,V>& lhs, const std::pair<K,V>& rhs) const
                {
                    return lhs.first < rhs.first;
                }
            };
        }
        namespace experimental
        {
            template<typename K, typename V>
            using map = binary_search_tree<std::pair<K,V>, detail::map_less<K,V>>;
        }
    }

}
