#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct linkedNode;

struct mainNode{
	char cityName[100];
	linkedNode* linkedNodes;
	mainNode* next;
};

struct linkedNode {
	//char cityName[100];	//another way of implementing it
	mainNode* destination;
	linkedNode* next;
	int travelTime;
};

mainNode* initMainNode(const char* city) {
	mainNode* newCity = (mainNode*)malloc(sizeof(mainNode));
	newCity->linkedNodes = NULL;
	newCity->next = NULL;
	strcpy(newCity->cityName, city);
	return newCity;
}

linkedNode* initDestinationNode(mainNode* destination,
	int travelTime) {
	if (destination == NULL)
		return NULL;
	linkedNode* newLink = 
		(linkedNode*)malloc(sizeof(linkedNode));
	newLink->destination = destination;
	newLink->travelTime = travelTime;
	newLink->next = NULL;
	return newLink;
}

void addNewNode(mainNode*& head, const char* city) {
	mainNode* newNode = initMainNode(city);
	if (head == NULL)
		head = newNode;
	else
	{
		mainNode* temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNode;
	}
}

void pushLinkedNode(linkedNode*& head, 
	mainNode* neighbour, int travelTime) {
	linkedNode* newNode =
		initDestinationNode(neighbour, travelTime);
	if (newNode == NULL)
		return;
	newNode->next = head;
	head = newNode;
}

mainNode* searchCity(const char* city, mainNode* list) {
	if (list == NULL)
		return NULL;
	mainNode* temp = list;
	while (temp != NULL) {
		if (strcmp(city, temp->cityName) == 0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

//print neighbour nodes
void printNeighbours(const char* city, mainNode* graph){
	if (graph != NULL) {
		mainNode* cityNode = searchCity(city, graph);
		linkedNode* neighbours = cityNode->linkedNodes;
		while (neighbours != NULL) {
			printf("\n %s -> %s (%d)", city,
				neighbours->destination, neighbours->travelTime);
			neighbours = neighbours->next;
		}
	}
}

struct queueNode {
	mainNode* node;
	queueNode* next;
};

void addNode(queueNode*& node, mainNode* graphNode) {

	queueNode* newNode = (queueNode*)malloc(sizeof(queueNode));
	newNode->next = NULL;
	newNode->node = graphNode;

	if (node == NULL) {
		node = newNode;
	}
	else
	{
		queueNode *it = node;
		while (it->next != NULL)
			it = it->next;
		it->next = newNode;
	}
}

mainNode* getNode(queueNode*& list) {
	if (list == NULL)
		return NULL;
	else {
		queueNode* head = list;
		list = list->next;
		mainNode*  graphNode = head->node;
		free(head);
		return graphNode;
	}
}

bool isVisited(queueNode* visitedNodes, mainNode* city){
	if (visitedNodes == NULL)
		return false;
	else {
		queueNode* it = visitedNodes;
		while (it != NULL) {
			if (it->node == city)
				return true;
			it = it->next;
		}
		return false;
	}
}

void breathFirst(mainNode* graph) {
	if (graph == NULL)
		printf("\n NU exista graful");
	else
	{
		queueNode* availableNodes = NULL;
		queueNode* visitedNodes = NULL;

		//get current node
		mainNode* currentNode = graph;
		while (currentNode != NULL) {

			addNode(visitedNodes, currentNode);

			printf("We are in %s ", currentNode->cityName);
			//save all neighbours in a queue
			linkedNode* neighbour = currentNode->linkedNodes;
			while (neighbour != NULL) {
				//add only new nodes
				if (!isVisited(visitedNodes, neighbour->destination)) {
					addNode(availableNodes, neighbour->destination);
				}
				neighbour = neighbour->next;
			}
			mainNode* nextNodeToVisit = getNode(availableNodes);
			currentNode = nextNodeToVisit;
		}
	}
}

void heapInOrder(int* heap, int n, int childIndex) {
	if (childIndex < n) {
		heapInOrder(heap, n, childIndex * 2 + 1);
		printf("\n Current node %d", heap[childIndex]);
		heapInOrder(heap, n, childIndex * 2 + 2);
	}
}

void main() {
	FILE *pf = fopen("SpeedCourier.txt", "r");
	if (pf == NULL)
		printf("There is no file !!!");
	else
	{
		char buffer[100];
		fgets(buffer, 100, pf);
		int noCities = atoi(buffer);
		printf("We have %d nodes", noCities);
		//read all nodes
		mainNode* graph = NULL;
		for (int i = 0; i < noCities; i++)
		{
			fgets(buffer, 100, pf);
			//remove '\n
			buffer[strlen(buffer) - 1] = '\0';
			addNewNode(graph, buffer);
		}

		printf("\nWe have %s", 
			searchCity("Craiova", graph)->cityName);

		//read neighbour links
		while (!feof(pf)) {
			//read source city
			char source[100];
			fgets(source, 100, pf);
			source[strlen(source) - 1] = '\0';
			char destination[100];
			fgets(destination, 100, pf);
			destination[strlen(destination) - 1] = '\0';
			//read travel time
			fgets(buffer, 100, pf);
			int travelTime = atoi(buffer);

			//get source city node
			mainNode* sourceNode = searchCity(source, graph);
			if (sourceNode == NULL) {
				printf("\n !!!! Nu exista nodul %s", source);
			}
			else {
				linkedNode* linkedNodesList = sourceNode->linkedNodes;
				mainNode* destinationNode = searchCity(destination, graph);
				if (destinationNode == NULL) {
					printf("\n !!!! Nu exista nodul destinatie %s", destination);
				}
				else
				{
					pushLinkedNode(linkedNodesList, destinationNode, travelTime);
					sourceNode->linkedNodes = linkedNodesList;
				}
			}

		}

		fclose(pf);

		//print graph
		const char* cities[] = {"Bucharest","Ploiesti","Brasov","Craiova"};
		for (int i = 0; i < 4; i++) {
			printNeighbours(cities[i], graph);
		}

		printf("\n Afisare *****************");
		breathFirst(graph);
	}

	//heap traversal simulation
	int heap[] = { 100,50,80,30,40,70,75,3,7 };
	heapInOrder(heap, 9, 0);
}