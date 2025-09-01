#include "Fruit.h"
#include <vector>
#include "Field.h"
#include <random>
Fruit::Fruit() {
	std::random_device rnum;
	Fruit::location = rnum() % 24 + 1;
}
int Fruit::getlocation() {
	return Fruit::location;
}
void Fruit::setlocation(std::vector<Field> field) {
	bool tf = false;
	std::random_device rnum;
	int num = rnum()%25;
	while (tf == false) {
		if (field[num].getState() == false) {
			break;
		}
	}
	Fruit::location = num;
}