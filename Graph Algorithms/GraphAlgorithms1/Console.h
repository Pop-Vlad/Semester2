#pragma once

#include <iostream>
#include <stdio.h>
#include <exception>
#include <string>

#include "Model.h"

using namespace std;



class Console {


private:

	Graph* graph;

	void printMenu();

	void readCommand(char command[], char parameter1[], char parameter2[], char parameter3[]);


public:

	Console(Graph* graph);

	~Console();

	void run();


};