#include <stdio.h>
#include <string.h>
#include <malloc.h>

const int NO_LETTERS = 26;

struct dictionaryTreeNode {
	char letter;
	dictionaryTreeNode* nodes[NO_LETTERS];
	int noNodes;
};

struct Dictionary {
	dictionaryTreeNode* nodes[NO_LETTERS];
};

dictionaryTreeNode* createLetterNode(char letter) {
	dictionaryTreeNode* newNode =
		(dictionaryTreeNode*)malloc(sizeof(dictionaryTreeNode));
	for (int i = 0; i < NO_LETTERS; i++)
		newNode->nodes[i] = NULL;
	newNode->letter = letter;
	newNode->noNodes = 0;
	return newNode;
}

Dictionary initDictionary() {

	Dictionary dictionary;

	for (int i = 0; i < NO_LETTERS; i++) {
		dictionary.nodes[i] = createLetterNode('a'+i);
	}
}

int getLetterIndex(dictionaryTreeNode* currentNode, char letter) {
	for (int i = 0; i < currentNode->noNodes; i++)
		if (currentNode->nodes[i]->letter == letter)
			return i;
	return -1;
}

FILE* openFile(const char* fileName) {
	FILE *pf = fopen(fileName, "r");
	if (pf == NULL)
		printf("The file is not opened !");
	return pf;
}

bool isEnglishWord( char* line) {
	//check if it has only latin alphabet letters
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
	for (int i = 0; i < strlen(line); i++) {
		if (line[i] < 'A' ||
			(line[i] > 'Z' && line[i] < 'a') || line[i] > 'z')
			return false;
	}
	return true;
}

char* toSmallCaps(const char* word) {
	char* newWord = (char*)malloc(strlen(word) + 1);

	//we assume that contains only letters
	for (int i = 0; i < strlen(word); i++) {
		if (word[i] >= 'A' && word[i] <= 'Z')
			newWord[i] = word[i] + 32;
		else
			newWord[i] = word[i];
	}
	newWord[strlen(word)] = '\0';
	return newWord;
}

void main() {

	FILE* wordsFile = openFile("words.txt");
	if (wordsFile != NULL)
		printf("We have the file");

	char buffer[300];
	while (!feof(wordsFile)) {
		fgets(buffer, sizeof(buffer), wordsFile);
		if (isEnglishWord(buffer)) {
			char* lowerCase = toSmallCaps(buffer);
			printf("\nThe word is %s", lowerCase);
			free(lowerCase);
		}
	}

	if(wordsFile != NULL)
		fclose(wordsFile);

}