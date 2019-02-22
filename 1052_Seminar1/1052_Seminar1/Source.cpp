#include <stdio.h>

void main() {

	int vb1 = 10;
	int vb2 = 20;
	double vb3 = 100.2;
	char  vb4 = 'a';
	char vb5 = 48;

	//NOT ALLOWED
	//vb4 = 'b';

	//TRY 1
	//&vb5 = &vb4;
	//vb5++;

	//TRY2
	char* vb6 = &vb4;
	(*vb6)++;

	printf("\n vb4 = %c", vb4);

	//TRY3
	char* addressVb1 = (char*)&vb1;
	int delta = &vb4 - (char*)&vb1;
	printf("\n memory jump is %d", delta);
	addressVb1 += delta;
	*addressVb1 = 'a';
	printf("\n vb4 = %c", vb4);

	//TRY 4
	char* addressVb01 = (char*)&vb1;
	addressVb01 -= 37;
	*addressVb01 = 'x';
	printf("\n vb4 = %c", vb4);
}