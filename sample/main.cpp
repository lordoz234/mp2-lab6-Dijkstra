#include "../include/graph.h"
#include "../include/djikstra.h"

int main() {
	Graph<double> vl(3);
	std::cin >> vl;
	std::vector <double> ans = Djikstra_avl(vl, 1);
    return 0;
}
