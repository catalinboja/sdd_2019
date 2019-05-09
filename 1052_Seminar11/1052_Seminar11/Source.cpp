#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Student {
	int id;		//unique
	char* name;
	int noGrades;
	int* grades;
};

struct FileStudent {
	int id;
	char name[100];
	int noGrades;
	int grades[50];
};

struct BSTStudentNode {
	BSTStudentNode* left;
	BSTStudentNode* right;
	int key;
	int fileIndex; //the location of the student with id = key
};

BSTStudentNode* createNode(int key, int index) {
	BSTStudentNode* node = (BSTStudentNode*)malloc(sizeof(BSTStudentNode) * 1);
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	node->fileIndex = index;
	return node;
}

Student initStudent(int id, const char* name, int noGrades, int* grades) {
	Student student;
	student.id = id;
	student.noGrades = noGrades;
	student.name = (char*)malloc(strlen(name) + 1);
	strcpy(student.name, name);
	student.grades = (int*)malloc(sizeof(int) * noGrades);
	memcpy(student.grades, grades, sizeof(int) * noGrades);
	return student;
}

void printStudent(Student student) {
	printf("\n %s - %d with %d grades: ",
		student.name,student.id,student.noGrades);
	for (int i = 0; i < student.noGrades; i++)
		printf(" %d ", student.grades[i]);
}

void writeStudent2DirectAccessFile(Student student, FILE* pf) {
	if (pf != NULL) {
		//write the id
		fwrite(&student.id, sizeof(int), 1, pf);
		//write the name
		char buffer[100];
		strcpy(buffer, student.name);
		fwrite(buffer, sizeof(buffer), 1, pf);
		//write the grades
		fwrite(&student.noGrades, sizeof(int), 1, pf);
		int gradesBuffer[50];
		for (int i = 0; i < student.noGrades; i++)
			gradesBuffer[i] = student.grades[i];
		fwrite(gradesBuffer, sizeof(int), 50, pf);
	}
}

Student readStudentFromFile(const char* fileName, 
	int index, int recordSize) {

	Student student;
	student.id = -1;	//for checking later if the student exists

	FILE* pf = fopen(fileName, "rb");
	if (pf != NULL) {
		//check of the record exists
		fseek(pf, 0, SEEK_END);
		int fileSize = ftell(pf);
		int jumpSize = (index - 1)*recordSize;
		if (jumpSize < fileSize) {
			//make the jump
			fseek(pf, jumpSize, SEEK_SET);
			//read the student data
			FileStudent temp;
			fread(&temp, sizeof(FileStudent), 1, pf);
			student = initStudent(temp.id,
				temp.name, temp.noGrades, temp.grades);
		}
		fclose(pf);
	}

	return student;
}

void main() {
	int initialGrades[] = { 9,9,10 };
	Student stud1 = initStudent(10, "John", 3, initialGrades);
	Student stud2 = initStudent(202, "Alice", 3, initialGrades);
	Student stud3 = initStudent(3, "Bob", 3, initialGrades);

	printStudent(stud1);
	printStudent(stud2);
	printStudent(stud3);

	//save the students in binary direct access file
	FILE *pf = fopen("students.dat", "wb");
	if (pf != NULL) {
		writeStudent2DirectAccessFile(stud1, pf);
		writeStudent2DirectAccessFile(stud2, pf);
		writeStudent2DirectAccessFile(stud3, pf);
		fclose(pf);
	}

	//test reading from the file
	Student alice = readStudentFromFile("students.dat", 2, sizeof(FileStudent));
	printStudent(alice);

}