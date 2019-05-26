#include <gtest/gtest.h>
#include "../include/graph.h"
#include "../include/djikstra.h"

TEST(avl_test, test1) {
    Graph<int> g(3);
    g.graph[0].push_back(std::make_pair(1, 1));
    g.graph[0].push_back(std::make_pair(2, 1));
    g.graph[1].push_back(std::make_pair(2, 1));
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_avl(g, 0);
    EXPECT_EQ(1, t.first[2]);
}

TEST(rb_test, test1) {
    Graph<int> g(3);
    g.graph[0].push_back(std::make_pair(1, 1));
    g.graph[0].push_back(std::make_pair(2, 1));
    g.graph[1].push_back(std::make_pair(2, 1));
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_rb(g, 0);
    EXPECT_EQ(1, t.first[2]);
}

TEST(rb_test, test2) {
    Graph<int> g(3);
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_rb(g, 0);
    EXPECT_EQ(1000000, t.first[2]);
}

TEST(heap_test, test1) {
    Graph<int> g(3);
    g.graph[0].push_back(std::make_pair(1, 1));
    g.graph[0].push_back(std::make_pair(2, 1));
    g.graph[1].push_back(std::make_pair(2, 1));
    std::pair<std::vector <int>, std::vector <int>> t= Djikstra_heap(g, 0, 2);
    EXPECT_EQ(1, t.first[2]);
}

TEST(heap_test, test2) {
    Graph<int> g(3);
    g.graph[0].push_back(std::make_pair(1, 1));
    g.graph[0].push_back(std::make_pair(2, 1));
    g.graph[1].push_back(std::make_pair(2, 1));
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_heap(g, 0, 3);
    EXPECT_EQ(1, t.first[2]);
}

TEST(avl_test, test2) {
    Graph<double> g(3);
    g.graph[0].push_back(std::make_pair(1, 1.1));
    g.graph[0].push_back(std::make_pair(2, 1.2));
    g.graph[1].push_back(std::make_pair(2, 1.3));
    std::pair<std::vector <double>, std::vector <int>> t = Djikstra_avl(g, 0);
    EXPECT_EQ(1.2, t.first[2]);
}

TEST(rb_test, test3) {
    Graph<double> g(3);
    g.graph[0].push_back(std::make_pair(1, 1.1));
    g.graph[0].push_back(std::make_pair(2, 1.2));
    g.graph[1].push_back(std::make_pair(2, 1.3));
    std::pair<std::vector <double>, std::vector <int>> t = Djikstra_rb(g, 0);
    EXPECT_EQ(1.2, t.first[2]);
}

TEST(heap_test, test3) {
    Graph<double> g(3);
    g.graph[0].push_back(std::make_pair(1, 1.1));
    g.graph[0].push_back(std::make_pair(2, 1.2));
    g.graph[1].push_back(std::make_pair(2, 1.3));
    std::pair<std::vector <double>, std::vector <int>> t = Djikstra_heap(g, 0, 2);
    EXPECT_EQ(1.2, t.first[2]);
}

TEST(heap_test, test4) {
    Graph<double> g(3);
    g.graph[0].push_back(std::make_pair(1, 1.1));
    g.graph[0].push_back(std::make_pair(2, 1.2));
    g.graph[1].push_back(std::make_pair(2, 1.3));
    std::pair<std::vector <double>, std::vector <int>> t = Djikstra_heap(g, 0, 3);
    EXPECT_EQ(1.2, t.first[2]);
}

TEST(avl_test, test3) {
	Graph<int> g(3);
    g.graph[0].push_back(std::make_pair(2, 2));
    g.graph[1].push_back(std::make_pair(0, 3));
    g.graph[2].push_back(std::make_pair(1, 4));
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_avl(g, 0);
    EXPECT_EQ(6, t.first[1]);
}

TEST(br_test, test4) {
	Graph<int> g(3);
    g.graph[0].push_back(std::make_pair(2, 2));
    g.graph[1].push_back(std::make_pair(0, 3));
    g.graph[2].push_back(std::make_pair(1, 4));
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_rb(g, 0);
    EXPECT_EQ(6, t.first[1]);
}

TEST(heap_test, test5) {
	Graph<int> g(3);
    g.graph[0].push_back(std::make_pair(2, 2));
    g.graph[1].push_back(std::make_pair(0, 3));
    g.graph[2].push_back(std::make_pair(1, 4));
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_heap(g, 0, 2);
    EXPECT_EQ(6, t.first[1]);
}

TEST(heap_test, test6) {
	Graph<int> g(3);
    g.graph[0].push_back(std::make_pair(2, 2));
    g.graph[1].push_back(std::make_pair(0, 3));
    g.graph[2].push_back(std::make_pair(1, 4));
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_heap(g, 0, 4);
    EXPECT_EQ(6, t.first[1]);
}

TEST(avl_test, test5) {
	Graph<int> g(5);
    g.graph[0].push_back(std::make_pair(1, 2));
    g.graph[1].push_back(std::make_pair(4, 5));
    g.graph[1].push_back(std::make_pair(2, 4));
    g.graph[0].push_back(std::make_pair(3, 1));
    g.graph[3].push_back(std::make_pair(2, 3));
    g.graph[2].push_back(std::make_pair(4, 1));
    g.graph[1].push_back(std::make_pair(0, 2));
    g.graph[4].push_back(std::make_pair(1, 5));
    g.graph[2].push_back(std::make_pair(1, 4));
    g.graph[3].push_back(std::make_pair(0, 1));
    g.graph[2].push_back(std::make_pair(3, 3));
    g.graph[4].push_back(std::make_pair(2, 1));
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_avl(g, 0);
    EXPECT_EQ(5, t.first[4]);
}

TEST(rb_test, test6) {
	Graph<int> g(5);
    g.graph[0].push_back(std::make_pair(1, 2));
    g.graph[1].push_back(std::make_pair(4, 5));
    g.graph[1].push_back(std::make_pair(2, 4));
    g.graph[0].push_back(std::make_pair(3, 1));
    g.graph[3].push_back(std::make_pair(2, 3));
    g.graph[2].push_back(std::make_pair(4, 1));
    g.graph[1].push_back(std::make_pair(0, 2));
    g.graph[4].push_back(std::make_pair(1, 5));
    g.graph[2].push_back(std::make_pair(1, 4));
    g.graph[3].push_back(std::make_pair(0, 1));
    g.graph[2].push_back(std::make_pair(3, 3));
    g.graph[4].push_back(std::make_pair(2, 1));
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_rb(g, 0);
    EXPECT_EQ(5, t.first[4]);
}

TEST(heap_test, test8) {
	Graph<int> g(5);
    g.graph[0].push_back(std::make_pair(1, 2));
    g.graph[1].push_back(std::make_pair(4, 5));
    g.graph[1].push_back(std::make_pair(2, 4));
    g.graph[0].push_back(std::make_pair(3, 1));
    g.graph[3].push_back(std::make_pair(2, 3));
    g.graph[2].push_back(std::make_pair(4, 1));
    g.graph[1].push_back(std::make_pair(0, 2));
    g.graph[4].push_back(std::make_pair(1, 5));
    g.graph[2].push_back(std::make_pair(1, 4));
    g.graph[3].push_back(std::make_pair(0, 1));
    g.graph[2].push_back(std::make_pair(3, 3));
    g.graph[4].push_back(std::make_pair(2, 1));
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_heap(g, 0, 2);
    EXPECT_EQ(5, t.first[4]);
}

TEST(heap_test, test9) {
	Graph<int> g(5);
    g.graph[0].push_back(std::make_pair(1, 2));
    g.graph[1].push_back(std::make_pair(4, 5));
    g.graph[1].push_back(std::make_pair(2, 4));
    g.graph[0].push_back(std::make_pair(3, 1));
    g.graph[3].push_back(std::make_pair(2, 3));
    g.graph[2].push_back(std::make_pair(4, 1));
    g.graph[1].push_back(std::make_pair(0, 2));
    g.graph[4].push_back(std::make_pair(1, 5));
    g.graph[2].push_back(std::make_pair(1, 4));
    g.graph[3].push_back(std::make_pair(0, 1));
    g.graph[2].push_back(std::make_pair(3, 3));
    g.graph[4].push_back(std::make_pair(2, 1));
    std::pair<std::vector <int>, std::vector <int>> t = Djikstra_heap(g, 0, 3);
    EXPECT_EQ(5, t.first[4]);
}