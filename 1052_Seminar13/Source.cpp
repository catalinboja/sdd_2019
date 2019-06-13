#include <stdio.h>
#include <malloc.h>
#include <string.h>




struct Student {
	int id;
	char name[100];
};

struct BSTNode {
	Student student;
	BSTNode *left;
	BSTNode* right;
};

Student initStudent(const char* name, int id) {
	Student student;
	student.id = id;
	strcpy(student.name, name);
	return student;
}

BSTNode* initNode(Student student) {
	BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
	newNode->left = newNode->right = NULL;
	newNode->student = initStudent(student.name, student.id);
	return newNode;
}

int getBalanceDegree(BSTNode* node);

BSTNode* insert(BSTNode* root, Student student) {
	if (root == NULL)
		return initNode(student);
	else
		if (root->student.id > student.id) {
			root->left = insert(root->left, student);
			//check the balance degree
			if (getBalanceDegree(root) == -2 || getBalanceDegree(root) == 2)
				printf("We have a major unbalance on %d", root->student.id);
		}
		else
			if (root->student.id < student.id) {
				root->right = insert(root->right, student);
				//check the balance degree
				if (getBalanceDegree(root) == -2 || getBalanceDegree(root) == 2)
					printf("We have a major unbalance on %d", root->student.id);
			}
			else
				return root;
	return root;
}

void inorderPrint(BSTNode* root) {
	if (root != NULL) {
		inorderPrint(root->left);
		printf("\n %d - %s", root->student.id, root->student.name);
		inorderPrint(root->right);
	}
}

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

//function that determines the height of a tree
int getHeight(BSTNode* root) {
	if (root == NULL)
		return 0;
	return 1 + max(getHeight(root->left), getHeight(root->right));
}

int getBalanceDegree(BSTNode* node) {
	if (node == NULL)
		return 0;
	return getHeight(node->left) - getHeight(node->right);
}

void simpleLeftRotation(BSTNode* pivot) {
	Student pivotValue = initStudent(pivot->student.name, pivot->student.id);

}

void main() {

	BSTNode* studentIndex = NULL;
	studentIndex = insert(studentIndex, { 3,"John"});
	studentIndex = insert(studentIndex, { 5,"Alice" });
	studentIndex = insert(studentIndex, { 1,"Bob" });
	studentIndex = insert(studentIndex, { 10,"Vader" });
	studentIndex = insert(studentIndex, { 100,"New Vader" });

	printf("The index height is %d", getHeight(studentIndex));
	
	inorderPrint(studentIndex);
}