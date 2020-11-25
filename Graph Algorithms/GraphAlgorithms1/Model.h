#pragma once

#include <vector>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <exception>
#include <string>

using namespace std;



class Graph {


private:

	char file_name[20];
	int number_of_nodes;
	int number_of_edges;
	std::vector<int> nodes;
	std::map<int, vector<int>*> outbound_edges;
	std::map<int, vector<int>*> inbound_edges;
	std::map<pair<int, int>, int> edges_weights;

	void loadGraph();

	void saveGraph();


public:

	Graph(char* file_name);

	~Graph();

	int getNumberOfNodes();

	void parseNodes(char* buffer);

	bool checkEdge(char* source, char* destination);

	int getEdgeWeight(char* source, char* destination);

	void setEdgeWeight(char* source, char* destination, char* new_value);

	int getOutDegree(char* node);

	int getInDegree(char* node);

	void parseEdgesOut(char* buffer, char* node);

	void parseEdgesIn(char* buffer, char* node);

	void addEdge(char* source, char* destination, char* weight);

	void removeEdge(char* source, char* destination);

	void addNode(char* source);

	void removeNode(char* node);

	Graph* copy();


};


class NodeNotFound : exception {

};


class NodeAlreadyExists : exception {

};


class EdgeNotFound : exception {

};


class EdgeAlreadyExists : exception {

};


class IntegerError : exception {

};