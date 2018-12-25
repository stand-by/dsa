#pragma once
#include <config.hpp>

namespace dsa
{
    
    namespace data_structures
    {
        
        template<typename K, typename V, typename H>
        class hash_table
        {
        public:
            
            typedef K                        key_type;
            typedef V                      value_type;
            typedef H              hash_function_type;
            typedef hash_table<K,V,H> hash_table_type;
            
            explicit hash_table(config::size_type slots, hash_function_type hash): table_(slots), hash_func_(std::move(hash)) {}
            
            value_type& operator[](const key_type& key)
            {
                auto& chain = access_chain(key);
                auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto& p){ return p.first == key; });
                
                if(it == chain.end())
                {
                    chain.push_back(std::make_pair(key, value_type{}));
                    return chain.back().second;
                }
                else
                    return it->second;
            }
            
            value_type& at(const key_type& key)
            {
                return const_cast<value_type&>(const_cast<const hash_table_type&>(*this).at(key));
            }
            const value_type& at(const key_type& key) const
            {
                const auto& chain = access_chain(key);
                auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto& p){ return p.first == key; });
                
                if(it == chain.end())
                    throw std::runtime_error("Cannot find value because key is not present in hash table");
                else
                    return it->second;
            }
            
            void add(const key_type& key, const value_type& val)
            {
                auto& chain = access_chain(key);
                auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto& p){ return p.first == key; });
                
                if(it != chain.end())
                    throw std::runtime_error("Cannot add value because key is already used in hash table");
                else
                    chain.push_back(std::make_pair(key, val));
            }
            
            void update(const key_type& key, const value_type& val)
            {
                auto& chain = access_chain(key);
                auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto& p){ return p.first == key; });
                
                if(it == chain.end())
                    chain.push_back(std::make_pair(key, val));
                else
                    it->second = val;
            }
            
            void remove(const key_type& key)
            {
                auto& chain = access_chain(key);
                auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto& p){ return p.first == key; });
                
                if(it == chain.end())
                    throw std::runtime_error("Cannot remove value because key is not present in hash table");
                else
                    chain.erase(it);
            }
            
            void resize(config::size_type slots)
            {
                std::vector<std::list<std::pair<key_type,value_type>>> new_table(slots);
                
                for(auto& chain: table_)
                {
                    for(auto& pair: chain)
                    {
                        auto new_index = compute_index(pair.first, slots);
                        new_table.at(new_index).push_back(std::move(pair));
                    }
                }
                
                table_.swap(new_table);
            }
            
            void clear()
            {
                table_.clear();
                table_.shrink_to_fit();
            }
            
            bool has_key(const key_type& key) const
            {
                auto& chain = access_chain(key);
                auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto& p){ return p.first == key; });
                return it != chain.end();
            }
            
            bool empty() const
            {
                return this->size() == 0;
            }
            
            config::size_type slots() const
            {
                return table_.size();
            }
            
            config::size_type size() const
            {
                return std::accumulate(table_.begin(), table_.end(), 0,
                                       [](config::size_type acc, const auto& chain){ return acc + chain.size(); });
            }
            
            double load_factor() const
            {
                return double(size()) / slots();
            }
            
        private:
            
            auto compute_index(const key_type& key) const
            {
                const config::size_type size = table_.size();
                auto index = hash_func_(key, size);
                return index;
            }
            auto compute_index(const key_type& key, const config::size_type size) const
            {
                auto index = hash_func_(key, size);
                return index;
            }
            
            const auto& access_chain(const key_type& key) const
            {
                auto index = compute_index(key);
                const auto& chain = table_.at(index);
                return chain;
            }
            auto& access_chain(const key_type& key)
            {
                auto index = compute_index(key);
                auto& chain = table_.at(index);
                return chain;
            }
            
            std::vector<std::list<std::pair<key_type,value_type>>> table_ = {};
            hash_function_type hash_func_;
            
        };
        
        template<typename K, typename V, typename H>
        auto make_hash_table(config::size_type slots, H hash_func)
        {
            return hash_table<K, V, H>{slots, std::move(hash_func)};
        }
        
    }

}
