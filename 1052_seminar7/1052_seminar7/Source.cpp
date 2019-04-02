#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Product {
	char name[50];
	float price;
	char barCode[50];
	int stock;
};

struct Node {
	Product product;
	Node* next;
};

struct HashTable {
	Node* *keyIndex;
	int noElements;
};

void initProduct(Product& product, const char* name,
	float price, const char* barCode, int stock);

int getHashValue(const char* barCode, int N) {
	int asciiCodesSum = 0;
	for (int i = 0; i < strlen(barCode); i++)
		asciiCodesSum += barCode[i];
	return asciiCodesSum % N;
}

Node* createProductNode(Product product) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	//works only for this structure - it doesn't have inner pointers
	newNode->product = product;
	newNode->next = NULL;
	return newNode;
}

Node* insertNewNode(Node* head, Product product) {
	Node* newProduct = createProductNode(product);
	newProduct->next = head;
	return newProduct;
}

Product searchProduct(Node* head, const char* barCode) {
	Product response;
	initProduct(response,"No product",0,"0000",0);
	if (head == NULL)
		return response;
	Node* iterator = head;
	while (iterator != NULL) {
		if (strcmp(iterator->product.barCode, barCode) == 0)
			return iterator->product;
		iterator = iterator->next;
	}
	return response;
}

HashTable createHashTable(int N) {
	HashTable hashTable;
	hashTable.noElements = N;
	hashTable.keyIndex = (Node**)malloc(N * sizeof(Node*));
	//init the pointers
	for (int i = 0; i < N; i++)
		hashTable.keyIndex[i] = NULL;
	return hashTable;
}

void insertProduct(HashTable hashTable, Product product) {
	//determin the index of the product based on its bar code
	int index = getHashValue(product.barCode, 
		hashTable.noElements);

	Node* list = hashTable.keyIndex[index];
	list = insertNewNode(list, product);
	hashTable.keyIndex[index] = list;
}

Product getProduct(HashTable hashTable, const char* barCode) {
	int index = getHashValue(barCode, hashTable.noElements);

	return searchProduct(hashTable.keyIndex[index],
		barCode);
}

void initProduct(Product& product, const char* name,
	float price, const char* barCode, int stock) {
	product.stock = stock;
	product.price = price;
	if (name != NULL) {
		strcpy(product.name, name);
	}
	else
		product.name[0] = '\0';
	if (barCode != NULL)
		strcpy(product.barCode, barCode);
	else
		product.barCode[0] = '\0';
}

void main() {
	HashTable myProductsTable = createHashTable(101);
	Product mirinda;
	initProduct(mirinda, "Mirinda", 2.4, "123abc567", 100);
	Product cola;
	initProduct(cola, "Cola", 2.9, "678fabc567", 100);

	insertProduct(myProductsTable, mirinda);
	insertProduct(myProductsTable, cola);

	printf("The price for cola is %f",
		getProduct(myProductsTable, "678fabc567").price);
}