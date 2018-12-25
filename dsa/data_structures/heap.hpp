#pragma once
#include <config.hpp>
#include <data_structures/detail/nodes.hpp>

namespace dsa
{

    namespace data_structures
    {

        template <typename T, typename Comp>
        class heap;

        template<typename C, typename I>
        heap<typename I::value_type, C> heapify(I begin, I end);

        template <typename T>
        using min_heap = heap<T, std::less<T>>;
        template <typename T>
        using max_heap = heap<T, std::greater<T>>;



        template <typename T, typename Comp>
        class heap
        {

            template<typename C, typename I>
            friend heap<typename I::value_type, C> heapify(I begin, I end);

            template<typename U, typename C>
            friend bool operator==(const heap<U,C>& lhs, const heap<U,C>& rhs);

        public:

            heap() = default;
            template <typename I>
            heap(I begin, I end)
            {
                *this = heapify<Comp>(begin, end);
            }

            bool empty() const
            {
                return arr_.empty();
            }

            config::size_type size() const
            {
                return arr_.size();
            }

            T top() const
            {
                utils::expect(!empty(), "Cannot obtain top element of empty heap");
                return arr_.front();
            }

            T pop_top()
            {
                T top = arr_.front();
                arr_.front() = arr_.back();
                arr_.pop_back();

                if(!arr_.empty())
                    propagate_downward(0);
                return top;
            }

            void add(const T& e)
            {
                arr_.push_back(e);
                propagate_upward(arr_.size()-1);
            }

        private:

            void propagate_upward(config::index_type idx)
            {
                while(idx != 0)
                {
                    auto parent_idx = (idx - 1) / 2;

                    if(Comp{}(arr_[parent_idx], arr_[idx]))
                        break;

                    std::swap(arr_[parent_idx], arr_[idx]);
                    idx = parent_idx;
                }
            }

            void propagate_downward(config::index_type idx)
            {
                while(idx != arr_.size()-1) {
                    auto left_child_idx = 2*idx + 1;
                    auto right_child_idx = 2*idx + 2;

                    if(left_child_idx > arr_.size()-1)
                        break;

                    auto min_child_idx = min_child(left_child_idx, right_child_idx);
                    if(Comp{}(arr_[idx], arr_[min_child_idx]))
                        break;

                    std::swap(arr_[idx], arr_[min_child_idx]);
                    idx = min_child_idx;
                }
            }

            config::index_type min_child(config::index_type left_child_idx, config::index_type right_child_idx) const
            {
                if(right_child_idx == arr_.size())
                    return left_child_idx;
                else
                    if(Comp{}(arr_[left_child_idx], arr_[right_child_idx]))
                        return left_child_idx;
                    else
                        return right_child_idx;
            }

            std::vector<T> arr_;

        };

        template<typename T, typename C>
        bool operator==(const heap<T,C>& lhs, const heap<T,C>& rhs)
        {
            return lhs.arr_ == rhs.arr_;
        }
        template<typename T, typename C>
        bool operator!=(const heap<T,C>& lhs, const heap<T,C>& rhs)
        {
            return !(lhs == rhs);
        }

        template<typename C, typename I>
        heap<typename I::value_type, C> heapify(I begin, I end)
        {
            heap<typename I::value_type, C> h;
            h.arr_.resize(std::distance(begin, end));
            std::copy(begin, end, h.arr_.begin());

            for(auto i = h.size()/2 - 1; i >= 0; --i)
                h.propagate_downward(i);

            return h;
        }

        template<typename I>
        auto build_min_heap(I begin, I end)
        {
            return heapify<std::less<typename I::value_type>>(begin, end);
        }
        template<typename I>
        auto build_max_heap(I begin, I end)
        {
            return heapify<std::greater<typename I::value_type>>(begin, end);
        }

    }

}