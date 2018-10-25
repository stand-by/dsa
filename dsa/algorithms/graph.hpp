#pragma once
#include <config.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace dsa
{

    namespace algorithms
    {

        namespace detail
        {

            template<typename C, typename F, typename... Args>
            void graph_traversal_impl(bst::adjacency_list<Args...>& graph, const F& traverse_func)
            {
                using descriptor_t = typename bst::adjacency_list<Args...>::vertex_descriptor;
                C cont;

                auto begin = *bst::vertices(graph).first;
                cont.push(begin);
                graph[begin].visited = true;

                while(!cont.empty())
                {
                    descriptor_t top;
                    if constexpr (std::is_same<C, std::stack<descriptor_t>>::value)
                        top = cont.top();
                    else
                        top = cont.front();
                    cont.pop();

                    bool stop = traverse_func(graph[top]);
                    if(stop)
                        break;

                    for(auto [edge_it, end] = bst::out_edges(top, graph); edge_it != end; ++edge_it)
                    {
                        auto tgt = bst::target(*edge_it, graph);
                        if(!graph[tgt].visited)
                        {
                            cont.push(tgt);
                            graph[tgt].visited = true;
                        }
                    }
                }
            }

        }

        template<typename F, typename... Args>
        void depth_first_traversal(bst::adjacency_list<Args...>& graph, const F& traverse_func)
        {
            using descriptor_t = typename bst::adjacency_list<Args...>::vertex_descriptor;
            using container_t = std::stack<descriptor_t>;
            detail::graph_traversal_impl<container_t>(graph,traverse_func);
        }

        template<typename F, typename... Args>
        void breadth_first_traversal(bst::adjacency_list<Args...>& graph, const F& traverse_func)
        {
            using descriptor_t = typename bst::adjacency_list<Args...>::vertex_descriptor;
            using container_t = std::queue<descriptor_t>;
            detail::graph_traversal_impl<container_t>(graph,traverse_func);
        }

    }

}