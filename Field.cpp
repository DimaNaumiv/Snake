#include "Field.h"
#include <windows.h>
Field::Field(HMENU hMenu_t) {
	Field::Btn_ID = hMenu_t;
	Field::hwnd = NULL;
	Field::state = false;
}
void Field::setHWND(HWND hwnd_t) {
	Field::hwnd = hwnd_t;
}
void Field::setState(bool state_t) {
	Field::state = state_t;
}

HMENU Field::getHMENU() {
	return Field::Btn_ID;
}
HWND Field::getHWND() {
	return Field::hwnd;
}
bool Field::getState() {
	return Field::state;
}