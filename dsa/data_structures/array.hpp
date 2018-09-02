#pragma once
#include <config.hpp>

namespace dsa 
{

    namespace data_structures 
    {

        template<typename T, config::size_type length>
        class array
        {
            static_assert(length > 0, "array length cannot be less or equal to zero");

        public:

            typedef T value_type;

            ~array() = default;
            array(const array<T,length>&& rhs) = delete;
            array<T,length>& operator=(array<T,length>&& rhs) = delete;

            array() {
                for (int i = 0; i < length; ++i)
                    memory_chunk[i] = T{};
            }

            array(std::initializer_list<T> init_list) {
                int i = 0;
                for (const T& e: init_list) {
                    memory_chunk[i] = e;
                    ++i;
                }
                while(i!=length) {
                    memory_chunk[i] = T{};
                    ++i;
                }
            }

            array(const array<T,length>& rhs) {
                for (int i = 0; i < length; ++i)
                    memory_chunk[i] = rhs.memory_chunk[i];
            }

            array<T,length>& operator=(const array<T,length>& rhs) {
                if (&rhs == this) {
                    return *this;
                }

                for (int i = 0; i < length; ++i)
                    memory_chunk[i] = rhs.memory_chunk[i];

                return *this;
            }

            bool operator==(const array<T,length>& rhs) const {
                if (&rhs == this) 
                    return true;

                for (int i = 0; i < length; ++i)
                    if (memory_chunk[i] != rhs.memory_chunk[i])
                        return false;

                return true;
            }

            bool operator!=(const array<T,length>& rhs) const {
                return !(*this == rhs);
            }

            T& operator[](int i) {
                if (i < 0 || i >= length) 
                    throw std::out_of_range("i is out of array's range");
                return memory_chunk[i];
            }

            const T& operator[](int i) const {
                if (i < 0 || i >= length) 
                    throw std::out_of_range("i is out of array's range");
                return memory_chunk[i];
            }

            T* data() { return &memory_chunk[0]; }

            const T* data() const { return &memory_chunk[0]; }

            T front() const { return memory_chunk[0]; }

            T back() const { return memory_chunk[length-1]; }

            config::size_type size() const { return length; }

            void fill(const T& e) {
                for (int i = 0; i < length; ++i)
                    memory_chunk[i] = e;
            }

        private:

            T memory_chunk[length];

        };

        template<typename T, int length>
        T* begin(array<T,length>& arr)
        {
            return arr.data();
        }
        template<typename T, int length>
        T* end(array<T,length>& arr)
        {
            return arr.data() + length;
        }

    }

}
