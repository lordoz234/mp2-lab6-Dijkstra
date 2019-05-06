#ifndef _INCLUDE_DIJKSTRA_H
#define _INCLUDE_DIJKSTRA_H

#include "graph.h"
#include "avl_tree.h"
#include "RB_tree.h"
#include "heap.h"
#include <vector>

template <typename T>
std::vector <T> Djikstra_avl (Graph<T>& g, int start) {
	int n = g.get_size_graph();
	std::vector <T> d(n, 1000000);
    d[start] = 0;
    avl_tree<std::pair<T, int>> s;
    std::pair<T, int> st = {d[start], start};
    s.insert(st);
    while (!s.empty()) {
        std::pair<T, int> v1 = s.minimum();
        s.erase(v1);
        int v = v1.second;
        for (unsigned i = 0; i < g.graph[v].size(); i++) {
            int to = g.graph[v][i].first;
            T len = g.graph[v][i].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                std::pair<T, int> temp = {d[to], to};
                s.insert(temp);
            }
        }
        std::cout << std::endl;
    }
    return d;
} 

template <typename T>
std::vector <T> Djikstra_rb (Graph<T>& g, int start) {
	int n = g.get_size_graph();
	std::vector <T> d(n, 1000000);
    d[start] = 0;
    RBTree<std::pair<T, int>> s;
    std::pair<T, int> st = {d[start], start};
    s.insert(st);
    while (!s.empty()) {
        std::pair<T, int> v1 = s.minimum();
        s.erase(v1);
        int v = v1.second;
        for (unsigned i = 0; i < g.graph[v].size(); i++) {
            int to = g.graph[v][i].first;
            T len = g.graph[v][i].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                std::pair<T, int> temp = {d[to], to};
                s.insert(temp);
            }
        }
    }
    return d;
} 

template <typename T>
std::vector <T> Djikstra_heap (Graph<T>& g, int start, int k) {
	int n = g.get_size_graph();
	std::vector <T> d(n, 1000000);
    d[start] = 0;
    Heap<std::pair<T, int>> s(k);
    std::pair<T, int> st = {d[start], start};
    s.insert(st);
    while (s.getsize() != 0) {
        std::pair<T, int> v1 = s.minimum();
        int v = v1.second;
        for (unsigned i = 0; i < g.graph[v].size(); i++) {
            int to = g.graph[v][i].first;
            T len = g.graph[v][i].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                std::pair<T, int> temp = {d[to], to};
                s.insert(temp);
            }
        }
    }
    return d;
} 

#endif //_INCLUDE_DIJKSTRA_H