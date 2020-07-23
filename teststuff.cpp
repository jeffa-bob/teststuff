// teststuff.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <wincon.h>
#include <tuple>
#include <WinUser.h>
#include <consoleapi.h>
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
				SetConsoleScreenBufferSize(console, g);
}

HANDLE makenewbuff(SECURITY_ATTRIBUTES* sectur) {
				HANDLE consolescreen = CreateConsoleScreenBuffer(GENERIC_ALL, FILE_SHARE_WRITE, sectur, CONSOLE_TEXTMODE_BUFFER, NULL);
				SetConsoleTitleA("3D");
				SetConsoleMode(consolescreen, (DWORD)ENABLE_EXTENDED_FLAGS);
				SetConsoleMode(consolescreen, (DWORD)ENABLE_VIRTUAL_TERMINAL_PROCESSING);
				SetConsoleMode(consolescreen, (DWORD)DISABLE_NEWLINE_AUTO_RETURN);
				return consolescreen;
}

void preparescreenbuffer(tuple<short, short, short> pixels[600][800])
{
				SECURITY_ATTRIBUTES sectur;
				sectur.bInheritHandle = true;
				sectur.lpSecurityDescriptor = NULL;
				sectur.nLength = sizeof(sectur);
				HANDLE consolescreen = makenewbuff(&sectur);
				SetConsoleActiveScreenBuffer(consolescreen);
				HANDLE stdOUT = GetStdHandle(STD_OUTPUT_HANDLE);
				auto fontsize = makefontsize((short)0, (short)1);
				SetCurrentConsoleFontEx(stdOUT, FALSE, &fontsize);
				changesize(800, 600);
				COORD consolesize = getrowcolumnlength();
				for (int i = 0; i < consolesize.Y; i++) {
								DWORD x;
								FillConsoleOutputCharacter(consolescreen,(TCHAR)219,(DWORD)consolesize.X,{(short)i,(short)0},&x);
								//GetWindowRect(GetConsoleWindow(), &consolesize);
								for (int j = 0; j < consolesize.X; j++) {
												FillConsoleOutputAttribute(consolescreen,(WORD)FOREGROUND_BLUE,(DWORD)1,{(short)i,(short)j},&x);
								 }
				}
}

int main() {
				tuple<short,short,short> pixels[600][800];
}