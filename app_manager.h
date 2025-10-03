#pragma once
#include "myLine.h"
#include "winFunc.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string>
using namespace std;

class app_manager {
private:
    int velocity;
    int length;
    bool epilepsy;
    int consoleWidth;
    int consoleHeight;

    int generateY();
    void getArguments();
    void startMove();
    void showHelp();

public:
    app_manager();
    app_manager(int argc, char* argv[]);
};