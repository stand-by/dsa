#pragma once
#include <config.hpp>

namespace dsa 
{

    namespace utilities 
    {

        template<typename C, typename V = typename C::value_type>
        class item_counter 
        {
        public:
            
            using map_t = std::map<V,int>;

            item_counter() = default;

            item_counter(typename C::const_iterator begin, typename C::const_iterator end) {
                add(begin, end);
            }

            item_counter(const C& container): item_counter(container.cbegin(), container.cend()) {}

            void add(const V& value, int amount) {
                map_m[value] += amount;
                if(map_m[value] <= 0)
                    map_m.erase(value);
            }

            void add(typename C::const_iterator begin, typename C::const_iterator end) {
                for(; begin != end; ++begin) {
                    map_m[*begin] += 1;
                }
            }

            std::vector<V> items() const {
                std::vector<V> items;
                items.reserve(map_m.size());

                for(auto it = map_m.begin(); it != map_m.end(); ++it)
                    items.push_back(it->first);

                return items;
            }

            int size() const { return map_m.size(); }

            typename map_t::const_iterator begin() const { return map_m.cbegin(); }
            typename map_t::iterator begin() { return map_m.begin(); }

            typename map_t::const_iterator end() const { return map_m.cend(); }
            typename map_t::iterator end() { return map_m.end(); }

            int& operator[](const V& value) { return map_m[value]; }
            int operator[](const V& value) const { return map_m[value]; }

            item_counter operator+(const item_counter& obj) const {
                item_counter<C,V> res = *this;
                for(auto it = obj.map_m.begin(); it != obj.map_m.end(); ++it)
                    if(res.map_m.count(it->first) == 0)
                        res.map_m[it->first] = it->second;
                    else
                        res.map_m[it->first] += it->second;
                return res;
            }

            item_counter operator-(const item_counter& obj) const {
                item_counter<C,V> res = *this;
                for(auto it = obj.map_m.begin(); it != obj.map_m.end(); ++it) {
                    if(res.map_m.count(it->first) != 0)
                        res.map_m[it->first] -= it->second;

                    if(res.map_m[it->first] <= 0)
                        res.map_m.erase(it->first);
                }
                return res;
            }

            item_counter& operator+=(const item_counter& obj) {
                *this = *this + obj;
                return *this;
            }

            item_counter& operator-=(const item_counter& obj) {
                *this = *this - obj;
                return *this;
            }

            bool operator==(const item_counter& obj) const {
                if (&obj == this) 
                    return true;
                return this->map_m == obj.map_m;
            }

            bool operator!=(const item_counter& obj) const {
                return !(*this == obj);
            }

        private:

            void add(typename map_t::const_iterator begin, typename map_t::const_iterator end) {
                for(; begin != end; ++begin) {
                    map_m[begin->first] += begin->second;
                    if(map_m[begin->first] <= 0)
                        map_m.erase(begin->first);
                }
            }

            void eliminate_rudiments() {
                for(auto it = map_m.begin(); it != map_m.end();)
                    if(it->second <= 0)
                        map_m.erase(it++);
                    else
                        ++it;
            }

            map_t map_m = {};

        };

    }

}

