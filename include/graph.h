#ifndef _INCLUDE_GRAPH_H
#define _INCLUDE_GRAPH_H
#include <iostream>
#include <functional>
#include <vector>
#include <set>
#include <random>
#include <algorithm>

static auto rng = []{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    return rng;
}();

template <typename T,
          template<typename> class Distribution
                                      = std::uniform_int_distribution,
          typename... Args>
T Randolfi(Args&&... args)
{
    Distribution<T> dist(std::forward<Args>(args)...);
    return dist(rng);
}

template <typename T>
class Graph {
private:
	int vertex;
	template <typename U> friend std::istream& operator>> (std::istream &in, Graph<U> &g) {
		g.graph.resize(g.vertex);
		for (int i = 0; i < g.vertex; i++) {
			int x, y;
			U z;
			in >> x >> y >> z;
			g.graph[x].push_back(std::make_pair(y, z));
		}
		return in;
	};
	template <typename U> friend std::ostream& operator<< (std::ostream &out, const Graph<U> &g) {
		for (int i = 0; i < g.vertex; i++) {
			std::cout << i << ": ";
			for (unsigned j = 0; j < g.graph[i].size(); j++) {
				int to = g.graph[i][j].first;
				U len = g.graph[i][j].second;
				std::cout << to << "-" << len << " ";
			}
			std::cout << std::endl;
		}
		return out;
	};
public:
	std::vector <std::vector <std::pair<int, T>>> graph;
	Graph(int _vertex);
	bool is_singularity();
	bool is_edge_positive();
	void create ();
	int get_size_graph();
};

template <typename T>
int Graph<T>::get_size_graph() {
	return vertex;
}

template <typename T>
Graph<T>::Graph(int _vertex) {
	vertex = _vertex;
	graph.resize(vertex);
}

template <typename T>
bool Graph<T>::is_singularity() {
	std::vector <char> used(vertex);
	std::function<void(int)> dfs = [&] (int v) {
		used[v] = true;
		for (unsigned i = 0; i < graph[v].size(); i++) {
			int to = graph[v][i].first;
			if (!used[to]) {
				dfs(to);
			}
		}
    };
	for (int i = 0; i < vertex; i++) {
		used[i] = false;
	}
	int comp = 0;
	for (int i = 0; i < vertex; i++) {
		if (!used[i]) {
			dfs(i);
			comp++;
		}
	}
	if (comp == 1) {
		return true;
	} 
	else {
		return false;
	}
}

template <typename T>
bool Graph<T>::is_edge_positive() {
	for (int i = 0; i < vertex; i++) {
		for (unsigned j = 0; j < graph[i].size(); j++) {
			T len = graph[j][i];
			if (len < 0) {
				return false;
			}
		}
	}
	return true;
}

template <typename T>
void Graph<T>::create () {
	int n = vertex;
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n - 1);
    std::vector <int> parent;
	std::vector <int> rank1;
	std::vector <std::vector <int>> g;
    parent.resize(n);
    rank1.resize(n);
    g.resize(n);
    auto make_set = [&](int v) {
    	parent[v] = v;
    	rank1[v] = 0;
    };
    std::function<int(int)> find_set = [&](int v) {
    	if (v == parent[v]) {
    		return v;
    	}
    	return parent[v] = find_set(parent[v]);
    };
    auto unions = [&] (int a, int b) {
    	a = find_set(a);
    	b = find_set(b);
    	if (a != b) {
    		if (rank1[b] > rank1[a]) {
    			std::swap(a, b);
    		}
    		parent[b] = a;
    		if (rank1[a] == rank1[b]) {
    			++rank1[a];
    		}
    	} 
    };
    auto randoms = [&] (int n, int k) {
    	std::vector <int> a;
    	for (int i = 0; i < n; i++) {
    		a.push_back(i);
    	}
    	for (int i = 0; i < k; i++) {
    		next_permutation(a.begin(), a.end());
    	}
    	return a;
    };
    for (int i = 0; i < n; i++) {
        g[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        make_set(i);
    }
    std::vector <int> r = randoms(n, 15);
    std::vector <int> r2 = randoms(n, 19);
    for (int i = 0; i < r.size(); i++) {
        int k = dis(gen);
        int a = find_set(r[i]);
        int b = find_set(r2[k]);
        if (a != b) {
            g[r[i]][r2[k]] = 1;
            g[r2[k]][r[i]] = 1;
            unions(r[i], r2[k]);
        }
        else {
            std::set <int> temp;
            for (int i = 0; i < n; i++) {
                temp.insert(find_set(i));
            }
            if (temp.size() > 1) {
                i--;
            }
        }
    }
    int k = (n*(n - 1))/4 - (n - 1);
    for (int i = 0; i < k; i++) {
        int k = dis(gen);
        if (r[i] == r2[k]) {
            i--;
        }
        else {
            if (g[r[i]][r2[k]] == 0) {
                g[r[i]][r2[k]] = 1;
                g[r2[k]][r[i]] = 1;
                --k;
                if (k == 0) {;
                    break;
                }
            }
            else {
                i--;
            }
        }
    }
    graph.resize(n);
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		if (i != j) {
    			if (g[i][j] == 1) {
    				graph[i].push_back(std::make_pair(j, Randolfi<T>(0, 100)));
    			}
    		}
    	}
    }
}

#endif //_INCLUDE_GRAPH_H
