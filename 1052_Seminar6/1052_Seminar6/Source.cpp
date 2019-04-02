#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Node {
	char text[100];
	Node* next;
	Node* prev;
};

struct TextHistory {
	Node* head;
	char session[100];
	Node* lastChange;
};

Node* createDLNode(const char* text) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (text == NULL)
		newNode->text[0] = '\0';
	else
		strcpy(newNode->text, text);
	newNode->next = newNode->prev = NULL;
	return newNode;
}

TextHistory openNewSession(const char* textFileName){
	TextHistory textHistory;
	textHistory.lastChange = NULL;

	if (textFileName == NULL)
		strcpy(textHistory.session, "Untitled.txt");
	else
		strcpy(textHistory.session, textFileName);
	textHistory.head = NULL;

	return textHistory;
}

void insertNewText(TextHistory& history, const char* newText) {
	Node* newNode = createDLNode(newText);
	history.lastChange = newNode;

	if (history.head == NULL) {
		history.head = newNode;
	}
	else
	{
		//traverse the list
		Node *current = history.head;
		for (; current->next != NULL; current = current->next) {
			;;;;;;;;;;;;;;;;;;;;;
		}

		//link the new node
		current->next = newNode;
		newNode->prev = current;
	}
}

void printHistory(TextHistory history) {
	if (history.head == NULL)
	{
		printf("\n No changes for %s", history.session);
	}
	else
	{
		printf("\n Changes for %s", history.session);
		Node* current = history.head;
		while (current != NULL) {
			printf("\n Change: %s", current->text);
			current = current->next;
		}
	}
}

void clearHistory(TextHistory& history) {

	if (history.head == NULL)
		return;

	//delete from end to head
	//move on the last node
	Node* current = history.head;
	for (; current->next != NULL; current = current->next);

	Node* prevFromCurrent = current->prev;
	while (prevFromCurrent != NULL) {
		free(current);
		current = prevFromCurrent;
		prevFromCurrent = current->prev;
	}

	history.head = NULL;
	history.lastChange = NULL;
}

const char* ctrlZ(TextHistory& history) {

	//leaking memory
	char* result = (char*)malloc(100);

	if (history.lastChange == NULL) {
		strcpy(result, "No more changes");
		history.lastChange = history.head;
	}
	else {
		strcpy(result, history.lastChange->text);
		history.lastChange = history.lastChange->prev;
	}

	return result;
}

const char* ctrlY(TextHistory& history) {

	//leaking memory
	char* result = (char*)malloc(100);

	if (history.lastChange == NULL) {
		strcpy(result, "No more additions");
	}
	else {
		strcpy(result, history.lastChange->text);
		if(history.lastChange->next!=NULL)
			history.lastChange = history.lastChange->next;
	}

	return result;
}

void main() {
	TextHistory notepad = openNewSession("DS subject1.txt");

	insertNewText(notepad, "Subject 1");
	insertNewText(notepad, "Student name: ___________");
	insertNewText(notepad, "Implement the next requirements.");

	printHistory(notepad);

	printf("\n Recover last change: %s", ctrlZ(notepad));
	printf("\n Recover last change: %s", ctrlZ(notepad));
	printf("\n Recover last change: %s", ctrlZ(notepad));
	printf("\n Recover last change: %s", ctrlZ(notepad));
	printf("\n Redo last change: %s", ctrlY(notepad));
	printf("\n Redo last change: %s", ctrlY(notepad));

	clearHistory(notepad);
	printHistory(notepad);
}