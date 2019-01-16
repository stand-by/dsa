#pragma once
#include <config.hpp>

namespace dsa
{
    
    namespace data_structures
    {

        template<template<typename... Args> typename M, typename K, typename V>
        class LRU_cache
        {
        public:
            
            typedef K                                         key_type;
            typedef V                                         value_type;
            typedef std::list<std::pair<key_type,value_type>> list_type;
            typedef M<key_type, typename list_type::iterator> map_type;

            LRU_cache(config::size_type max_cache_size): cache_size_{max_cache_size} {}
            
            void put(const key_type& key, const value_type& val)
            {
                if(auto map_it = map_.find(key); map_it != map_.end())
                {
                    list_.erase(map_it->second);
                }
                else if(map_.size() == cache_size_)
                {
                    map_.erase(map_.find(list_.front().first));
                    list_.pop_front();
                }
                
                list_.push_back({key, val});
                map_[key] = --list_.end();
            }
            
            value_type get(const key_type& key) const
            {
                auto list_it = map_.at(key);
                value_type corresponding_value = list_it->second;
                
                list_.erase(list_it);
                list_.push_back({key, corresponding_value});
                map_[key] = --list_.end();
                
                return corresponding_value;
            }
            
            bool contains(const key_type& key) const
            {
                return map_.find(key) != map_.end();
            }
            
            config::size_type size() const
            {
                utils::ensure(map_.size() == list_.size());
                return map_.size();
            }
            
            config::size_type max_size() const
            {
                return cache_size_;
            }
            
        private:
            
            const config::size_type cache_size_;
            mutable map_type        map_{};
            mutable list_type       list_{};
            
        };
        
    }
    
}
