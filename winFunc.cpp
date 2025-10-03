#include "winFunc.h"
#include <string>
#include <algorithm>

winFunc::winFunc() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void winFunc::cleanConsole() {
    system("cls");
}

void winFunc::changeCursor(bool visible) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = visible;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void winFunc::setConsoleSize(int width, int height) {
    consoleWidth = width;
    consoleHeight = height;
    // Для простоты используем system, но можно через Windows API
    string command = "mode con cols=" + to_string(width) + " lines=" + to_string(height);
    system(command.c_str());
}

void winFunc::setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

void winFunc::setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

int winFunc::getCsWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int winFunc::getCsHeight() {
    return consoleHeight;
}