#include <windows.h>
#ifndef Field_H
#define Field_H
class Field {
private:
	HMENU Btn_ID;
	HWND hwnd;
	bool state;
public:
	Field(HMENU hMenu_t);
	void setHWND(HWND hwnd_t);
	void setState(bool state_t);

	HMENU getHMENU();
	HWND getHWND();
	bool getState();
};
#endif // !Field_H
