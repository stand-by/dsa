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

        template<typename W, typename... Args>
        void dijkstra_shortest_path(bst::adjacency_list<Args...>& graph, const W& weight_map,
                typename bst::adjacency_list<Args...>::vertex_descriptor source)
        {
            using descriptor_t = typename bst::adjacency_list<Args...>::vertex_descriptor;

            auto comp = [&graph](descriptor_t left, descriptor_t right){ return graph[left].distance > graph[right].distance; };
            std::priority_queue<descriptor_t, std::vector<descriptor_t>, decltype(comp)> min_pq{comp};

            min_pq.push(source);
            graph[min_pq.top()].distance = 0;

            while(!min_pq.empty())
            {
                auto current = min_pq.top();
                min_pq.pop();

                if(graph[current].visited)
                    continue;
                else
                    graph[current].visited = true;

                for(auto [edge_it, end] = bst::out_edges(current, graph); edge_it != end; ++edge_it)
                {
                    auto neighbour = bst::target(*edge_it, graph);
                    if(!graph[neighbour].visited)
                    {
                        auto dist = weight_map[*edge_it] + graph[current].distance;

                        if (graph[neighbour].distance > dist) {
                            graph[neighbour].distance = dist;
                            graph[neighbour].predecessor = current;
                            min_pq.push(neighbour);
                        }
                    }
                }
            }
        }

        template<typename... Args>
        auto backtrace_shortest_path(const bst::adjacency_list<Args...>& graph, typename bst::adjacency_list<Args...>::vertex_descriptor endpoint)
        {
            std::vector<typename bst::adjacency_list<Args...>::vertex_descriptor> path;
            auto current = endpoint;

            while(graph[current].distance != 0 && graph[current].predecessor != -1)
            {
                path.push_back(current);
                current = graph[current].predecessor;
            }
            path.push_back(current);

            return path;
        }

    }

}