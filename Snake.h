#include <list>
#ifndef SNAKE_H
#define SNAKE_H
class Snake {
private:
	int way;
	int head;
	int size;
	std::list<int>body;
public:
	Snake();
	void setWay(int way_t);
	void eatfruit(int i);
	void AddBody(int i);
	int getWay();
	std::list<int> getBody();
	int getHead();
	void setHead(int head_t);
	int getSize();
	void DelBody();
};
#endif // !SNAKE_H
