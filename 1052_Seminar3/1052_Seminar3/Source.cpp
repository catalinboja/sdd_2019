#include <stdio.h>
#include <string.h>

#pragma pack(1)

struct Laboratory {
	int number;
	int noChairs;
	char code;
	float temp;
	char buildingName[10];
};

union MinimizedLaboratory {
	int number;
	int noChairs;
	char code;
	float temp;
	char buildingName[10];
};

struct VerySmallLaboratory {

	unsigned int buildingNumber:4;
	unsigned int floorLevel : 3;
	unsigned int roomNumber : 5;
	unsigned int hasComputers : 1;
	unsigned int noChairs : 9;
};

int main() {
	Laboratory lab2016;
	MinimizedLaboratory minimal2016;

	printf("\n Sizeof of a Laboratory is %d", sizeof(lab2016));
	printf("\n Sizeof of a MinimizedLaboratory is %d", sizeof(minimal2016));

	lab2016.number = 2016;
	strcpy(lab2016.buildingName, "Madgearu");

	printf("\n The lab number is %d and the building is %s",
		lab2016.number, lab2016.buildingName);

	
	strcpy(minimal2016.buildingName, "Madgearu");
	minimal2016.number = 0x41414141;

	printf("\n The minimal lab number is %d and the building is %s",
		minimal2016.number, minimal2016.buildingName);

	VerySmallLaboratory verySmall2016;
	printf("\n Sizeof of a VerySmallLaboratory is %d", sizeof(verySmall2016));

	verySmall2016.floorLevel = 0;
	verySmall2016.buildingNumber = 2;
	verySmall2016.roomNumber = 16;
	
	printf("\n The minimal lab number is %d and the floor is %d",
		verySmall2016.roomNumber, verySmall2016.floorLevel);

}