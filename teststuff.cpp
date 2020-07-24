// teststuff.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <wincon.h>
#include <stdio.h>
#include <tuple>
#include <tchar.h>
#include <WinUser.h>
#include <consoleapi.h>
#include <map>
#include <cwchar>

using std::tuple;


CONSOLE_FONT_INFOEX makefontsize(short x, short y) {
				CONSOLE_FONT_INFOEX fontsize;
				fontsize.cbSize = sizeof(fontsize);
				fontsize.nFont = 0;
				fontsize.dwFontSize.X = x;
				fontsize.dwFontSize.Y = y;
				fontsize.FontFamily = FF_DONTCARE;
				fontsize.FontWeight = FW_NORMAL;
				wcscpy_s(fontsize.FaceName, L"Consolas");
				return fontsize;
}

COORD getrowcolumnlength() {
				CONSOLE_SCREEN_BUFFER_INFO consolesize;
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consolesize);
				return consolesize.dwSize;
}

void changesize(int x, int y) {
				HWND console = GetConsoleWindow();
				RECT r;
				GetWindowRect(console, &r); //stores the console's current dimensions
				COORD g = { x,y };
				//MoveWindow(window_handle, x, y, width, height, redraw_window);
				MoveWindow(console, r.left, r.top, x, y, TRUE);
				SetConsoleScreenBufferSize(console, {(short)x-(short)2,(short)y-(short)10});
}

HANDLE makenewbuff(SECURITY_ATTRIBUTES* sectur) {
				HANDLE consolescreen = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE, FILE_SHARE_WRITE, sectur, CONSOLE_TEXTMODE_BUFFER, NULL);
				SetConsoleTitleA("3D");
				SetConsoleMode(consolescreen, (DWORD)ENABLE_VIRTUAL_TERMINAL_PROCESSING);
				SetConsoleMode(consolescreen, (DWORD)DISABLE_NEWLINE_AUTO_RETURN);
    CONSOLE_CURSOR_INFO info;
				info.dwSize = 100;
				info.bVisible = FALSE;
				SetConsoleCursorInfo(consolescreen, &info);
				return consolescreen;
}

void disablemouseinputbuff() {
				HANDLE consolescreeninput = GetStdHandle(STD_INPUT_HANDLE);
				DWORD prev_mode;
				GetConsoleMode(consolescreeninput, &prev_mode);
				SetConsoleMode(consolescreeninput, (DWORD)ENABLE_EXTENDED_FLAGS |
								(prev_mode & ~ENABLE_QUICK_EDIT_MODE));
}

HANDLE preparescreenbuffer(SECURITY_ATTRIBUTES *sectur)
{			std::map<int,WORD> color = {{1,FOREGROUND_RED},{2,FOREGROUND_GREEN},{3,FOREGROUND_BLUE}};
				HANDLE consolescreen = makenewbuff(sectur);
				HANDLE stdOUT = GetStdHandle(STD_OUTPUT_HANDLE);
				CONSOLE_FONT_INFOEX fontsize = makefontsize((short)0, (short)18);
				disablemouseinputbuff();
				SetCurrentConsoleFontEx(stdOUT, FALSE, &fontsize);
				changesize(600, 600);
				COORD consolesize = getrowcolumnlength();
				DWORD x;
				for (int i = 0; i < (int)consolesize.Y; i++) {
								for (int j = 0; j < (int)consolesize.X; j++) {
												FillConsoleOutputCharacterA(consolescreen,219, (DWORD)600, { (short)i,(short)0 }, &x);
												FillConsoleOutputAttribute(consolescreen,FOREGROUND_GREEN|FOREGROUND_INTENSITY,(DWORD)1,{(short)i,(short)j},&x);
								 }
				}
				return consolescreen;
}

int main() {
				SECURITY_ATTRIBUTES sectur;
				sectur.bInheritHandle = true;
				sectur.lpSecurityDescriptor = NULL;
				sectur.nLength = sizeof(sectur);
				//tuple<short,short,short> pixels[600][800];
				HANDLE nextconscrbuf = preparescreenbuffer(&sectur);
				SetConsoleActiveScreenBuffer(nextconscrbuf);
				while(true){}
}