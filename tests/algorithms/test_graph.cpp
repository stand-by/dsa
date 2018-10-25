#include <boost/test/unit_test.hpp>
#include <algorithms/graph.hpp>
#include <iostream>

using namespace dsa;

struct vertex_info
{
    int id = -1;
    bool visited = false;
};

auto setup_graph()
{
    typedef bst::adjacency_list<bst::vecS, bst::vecS,
                            bst::undirectedS,
                            vertex_info,
                            bst::no_property
                            > graph_t;
    graph_t g;

    auto v1 = bst::add_vertex({1},g);
    auto v2 = bst::add_vertex({2},g);
    auto v3 = bst::add_vertex({3},g);
    auto v4 = bst::add_vertex({4},g);
    auto v5 = bst::add_vertex({5},g);
    auto v6 = bst::add_vertex({6},g);
    auto v7 = bst::add_vertex({7},g);

    bst::add_edge(v1,v2,g);
    bst::add_edge(v1,v3,g);
    bst::add_edge(v1,v4,g);
    bst::add_edge(v2,v3,g);
    bst::add_edge(v3,v5,g);
    bst::add_edge(v5,v6,g);
    bst::add_edge(v4,v7,g);

    return g;
}

BOOST_AUTO_TEST_SUITE(test_graph_algorithms)

BOOST_AUTO_TEST_CASE(test_depth_first_traversal)
{
    //auto epair = bst::edges(g);
    //for(auto iter=epair.first; iter!=epair.second; iter++) {
    //   std::cout << g[source(*iter, g)].id << " - " << g[target(*iter, g)].id << std::endl;
    //}

    //auto gg = setup_graph();
    //auto print_v = [](const vertex_info& v){std::cout << v.id << std::endl; return false; };
    //algos::depth_first_traversal(gg,print_v);

    int n;
    bool res = false;
    auto found_n = [&n, &res](const vertex_info& v){ res = v.id == n ? true : false; return res; };

    auto g = setup_graph();
    n = 1;
    algos::depth_first_traversal(g,found_n);
    BOOST_CHECK(res);
    g = setup_graph();
    n = 2;
    algos::depth_first_traversal(g,found_n);
    BOOST_CHECK(res);
    g = setup_graph();
    n = 4;
    algos::depth_first_traversal(g,found_n);
    BOOST_CHECK(res);
    g = setup_graph();
    n = 3;
    algos::depth_first_traversal(g,found_n);
    BOOST_CHECK(res);
    g = setup_graph();
    n = 6;
    algos::depth_first_traversal(g,found_n);
    BOOST_CHECK(res);
    g = setup_graph();
    n = 10;
    algos::depth_first_traversal(g,found_n);
    BOOST_CHECK(res == false);
    g = setup_graph();
    n = 8;
    algos::depth_first_traversal(g,found_n);
    BOOST_CHECK(res == false);
    g = setup_graph();
    n = 0;
    algos::depth_first_traversal(g,found_n);
    BOOST_CHECK(res == false);
}

BOOST_AUTO_TEST_CASE(test_breadth_first_traversal)
{
    //auto gg = setup_graph();
    //auto print_v = [](const vertex_info& v){std::cout << v.id << std::endl; return false; };
    //algos::breadth_first_traversal(gg,print_v);

    int n;
    bool res = false;
    auto found_n = [&n, &res](const vertex_info& v){ res = v.id == n ? true : false; return res; };

    auto g = setup_graph();
    n = 1;
    algos::breadth_first_traversal(g,found_n);
    BOOST_CHECK(res);
    g = setup_graph();
    n = 2;
    algos::breadth_first_traversal(g,found_n);
    BOOST_CHECK(res);
    g = setup_graph();
    n = 4;
    algos::breadth_first_traversal(g,found_n);
    BOOST_CHECK(res);
    g = setup_graph();
    n = 3;
    algos::breadth_first_traversal(g,found_n);
    BOOST_CHECK(res);
    g = setup_graph();
    n = 6;
    algos::breadth_first_traversal(g,found_n);
    BOOST_CHECK(res);
    g = setup_graph();
    n = 10;
    algos::breadth_first_traversal(g,found_n);
    BOOST_CHECK(res == false);
    g = setup_graph();
    n = 8;
    algos::breadth_first_traversal(g,found_n);
    BOOST_CHECK(res == false);
    g = setup_graph();
    n = 0;
    algos::breadth_first_traversal(g,found_n);
    BOOST_CHECK(res == false);
}

BOOST_AUTO_TEST_SUITE_END()
