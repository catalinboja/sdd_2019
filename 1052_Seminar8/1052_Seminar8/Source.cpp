#include <malloc.h>
#include <stdio.h>
#include <string.h>

struct Message {
	char text[100];
	int priority;
};

struct maxHeap {
	Message* messages;
	int noMsg;
	int capacity;
};

maxHeap createHeap(int initialSize) {
	maxHeap heap;
	heap.messages = (Message*)malloc(initialSize * sizeof(Message));
	heap.noMsg = 0;
	heap.capacity = initialSize;

	return heap;
}

int getParent(int index) {
	return (index - 1) / 2;
}

int getLeftChild(int index) {
	return index * 2 + 1;
}

int getRightChild(int index) {
	return (index + 1) * 2;
}

void swap(maxHeap heap, int index1, int index2) {
	Message temp = heap.messages[index1];
	heap.messages[index1] = heap.messages[index2];
	heap.messages[index2] = temp;
}

void resize(maxHeap& heap) {
	Message* newArray = (Message*)malloc(heap.capacity * 2 * sizeof(Message));
	for (int i = 0; i < heap.noMsg; i++)
		newArray[i] = heap.messages[i];
	free(heap.messages);
	heap.messages = newArray;
	heap.capacity *= 2;	
}

void insert(maxHeap& heap, Message newMessage) {
	if (heap.noMsg == heap.capacity)
		resize(heap);

	heap.messages[heap.noMsg] = newMessage;
	int currentIndex = heap.noMsg;
	heap.noMsg += 1;

	while (currentIndex != 0) {
		int parentIndex = getParent(currentIndex);
		if (heap.messages[parentIndex].priority < newMessage.priority) {
			swap(heap, parentIndex, currentIndex);
			currentIndex = parentIndex;
		}
		else
			break;
	}
}

Message createMesage(int priority, const char* text) {
	Message newMessage;
	strcpy(newMessage.text, text);
	newMessage.priority = priority;
	return newMessage;
}

int main() {
	Message m1 = createMesage(1, "Hello");
	Message m2 = createMesage(100, "You need to pay the bill");
	Message m3 = createMesage(3, "Call your mom");
	Message m4 = createMesage(1000, "Plug your phone");
	Message m5 = createMesage(2000, "Prepare for exams");

	maxHeap heap = createHeap(100);
	insert(heap, m1);
	insert(heap, m2);
	insert(heap, m3);
	insert(heap, m4);
	insert(heap, m5);

	printf("Maximum priority message is %s", heap.messages[0].text);

}