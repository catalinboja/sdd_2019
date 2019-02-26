
#include <stdio.h>
#include <string.h>
#include <malloc.h>

enum Colors { red = 10, green = 20, blue = 30, yellow};

struct Product {
	unsigned int id;
	char* name;
	float price;
	Colors color;
};

void changeProductName(Product& p, const char* newName) {
	delete[] p.name;
	p.name = (char*)malloc(strlen(newName) + 1);
	strcpy(p.name, newName);
	p.price = 99;
}

void main() {
	Product p1;

	p1.id = 1;
	p1.price = 10;
	p1.color = Colors::red;
	p1.color = blue;
	// p1.name = "Gigel";
	// p1.name = (char*)"Gigel";
	//p1.name = new char[6] {"Doll"};
	p1.name = new char[strlen("Test")+1];
	strcpy(p1.name, "Test");

	printf("\n The product name is %s", p1.name);
	printf("\n The product price is %.2f", p1.price);

	changeProductName(p1, "Video game");

	printf("\n The product name is %s", p1.name);
	printf("\n The product price is %.2f", p1.price);

	//storing multiple products
	Product products[5];
	Product *multipleProducts;
	multipleProducts = new Product[5];

	//watch out for shallow-copy
	products[0] = p1;
	products[1] = p1;

	for(int i = 0; i < 2; i++)
		printf("\n The product name is %s", products[i].name);

	changeProductName(products[1], "RC Tank");

	for (int i = 0; i < 2; i++)
		printf("\n The product name is %s", products[i].name);
}