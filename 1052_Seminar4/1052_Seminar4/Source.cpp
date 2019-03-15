#include <stdio.h>
#include <malloc.h>

struct Array {
	int *values = NULL;
	int no = 0;
};

struct ListNode {
	int value;
	ListNode* next = NULL;
};

struct List {
	//listNode* nodes;
	//int no;

	ListNode* listHead;
};

//function that creates an array with a given size
Array createArrayWithNSize(int n) {
	Array result;
	result.values = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		result.values[i] = i + 1;
	result.no = n;
	return result;
}

//function that prints an array
void printArray(Array array) {
	if (array.no == 0)
		printf("\n The array is empty");
	else
	{
		printf("\nThe array values are: ");
		for (int i = 0; i < array.no; i++)
			printf(" %d", array.values[i]);
	}
}

//function that creates and inits a single list node
ListNode* createListNode(int value) {
	ListNode* node;
	node = (ListNode*)malloc(1 * sizeof(ListNode));
	node->value = value;
	node->next = NULL;
	return node;
}

//function that creates a list with a given size
List createListWithNSize(int n) {
	List list;
	list.listHead = NULL;

	for (int i = n; i > 0; i--) {
		//create each node and init it
		ListNode* current = createListNode(i);
		//link the new node to the existing head
		current->next = list.listHead;
		//change the head
		list.listHead = current;
	}
	return list;
}

void printList(List list) {
	if (list.listHead == NULL)
		printf("\n The list is empty !");
	else
		for (ListNode *node = list.listHead;
			node != NULL;
			node = node->next) {
		printf("\n The node list value is %d", node->value);
	}
}

//function inserts a node at the end
List insertNodeAtTheEnd(List list, int newValue) {
	ListNode* newNode = createListNode(newValue);

	if (list.listHead == NULL) {
		list.listHead = newNode;
		return list;
	}

	//position on the last node
	ListNode* current = list.listHead;
	while (current->next != NULL)
		current = current->next;
	current->next = newNode;
	return list;
}

int main() {
	
	Array array = createArrayWithNSize(5);
	printArray(array);

	List list = createListWithNSize(5);
	printList(list);
	printf("\n After insert");
	list = insertNodeAtTheEnd(list,99);
	printList(list);
}