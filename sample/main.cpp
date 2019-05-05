#include "../include/graph.h"
#include "../include/djikstra.h"

int main() {
	while (true) {
		std::cout << "Enter the number of vertex" << std::endl;
		int vertex;
		std::cin >> vertex;
		Graph<int> g(vertex);
		std::cout << "How do you want to set the graph" << std::endl;
		std::cout << "1. By hand" << std::endl;
		std::cout << "2. Automatic (random generation)" << std::endl;
		int a;
		std::cin >> a;
		if (a == 1) {
			std::cin >> g;
		}
		else {
			g.create();
		}
		std::cout << "If you want to see graph enter 1 otherwise 2:";
		int c;
		std::cin >> c;
		if (c == 1) {
			std::cout << g;
			std::cout << std::endl;
		}
		if (g.is_singularity() && g.is_edge_positive()) {
			std::cout << "The graph satisfies the constraints" << std::endl;
		}
		else {
			std::cout << "The graph does not satisfies the constraints" << std::endl;
			return 1;
		}
		std::cout << "Choose the struct for using Djikstra" << std::endl;
		std::cout << "1. AVL Tree" << std::endl;
		std::cout << "2. Red Black Tree" << std::endl;
		std::cout << "3. D-Heap" << std::endl;
		int b;
		std::cin >> b;
		if (b == 1) {
			std::cout << "Choose the starting vertex" << std::endl;
			int start;
			std::cin >> start;
			std::vector <int> ans = Djikstra_avl(g, start);
			std::cout << "Enter the end vertex" << std::endl;
			int end;
			std::cin >> end;
			std::cout << "The answer is " << ans[end] << std::endl;
		}
		else if (b == 2) {
			std::cout << "Enter the starting vertex" << std::endl;
			int start;
			std::cin >> start;
			std::vector <int> ans = Djikstra_rb(g, start);
			std::cout << "Choose the end vertex" << std::endl;
			int end;
			std::cin >> end;
			std::cout << "The answer is " << ans[end] << std::endl;
		}
		else {
			std::cout << "Enter the starting vertex" << std::endl;
			int start;
			std::cin >> start;
			std::cout << "Enter the D" << std::endl;
			int D;
			std::cin >> D;
			std::vector <int> ans = Djikstra_heap(g, start, D);
			std::cout << "Choose the end vertex" << std::endl;
			int end;
			std::cin >> end;
			std::cout << "The answer is " << ans[end] << std::endl;
		}
	}
    return 0;
}
