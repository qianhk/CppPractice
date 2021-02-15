//
// Created by KaiKai on 2021/1/16.
//

#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include "ModernCpp/modernMain.h"
#include "UseMathFunctions/useMathMain.h"
#include "WinApi/usewinapi.h"

int _tmain(int argc, char *argv[]) {

//    setlocale(LC_ALL, "UTF-8");
    setlocale(LC_ALL, "zh_CN.UTF-8");

    system("chcp 65001 > nul");

    mainModerns();

    mainUseMath(argc, argv);

    mainUseWinApi(argc, argv);

    return 0;
}
