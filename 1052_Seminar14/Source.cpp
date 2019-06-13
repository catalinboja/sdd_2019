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

		fclose(pf);
	}
}