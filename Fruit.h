#include <vector>
#include "Field.h"
#ifndef FRUIT_H
#define FRUIT_H
class Fruit {
private:
	int location;
public:
	Fruit();
	void setlocation(std::vector<Field> field);
	int getlocation();
};
#endif
