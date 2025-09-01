#include "Snake.h"
#include <vector>
Snake::Snake() {
	Snake::way = 1;
	Snake::size = -1;
}
void Snake::eatfruit(int i) {
	Snake::size = Snake::size + 1;
}
void Snake::setWay(int way_t) {
	Snake::way = way_t;
}
int Snake::getWay() {
	return Snake::way;
}
std::list<int> Snake::getBody() {
	return Snake::body;
}
void Snake::setHead(int head_t) {
	Snake::head = head_t;
}
int Snake::getHead() {
	return Snake::head;
}
int Snake::getSize() {
	return Snake::size;
}
void Snake::AddBody(int i) {
	Snake::body.push_back(i);
}
void Snake::DelBody() {
	Snake::body.pop_front();
}