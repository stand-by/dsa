#pragma once
#include <config.hpp>

namespace dsa 
{

    namespace data_structures 
    {

        template <typename T>
        class vector 
        {
            static_assert(std::is_pod<T>::value, "vector logic can handle only POD types");
        public:

            vector(): memory_block(nullptr), capacity(0), length(0) {}
            
            vector(config::size_type len): memory_block(new T[len]()), capacity(len), length(len) {}
            
            vector(const T& item, int len): vector(len) {
                for(int i=0, l=length; i<l; ++i)
                    memory_block[i] = item;
            }

            vector(std::initializer_list<T> init_list): vector(init_list.size())  {
                int i = 0;
                for (const T& e: init_list) {
                    memory_block[i] = e;
                    ++i;
                }
            }

            vector(const vector &obj): vector(obj.length) {
                for (int i=0, l=length; i<l; ++i)
                    memory_block[i] = obj.memory_block[i];
            }
            
            ~vector() {
                erase();
            }

            void reserve(config::size_type size) {
                if(size < 0) 
                    throw std::length_error("Cannot change capacity to negative value");
                else if(size <= capacity) 
                    return;

                capacity = size;
                T* new_memory_block = new T[capacity];

                for (int i=0, l=length; i<l; ++i)
                    new_memory_block[i] = memory_block[i];

                delete[] memory_block;
                memory_block = new_memory_block;
            }

            void shrink() {
                capacity = length;
                T* new_memory_block = new T[capacity];

                for(int i=0, l=length; i<l; ++i)
                    new_memory_block[i] = memory_block[i];

                delete[] memory_block;
                memory_block = new_memory_block;
            }

            T* data() { return &memory_block[0]; }
            const T* data() const { return &memory_block[0]; }

            T front() const { return memory_block[0]; }
            T back() const { return memory_block[length-1]; }

            T& operator[](config::index_type index) { return memory_block[index]; }
            const T& operator[](config::index_type index) const { return memory_block[index]; }

            vector<T>& operator=(const vector &obj) {
                if(this == &obj)
                    return *this;

                delete[] memory_block;
                length = obj.length;
                capacity = obj.capacity;
                memory_block = new T[capacity];

                for(int i=0, l=length; i<l; ++i)
                    memory_block[i] = obj.memory_block[i];

                return *this;
            }

            bool operator==(const vector &obj) const {
                if(this == &obj)
                    return true;

                if(length != obj.length) 
                    return false;

                for(int i=0, l=length; i<l; ++i)
                    if(memory_block[i] != obj.memory_block[i]) 
                        return false;

                return true;
            }

            bool operator!=(const vector &obj) const {
                return !(*this == obj);
            }
            
            config::size_type size() const { return length; }
            config::size_type get_capacity() const { return capacity; }

            bool empty() const {
                if(length == 0) 
                    return true;
                return false;
            }

            bool contains(const T& item) const {
                for(int i=0, l=length; i<l; ++i)
                    if(item == memory_block[i]) return true;
                return false;
            }

            int count(T item) const {
                int amount = 0;

                for(int i = 0, l = length; i < l; ++i)
                    if(memory_block[i] == item) ++amount;

                return amount;
            }

            config::index_type find_index_of(const T& item, config::index_type from_index = 0) const {
                if(from_index >= length || from_index < 0) 
                    throw std::out_of_range("vector index range was exceeded");

                for(int i = from_index, len = length; i < len; i++)
                    if(item == memory_block[i]) return i;

                return -1;
            }

            void reverse() {
                for(int i=0, len=length; i < (len/2); ++i)
                    std::swap(memory_block[i], memory_block[len-1-i]);
            }

            void sort() {
                for (int gap = length/2; gap > 0; gap /= 2) {
                    for (int i = gap, l = length; i < l; i += 1) {
                        T temp = memory_block[i];

                        int j;
                        for (j = i; j >= gap && memory_block[j - gap] > temp; j -= gap)
                            memory_block[j] = memory_block[j - gap];

                        memory_block[j] = temp;
                    }
                }
            }

            void erase() {
                delete[] memory_block;
                memory_block = nullptr;
                length = 0;
                capacity = 0;
            }

            void remove_by_index(config::index_type index) {
                if(length == 0) 
                    throw std::length_error("vector has zero length");
                if(index >= length || index < 0) 
                    throw std::out_of_range("vector index range was exceeded");

                for(int i = index+1, len = length; i < len; ++i)
                    memory_block[i-1] = memory_block[i];
                
                --length;
            }

            void push_back(const T& item) {
                if(capacity<length+1)
                    reserve(length==0 ? 10 : 2*capacity);

                memory_block[length] = item;
                ++length;
            }

            T pop_back() {
                if(length == 0) 
                    throw std::length_error("vector has zero length");
                --length;
                return memory_block[length];
            }

            T pop_front() {
                if(length == 0) 
                    throw std::length_error("vector has zero length");

                T first_elem = memory_block[0];
                for(int i = 1, l=length; i<l; ++i)
                    memory_block[i-1] = memory_block[i];

                --length;
                return first_elem;
            }

            void insert(config::index_type position, const T& item) {
                if(position >= length || position < 0) 
                    throw std::out_of_range("vector index range was exceeded");

                if(capacity<length+1)
                    reserve(length==0 ? 10 : 2*capacity);

                for(int i = length; i!=position; --i)
                    memory_block[i] = memory_block[i-1];

                memory_block[position] = item;
                ++length;
            }

        private:

            T* memory_block;
            config::size_type capacity;
            config::size_type length;

        };

        template<typename T>
        T* begin(vector<T>& vec)
        {
            return vec.data();
        }
        template<typename T>
        T* end(vector<T>& vec)
        {
            return vec.data() + vec.size();
        }

    }
    
}
