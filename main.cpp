#include <windows.h>
#include <vector>
#include "ItemIds.h"
#include <thread>
#include "Field.h"
#include "Snake.h"
#include "Fruit.h"
#include <list>
#include <algorithm>

HWND StartBtn = NULL;

std::vector<Field>field;
HWND ghwnd = NULL;
HINSTANCE ghInstance = NULL;

Snake snake = Snake();
Fruit fruit = Fruit();

int section_x = 0;
int section_y = 0;

int this_section = 9999;

void creatfield() {
	field.push_back(Field((HMENU)BTN1_ID));
	field.push_back(Field((HMENU)BTN2_ID));
	field.push_back(Field((HMENU)BTN3_ID));
	field.push_back(Field((HMENU)BTN4_ID));
	field.push_back(Field((HMENU)BTN5_ID));

	field.push_back(Field((HMENU)BTN6_ID));
	field.push_back(Field((HMENU)BTN7_ID));
	field.push_back(Field((HMENU)BTN8_ID));
	field.push_back(Field((HMENU)BTN9_ID));
	field.push_back(Field((HMENU)BTN10_ID));

	field.push_back(Field((HMENU)BTN11_ID));
	field.push_back(Field((HMENU)BTN12_ID));
	field.push_back(Field((HMENU)BTN13_ID));
	field.push_back(Field((HMENU)BTN14_ID));
	field.push_back(Field((HMENU)BTN15_ID));

	field.push_back(Field((HMENU)BTN16_ID));
	field.push_back(Field((HMENU)BTN17_ID));
	field.push_back(Field((HMENU)BTN18_ID));
	field.push_back(Field((HMENU)BTN19_ID));
	field.push_back(Field((HMENU)BTN20_ID));

	field.push_back(Field((HMENU)BTN21_ID));
	field.push_back(Field((HMENU)BTN22_ID));
	field.push_back(Field((HMENU)BTN23_ID));
	field.push_back(Field((HMENU)BTN24_ID));
	field.push_back(Field((HMENU)BTN25_ID));
}
void showField(Field  i) {
	HWND section = NULL;
	section = CreateWindowExW(0,L"Static",L"",WS_CHILD|WS_VISIBLE|SS_OWNERDRAW,section_x,section_y,50,50,ghwnd,i.getHMENU(),ghInstance,NULL);
	if (section == NULL) {
		MessageBox(0,L"fail create section in field",L"Error",MB_OK);
	}
	else {
		i.setHWND(section);
	}
}

void findSection(HMENU id) {
	for (int i = 0; i < field.size(); i++) {
		if (id == field[i].getHMENU()) {
			this_section = i;
			break;
		}
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam) {
	switch (uMsg) {
	 case WM_DESTROY: {
		 PostQuitMessage(0);
		 return 0;
		}
	 case WM_CREATE: {
		 return 0;
	 }
	 case WM_COMMAND: {
		 if (LOWORD(wParam) == StartBTN_ID) {
			 field[0].setState(true);
			 snake.setHead(0);
			 SetTimer(hwnd,GAMETIMER,1000,NULL);
			 InvalidateRect(field[0].getHWND(),NULL,NULL);
			 DestroyWindow(StartBtn);
			 StartBtn = NULL;
		 }
		 return 0;
	 }
	 case WM_DRAWITEM: {
		 LPDRAWITEMSTRUCT ipdis = (LPDRAWITEMSTRUCT)lParam;

		 if (ipdis->CtlID == StartBTN_ID) {
			 HPEN pen = CreatePen(PS_SOLID,4,RGB(0,0,0));
			 HBRUSH brush = CreateSolidBrush(RGB(0,255,0));

			 HPEN hOldPen = (HPEN)SelectObject(ipdis->hDC, pen);
			 HBRUSH hOldBrush = (HBRUSH)SelectObject(ipdis->hDC,brush);

			 Rectangle(ipdis->hDC,ipdis->rcItem.left, ipdis->rcItem.top, ipdis->rcItem.right, ipdis->rcItem.bottom);

			 SelectObject(ipdis->hDC,hOldPen);
			 SelectObject(ipdis->hDC, hOldBrush);
			 DeleteObject(pen);
			 DeleteObject(brush);

			 wchar_t Text[255];
			 GetWindowText(ipdis->hwndItem,Text,_countof(Text));
			 SetTextColor(ipdis->hDC,RGB(0,0,0));
			 SetBkMode(ipdis->hDC, TRANSPARENT);
			 DrawText(ipdis->hDC,Text,-1, &ipdis->rcItem, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		 }
		 else {
			 HPEN pen = CreatePen(PS_SOLID,2,RGB(0,0,0));
			 HBRUSH brush = CreateSolidBrush(RGB(0,0,255));

			 HPEN hOldPen = (HPEN)SelectObject(ipdis->hDC,pen);
			 HBRUSH hOldBrush = (HBRUSH)SelectObject(ipdis->hDC, brush);

			 Rectangle(ipdis->hDC,ipdis->rcItem.left, ipdis->rcItem.top, ipdis->rcItem.right, ipdis->rcItem.bottom);
			 
			 SelectObject(ipdis->hDC,hOldPen);
			 SelectObject(ipdis->hDC, hOldBrush);
			 DeleteObject(pen);
			 DeleteObject(brush);
			 findSection((HMENU)ipdis->CtlID);
			 if (this_section != 9999) {
				 if (field[this_section].getState() == true) {
					 HBRUSH brush = CreateSolidBrush(RGB(255,0,0));
					 RECT rect = {};
					 rect.left = ipdis->rcItem.left + 17;
					 rect.top = ipdis->rcItem.top + 17;
					 rect.right = ipdis->rcItem.right - 17;
					 rect.bottom = ipdis->rcItem.bottom - 17;

					 FillRect(ipdis->hDC, &rect, brush);
					 DeleteObject(brush);
				 }
				 else if(field[this_section].getState() == false) {
					 HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
					 RECT rect = {};
					 rect.left = ipdis->rcItem.left + 17;
					 rect.top = ipdis->rcItem.top + 17;
					 rect.right = ipdis->rcItem.right - 17;
					 rect.bottom = ipdis->rcItem.bottom - 17;

					 FillRect(ipdis->hDC, &rect, brush);
					 DeleteObject(brush);
				 }
				 if (this_section == fruit.getlocation()) {
					 HBRUSH brush = CreateSolidBrush(RGB(255, 255, 0));
					 RECT rect = {};
					 rect.left = ipdis->rcItem.left + 17;
					 rect.top = ipdis->rcItem.top + 17;
					 rect.right = ipdis->rcItem.right - 17;
					 rect.bottom = ipdis->rcItem.bottom - 17;

					 FillRect(ipdis->hDC, &rect, brush);
					 DeleteObject(brush);
				 }
				 this_section = 9999;
			 }
		 }
		 return TRUE;
	 }
	 case WM_KEYDOWN: {
		 switch (wParam) {
		 case 'W':
			 if (snake.getWay() != 2) {
				 snake.setWay(0);
			 }
			 break;
		 case 'D':
			 if (snake.getWay() != 3) {
				 snake.setWay(1);
			 }
			 break;
		 case 'S':
			 if (snake.getWay() != 0) {
				 snake.setWay(2);
			 }
			 break;
		 case 'A':
			 if (snake.getWay() != 1) {
				 snake.setWay(3);
			 }
			 break;
		 }
		 return 0;
	 }
	 case WM_TIMER: {
		 if (wParam == GAMETIMER) {
			 int head = snake.getHead();
			 field[head].setState(false);
			 InvalidateRect(field[head].getHWND(),NULL,NULL);

			 if (snake.getSize() != -1) {
				 std::list<int> body = snake.getBody();
				 std::for_each(body.begin(), body.end(), [](int i) {field[i].setState(false); InvalidateRect(field[i].getHWND(), NULL, NULL); });
			 }


			 bool xy = false;
			 if (snake.getWay() == 0) {
				 if (head - 5 >head%10%5-1) {
					 head = head - 5;
				 }
				 else {
					 head = head % 10 + 20;
				 }
			 }
			 else if (snake.getWay() == 1) {
				 if ((head + 1) % 5 == 0) {
					 head = head - 4;
				 }
				 else {
					 head = head + 1;
				 }
			 }
			 else if (snake.getWay() == 2) {
				 int max = head % 10 + 21;
				 if (head + 5 < max) {
					 head = head + 5;
				 }
				 else {
					 head = head % 10;
				 }
			 }
			 else if (snake.getWay() == 3) {
				 if ((head + 1) % 5 == 1) {
					 head = head + 4;
				 }
				 else {
					 head = head - 1;
				 }
			 }

			 if (head == fruit.getlocation()) {
				 fruit.setlocation(field);
				 snake.eatfruit(head);
				 if (snake.getSize() == 24) {
					 KillTimer(hwnd,GAMETIMER);
					 MessageBox(0,L"you won",L"Message",MB_OK);
					 PostQuitMessage(0);
				 }
			 }
			 std::list<int>::iterator it;
			 std::list<int> bb = snake.getBody();
			 bool tf = false;
			 for (it = bb.begin(); it != bb.end(); it++) {
				 if (*it == head) {
					 tf = true;
					 break;
				 }
			 }
			 if (tf == true) {
				 KillTimer(hwnd,GAMETIMER);
				 MessageBox(0,L"you lose",L"Message",MB_OK);
				 PostQuitMessage(0);
			 }

			 field[head].setState(true);

			 if (snake.getSize() > -1) {
				 snake.AddBody(head);
				 if (snake.getSize() + 1 < snake.getBody().size()-1) {
					 snake.DelBody();
				 }
				 
				 std::list<int> body = snake.getBody();
				 std::for_each(body.begin(), body.end(), [](int i) {field[i].setState(true); InvalidateRect(field[i].getHWND(), NULL, NULL); });
			 }

			 InvalidateRect(field[head].getHWND(),NULL,NULL);
			 snake.setHead(head);
		 }
	 }
	}
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE PrewInstance,LPSTR CmdLine,int CmdShow) {
	std::thread stream = std::thread(creatfield);
	wchar_t CLASS_NAME[] = L"MyWindow";
	WNDCLASS wc = {};
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = CLASS_NAME;
	if (!RegisterClass(&wc)) {
		MessageBox(0,L"Class didnt create",L"Error",MB_OK);
	}
	HWND hwnd = CreateWindow(CLASS_NAME,L"Snake",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,500,500,NULL,NULL,hInstance,NULL);
	if (hwnd == NULL) {
		MessageBox(0,L"window error",L"Error",MB_OK);
	}
	if (stream.joinable() == true) {
		stream.join();
	}
	ghwnd = hwnd;
	ghInstance = hInstance;
	section_x = 105;
	section_y = -20;
	for (int i = 0; i < field.size(); i++) {
		if (i % 5 == 0) {
			section_x = 105;
			section_y = section_y + 50;
		}
		else {
			section_x = section_x + 50;
		}
		showField(field[i]);
	}

	StartBtn = CreateWindowEx(0,L"Button",L"Start",WS_CHILD|WS_VISIBLE |WS_TABSTOP | BS_OWNERDRAW,165,350,130,70,hwnd,(HMENU)StartBTN_ID,hInstance,NULL);
	if (StartBtn == NULL) {
		MessageBox(0,L"Fail create start btn",L"Error",MB_OK);
	}

	HWND HTEXT = CreateWindowEx(0,L"Static",L"W-UP\nD-RIGHT\nS-DOWN\nA-LEFT",WS_CHILD|WS_VISIBLE,400,125,60,68,hwnd,(HMENU)HELPTEXT,hInstance,NULL);
	if (HTEXT == NULL) {
		MessageBox(0, L"Fail create help text", L"Error", MB_OK);
	}

	ShowWindow(hwnd,CmdShow);

	MSG Msg = {};
	while (GetMessage(&Msg,NULL,0,0)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}