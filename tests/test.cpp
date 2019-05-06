#include <gtest/gtest.h>
#include "../include/graph.h"
#include "../include/djikstra.h"

TEST(avl_test, test1) {
    std::vector<std::vector<std::pair<int, int>>> gr;
    gr.resize(3);
    gr[0].push_back(std::make_pair(1, 1));
    gr[0].push_back(std::make_pair(2, 1));
    gr[1].push_back(std::make_pair(2, 1));
    Graph<int> g(gr);
    std::vector <int> ans = Djikstra_avl(g, 0);
    EXPECT_EQ(1, ans[2]);
}

TEST(rb_test, test1) {
    Graph<int> g(3);
    std::vector <int> ans = Djikstra_rb(g, 0);
    EXPECT_EQ(1000000, ans[2]);
}

TEST(heap_test, test1) {
    std::vector<std::vector<std::pair<int, int>>> gr;
    gr.resize(3);
    gr[0].push_back(std::make_pair(1, 1));
    gr[0].push_back(std::make_pair(2, 1));
    gr[1].push_back(std::make_pair(2, 1));
    Graph<int> g(gr);
    std::vector <int> ans = Djikstra_heap(g, 0, 2);
    EXPECT_EQ(1, ans[2]);
}

TEST(heap_test, test2) {
    std::vector<std::vector<std::pair<int, int>>> gr;
    gr.resize(3);
    gr[0].push_back(std::make_pair(1, 1));
    gr[0].push_back(std::make_pair(2, 1));
    gr[1].push_back(std::make_pair(2, 1));
    Graph<int> g(gr);
    std::vector <int> ans = Djikstra_heap(g, 0, 3);
    EXPECT_EQ(1, ans[2]);
}
