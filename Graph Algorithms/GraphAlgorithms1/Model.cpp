#include "Model.h"


Graph::Graph(char* file_name = NULL) {
	strcpy(this->file_name, file_name);
	this->number_of_nodes = 0;
	this->number_of_edges = 0;
	this->nodes.clear();
	this->outbound_edges.clear();
	this->inbound_edges.clear();
	this->edges_weights.clear();
	this->loadGraph();
}


Graph::~Graph() {
	this->nodes.clear();
	this->outbound_edges.clear();
	this->inbound_edges.clear();
	this->edges_weights.clear();
	delete this;
}


void Graph::loadGraph() {
	if (this->file_name != NULL) {
		fstream f(file_name);
		f >> this->number_of_nodes;
		f >> this->number_of_edges;
		for (int i = 0; i < number_of_nodes; i++) {
			this->nodes.push_back(i);
			this->outbound_edges[i] = new vector<int>;
			this->inbound_edges[i] = new vector<int>;
		}

		int source;
		int destination;
		int weight;
		pair<int, int> edge;
		for (int i = 0; i < number_of_edges; i++) {
			f >> source;
			f >> destination;
			f >> weight;
			this->outbound_edges[source]->push_back(destination);
			this->inbound_edges[destination]->push_back(source);
			edge.first = source;
			edge.second = destination;
			this->edges_weights[edge] = weight;
		}
	}
}

void Graph::saveGraph() {
	return;
}


int Graph::getNumberOfNodes() {
	return this->number_of_nodes;
}


void Graph::parseNodes(char* buffer) {
	strcpy(buffer, "");
	for (int i = 0; i < this->number_of_nodes; i++) {
		char current_node[20];
		itoa(this->nodes.at(i), current_node, 10);
		strcat(current_node, "\n");
		strcat(buffer, current_node);
	}
}


bool Graph::checkEdge(char* source, char* destination) {
	int source_int = atoi(source);
	int destination_int = atoi(destination);
	if (source_int == 0 && strcmp(source, "0") != 0) {
		return false;
	}
	if (destination_int == 0 && strcmp(destination, "0") != 0) {
		return false;
	}
	for (auto iterator = this->outbound_edges[source_int]->begin(); iterator != this->outbound_edges[source_int]->end(); iterator++) {
		if (*iterator == destination_int) {
			return true;
		}
	}
	return false;
}


int Graph::getEdgeWeight(char* source, char* destination) {
	if (!this->checkEdge(source, destination)) {
		throw EdgeNotFound();
	}
	int source_int = atoi(source);
	int destination_int = atoi(destination);
	pair<int, int> edge;
	edge.first = source_int;
	edge.second = destination_int;
	auto search_result = this->edges_weights.find(edge);
	return search_result->second;
}


void Graph::setEdgeWeight(char* source, char* destination, char* new_value) {
	if (!this->checkEdge(source, destination)) {
		throw EdgeNotFound();
	}
	int source_int = atoi(source);
	int destination_int = atoi(destination);
	int weight_int = atoi(new_value);
	if (weight_int == 0 && strcmp(new_value, "0") != 0) {
		throw IntegerError();
	}
	pair<int, int> edge;
	edge.first = source_int;
	edge.second = destination_int;
	this->edges_weights[edge] = weight_int;
}


int Graph::getOutDegree(char* node) {
	int node_int = atoi(node);
	if (node_int == 0 && strcmp(node, "0") != 0) {
		throw IntegerError();
	}
	return this->outbound_edges[node_int]->size();
}


int Graph::getInDegree(char* node) {
	int node_int = atoi(node);
	if (node_int == 0 && strcmp(node, "0") != 0) {
		throw IntegerError();
	}
	return this->inbound_edges[node_int]->size();
}


void Graph::parseEdgesOut(char* buffer, char* node) {
	int node_int = atoi(node);
	if (node_int == 0 && strcmp(node, "0") != 0) {
		throw IntegerError();
	}
	bool check = false;
	for (int i = 0; i < this->nodes.size(); i++) {
		if (this->nodes.at(i) == node_int) {
			check = true;
			break;
		}
	}
	if (check == false) {
		throw NodeNotFound();
	}
	strcpy(buffer, "");
	for (int i = 0; i < this->outbound_edges[node_int]->size(); i++) {
		char current_node[20];
		itoa(this->outbound_edges[node_int]->at(i), current_node, 10);
		strcat(current_node, "\n");
		strcat(buffer, current_node);
	}
}

void Graph::parseEdgesIn(char* buffer, char* node) {
	int node_int = atoi(node);
	if (node_int == 0 && strcmp(node, "0") != 0) {
		throw IntegerError();
	}
	bool check = false;
	for (int i = 0; i < this->nodes.size(); i++) {
		if (this->nodes.at(i) == node_int) {
			check = true;
			break;
		}
	}
	if (check == false) {
		throw NodeNotFound();
	}
	strcpy(buffer, "");
	for (int i = 0; i < this->inbound_edges[node_int]->size(); i++) {
		char current_node[20];
		itoa(this->inbound_edges[node_int]->at(i), current_node, 10);
		strcat(current_node, "\n");
		strcat(buffer, current_node);
	}
}

void Graph::addEdge(char* source, char* destination, char* weight) {
	if (this->checkEdge(source, destination)) {
		throw EdgeAlreadyExists();
	}
	int source_int = atoi(source);
	int destination_int = atoi(destination);
	int weight_int = atoi(weight);
	if (source_int == 0 && strcmp(source, "0") != 0) {
		throw IntegerError();
	}
	if (destination_int == 0 && strcmp(destination, "0") != 0) {
		throw IntegerError();
	}
	if (weight_int == 0 && strcmp(weight, "0") != 0) {
		throw IntegerError();
	}
	this->outbound_edges[source_int]->push_back(destination_int);
	this->inbound_edges[destination_int]->push_back(source_int);
	pair<int, int> edge;
	edge.first = source_int;
	edge.second = destination_int;
	this->edges_weights[edge] = weight_int;
}


void Graph::removeEdge(char* source, char* destination) {
	int source_int = atoi(source);
	int destination_int = atoi(destination);
	if (source_int == 0 && strcmp(source, "0") != 0) {
		throw IntegerError();
	}
	if (destination_int == 0 && strcmp(destination, "0") != 0) {
		throw IntegerError();
	}
	for (int i = 0; i < this->outbound_edges[source_int]->size(); i++) {
		if (this->outbound_edges[source_int]->at(i) == destination_int) {
			this->outbound_edges[source_int]->erase(this->outbound_edges[source_int]->begin() + i);
			break;
		}
	}
	for (int i = 0; i < this->inbound_edges[destination_int]->size(); i++) {
		if (this->inbound_edges[destination_int]->at(i) == source_int) {
			this->inbound_edges[destination_int]->erase(this->inbound_edges[destination_int]->begin() + i);
			break;
		}
	}
	pair<int, int> key;
	key.first = source_int;
	key.second = destination_int;
	this->edges_weights.erase(key);
	this->number_of_edges -= 1;
}


void Graph::addNode(char* node) {
	int node_int = atoi(node);
	if (node_int == 0 && strcmp(node, "0") != 0) {
		throw IntegerError();
	}
	this->number_of_nodes += 1;
	this->nodes.push_back(node_int);
	this->outbound_edges[node_int] = new vector<int>;
	this->inbound_edges[node_int] = new vector<int>;
}


void Graph::removeNode(char* node) {
	int node_int = atoi(node);
	if (node_int == 0 && strcmp(node, "0") != 0) {
		throw IntegerError();
	}
	for (auto iterator = this->outbound_edges[node_int]->begin(); iterator != this->outbound_edges[node_int]->end(); iterator++) {
		for (int i = 0; i < this->inbound_edges[*iterator]->size(); i++) {
			if (this->inbound_edges[*iterator]->at(i) == node_int) {
				this->inbound_edges[*iterator]->erase(this->inbound_edges[*iterator]->begin() + i);
				break;
			}
		}
		pair<int, int> key;
		key.first = node_int;
		key.second = *iterator;
		this->edges_weights.erase(key);
	}
	for (auto iterator = this->inbound_edges[node_int]->begin(); iterator != this->inbound_edges[node_int]->end(); iterator++) {
		for (int i = 0; i < this->outbound_edges[*iterator]->size(); i++) {
			if (this->outbound_edges[*iterator]->at(i) == node_int) {
				this->outbound_edges[*iterator]->erase(this->outbound_edges[*iterator]->begin() + i);
				break;
			}
		}
		pair<int, int> key;
		key.first = node_int;
		key.second = *iterator;
		this->edges_weights.erase(key);
	}
	this->outbound_edges.erase(node_int);
	this->inbound_edges.erase(node_int);
	for (int i = 0; i < this->nodes.size(); i++) {
		if (this->nodes.at(i) == node_int) {
			this->nodes.erase(this->nodes.begin() + i);
			break;
		}
	}
	this->number_of_nodes -= 1;
}


Graph* Graph::copy() {
	Graph* graph_copy = new Graph(this->file_name);
	graph_copy->number_of_nodes = this->number_of_nodes;
	graph_copy->number_of_edges = this->number_of_edges;
	graph_copy->nodes = this->nodes;
	graph_copy->outbound_edges = this->outbound_edges;
	graph_copy->inbound_edges = this->inbound_edges;
	graph_copy->edges_weights = this->edges_weights;

	return graph_copy;
}