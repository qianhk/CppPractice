//
// Created by KaiKai on 2021/1/16.
//

#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include "ModernCpp/modernMain.h"
#include "UseMathFunctions/useMathMain.h"
#include "WinApi/usewinapi.h"
#include "DllFunc/library.h"

int _tmain(int argc, char *argv[]) {

//    setlocale(LC_ALL, "UTF-8");
    setlocale(LC_ALL, "zh_CN.UTF-8");

    system("chcp 65001 > nul");

    mainModerns();

    mainUseMath(argc, argv);

    mainUseWinApi(argc, argv);

    hello();

    PWSTR path;
    HRESULT result = getRoamingAppDataPath(&path);
    if (result == S_OK) {
        wprintf(L"lookKai invoke getKnownFolderPath success: %ls\n", path);
    } else {
        wprintf(L"lookKai invoke getKnownFolderPath failed: %lu\n", result);
    }

    return 0;
}
