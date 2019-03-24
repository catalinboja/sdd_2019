#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct message {
	char text[100];
	int priority;
};

struct node {
	message msg;
	node* next;
};

struct RingBuffer {
	node* head;
	node* tail;
	int capacity;			//no of initial nodes
	int noNodes;			//no of used nodes
};

node* createNode(char* text, int priority) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->next = NULL;
	if (text != NULL) {
		strcpy(newNode->msg.text, text);
	}
	else
		newNode->msg.text[0] = '\0';
	newNode->msg.priority = priority;

	return newNode;
}

//the size should be > 0 
RingBuffer createRingBuffer(int initialSize) {
	RingBuffer ringBuffer;
	ringBuffer.head = NULL;
	ringBuffer.tail = NULL;

	if (initialSize > 0) {
		ringBuffer.capacity = initialSize;
		ringBuffer.noNodes = 0;
		for (int i = 0; i < initialSize; i++) {
			node *newNode = createNode(NULL, 0);
			newNode->next = ringBuffer.head;
			ringBuffer.head = newNode;
			ringBuffer.tail = newNode;
		}
	}
	else
	{
		ringBuffer.capacity = 0;
		ringBuffer.noNodes = 0;
	}

	return ringBuffer;
}

void printRingBuffer(RingBuffer ringBuffer) {
	printf("\n The buffer is using %d out of %d elements",
		ringBuffer.noNodes, ringBuffer.capacity);
	printf("\n The values are: ");
	node* currentNode = ringBuffer.head;
	for (int i = 0; i < ringBuffer.noNodes; i++) {
		printf("Message[%d] - %s", currentNode->msg.priority,
			currentNode->msg.text);
		currentNode = currentNode->next;
	}
}

void insertMessage(RingBuffer& ringBuffer, message msg) {

	if (ringBuffer.capacity == 0) {
		node* newNode = createNode(msg.text, msg.priority);
		ringBuffer.capacity += 1;
		ringBuffer.noNodes += 1;
		ringBuffer.tail = ringBuffer.head = newNode;
		return;
	}

	if (ringBuffer.capacity == ringBuffer.noNodes) {
		node* newNode = createNode(msg.text, msg.priority);
		ringBuffer.tail->next = newNode;
		ringBuffer.tail = newNode;
		ringBuffer.capacity += 1;
		ringBuffer.noNodes += 1;
	}
	else if(ringBuffer.noNodes>0) {
		//node* nextToTail = ringBuffer.tail->next;

		strcpy(ringBuffer.tail->next->msg.text, msg.text);
		ringBuffer.tail->next->msg.priority = msg.priority;
		ringBuffer.noNodes += 1;
		ringBuffer.tail = ringBuffer.tail->next;
	}
	else { //empty ring buffer
		//the tail and the head are poiting to the same node
		node* initialNode = ringBuffer.tail;
		strcpy(initialNode->msg.text, msg.text);
		initialNode->msg.priority = msg.priority;
		ringBuffer.noNodes += 1;
	}
}

int main() {
	RingBuffer importantMessages = createRingBuffer(1000);
	RingBuffer logs = createRingBuffer(0);

	message msg1 = { "This is a test",1 };
	message msg2 = { "This is an important test",200 };

	insertMessage(importantMessages, msg1);
	insertMessage(importantMessages, msg2);

	insertMessage(logs, msg1);
	insertMessage(logs, msg2);

	printRingBuffer(importantMessages);
	printRingBuffer(logs);
}