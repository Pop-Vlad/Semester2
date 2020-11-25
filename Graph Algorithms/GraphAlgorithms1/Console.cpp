#include "Console.h"



Console::Console(Graph* graph) {
	this->graph = graph;
}


Console::~Console() {
	delete this->graph;
}


void Console::printMenu() {
	char string_to_print[] = "\n"
		"count vertices -> get the number of vertices\n"
		"parse vertices -> parse (iterate) the set of vertices\n"
		"is edge - <source> <destination> -> find if there is an edge from the source to the destination\n"
		"degree out - <source> -> get the out degree of a specified vertex\n"
		"degree in - <destination> -> get the in degree of a specified vertex\n"
		"parse outbound - <source> -> parse (iterate) the set of outbound edges of a specified vertex\n"
		"parse inbound - <destination> -> parse the set of inbound edges of a specified vertex\n"
		"get cost - <source> <destination> -> obtain the cost of an edge\n"
		"set cost - <source> <destination> <new weight> -> modify the cost of an edge\n"
		"add edge - <source> <destination> <cost> -> add a new edge\n"
		"remove edge - <source> <destination> -> remove a specified edge\n"
		"add vertex <vertex_id> -> add a new vertex\n"
		"remove vertex <vertex_id> -> remove a specified vertex\n"
		"copy -> create an exact copy of a graph, the original can be modified independently of its copy\n\n";
	 cout << string_to_print;
}


void Console::run() {
	char command[20];
	char parameter1[10];
	char parameter2[10];
	char parameter3[10];
	while (true) {
		this->printMenu();
		try {

			this->readCommand(command, parameter1, parameter2, parameter3);
			//cout << command << "|" << parameter1 << "|" << parameter2 << "|" << parameter3 << "\n";

			if (strcmp(command, "count vertices") == 0) {
				cout << this->graph->getNumberOfNodes() << "\n";
			}
			else if (strcmp(command, "parse vertices") == 0) {
				char buffer[100000];
				this->graph->parseNodes(buffer);
				cout << buffer;
			}
			else if (strcmp(command, "is edge") == 0) {
				cout << this->graph->checkEdge(parameter1, parameter2) << "\n";
			}
			else if (strcmp(command, "degree out") == 0) {
				cout << this->graph->getOutDegree(parameter1) << "\n";
			}
			else if (strcmp(command, "degree in") == 0) {
				cout << this->graph->getInDegree(parameter1) << "\n";
			}
			else if (strcmp(command, "parse outbound") == 0) {
				char buffer[100000];
				this->graph->parseEdgesOut(buffer, parameter1);
				cout << buffer;
			}
			else if (strcmp(command, "parse inbound") == 0) {
				char buffer[100000];
				this->graph->parseEdgesIn(buffer, parameter1);
				cout << buffer;
			}
			else if (strcmp(command, "get cost") == 0) {
				cout << this->graph->getEdgeWeight(parameter1, parameter2) << "\n";
			}
			else if (strcmp(command, "set cost") == 0) {
				this->graph->setEdgeWeight(parameter1, parameter2, parameter3);
				cout << "Cost set\n";
			}
			else if (strcmp(command, "add edge") == 0) {
				this->graph->addEdge(parameter1, parameter2, parameter3);
				cout << "Edge added\n";
			}
			else if (strcmp(command, "remove edge") == 0) {
				this->graph->removeEdge(parameter1, parameter2);
				cout << "Edge removed\n";
			}
			else if (strcmp(command, "add vertex") == 0) {
				this->graph->addNode(parameter1);
				cout << "Vertex added\n";
			}
			else if (strcmp(command, "remove vertex") == 0) {
				this->graph->removeNode(parameter1);
				cout << "Vertex removed\n";
			}
			else if (strcmp(command, "copy ") == 0) {
				Graph* graph_copy = this->graph->copy();
				cout << "Graph copied\n";
			}
			else if (strcmp(command, "exit ") == 0) {
				break;
			}
			else {
				cout << "Unrecognised command!\n";
			}
		}
		catch (NodeNotFound) {
			cout << "Node not found\n";
		}
		catch (NodeAlreadyExists) {
			cout << "Node already exists\n";
		}
		catch (EdgeNotFound) {
			cout << "Edge not found\n";
		}
		catch (EdgeAlreadyExists) {
			cout << "Edge already exists\n";
		}
		catch (IntegerError) {
			cout << "Expected an integer\n";
		}
		catch (exception&) {
			cout << "An error occured\n";
		}
	}
}


void Console::readCommand(char command[], char parameter1[], char parameter2[], char parameter3[]) {
	char keyboard_input[50];
	char delimiters[] = " -";
	char parts[5][10] = { NULL };
	char* token;
	int i = 0;
	
	cout << ">>>";
	gets_s(keyboard_input);

	token = strtok(keyboard_input, delimiters);
	while (token != NULL && i < 5) {
		strcpy(parts[i], token);
		i++;
		token = strtok(NULL, delimiters);
	}

	strcpy(command, parts[0]);
	strcat(command, " ");
	strcat(command, parts[1]);
	strcpy(parameter1, parts[2]);
	strcpy(parameter2, parts[3]);
	strcpy(parameter3, parts[4]);
}