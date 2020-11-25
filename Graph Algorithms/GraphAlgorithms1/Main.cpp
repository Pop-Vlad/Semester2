#include <iostream>

#include "Console.h"

using namespace std;

int main() {
	char file_name[] = "graph.txt";
	Graph* graph = new Graph(file_name);
	Console* console = new Console(graph);
	console->run();
	return 0;
}