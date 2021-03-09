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

void invalidParameterErrorHandler(PCTSTR expression, PCTSTR function, PCTSTR file, unsigned int line , uintptr_t /*pReserved*/) {
    wprintf(L"invalidParameter expresion=%s func=%s file=%s line=%d\n"
            , expression, function, file, line);
}

int _tmain(int argc, char *argv[]) {

//    setlocale(LC_ALL, "UTF-8");
//    setlocale(LC_ALL, "zh_CN.UTF-8");
    _set_invalid_parameter_handler(invalidParameterErrorHandler);
    _CrtSetReportMode(_CRT_ASSERT, 0);

//    system("chcp 65001 > nul");

//    system("pause");

    std::cout << "sizeof(long)=" << sizeof(long) << std::endl;
    std::cout << "sizeof(long long)=" << sizeof(long long) << std::endl;

    std::cout << "kaikai_test 01" << std::endl;

    const char testChars[][16] = {"kaichars1", "kaikaiChars2", "kaikaikaiChars3", "kaikai04"};
    std::cout << testChars[2] << std::endl;
    size_t totalLen = sizeof(testChars);
    size_t itemLen = sizeof(testChars[0]);
    int szLen = totalLen / itemLen;
    printf("strLen0=%u szLen=%d totalLen=%u itemLen=%u\n", strlen(testChars[0]), szLen, totalLen, itemLen);
    char destChars[16];
//    strcpy(destChars, "IamShei_abcdefghijklmnopqrstuvwxyz");
//    try {
//    errno_t tmpErrNo = strcpy_s(destChars, sizeof(destChars), "IamShei_abcdefghijklmnopqrstuvwxyz");
    errno_t tmpErrNo = strcpy_s(destChars, sizeof(destChars), "IamShei");
//    } catch (...) {
//        std::cout << "strcpy_s exception\n";
//    }
    destChars[2] = 'A' + rand() % 2;
    int hasSame;
    for (int idx = 0; idx < szLen; ++idx) {
        hasSame = strcmp(destChars, testChars[idx]);
        if (hasSame == 0) {
            break;
        }
    }

    const PCWCHAR testWchar = L"abc";
    wcslen(testWchar);
    lstrlenW(testWchar);
    wcscmp(testWchar, L"def");
//    lstrcpy(testWchar, L"abc");
//    testWchar = L"def";
//    testWchar[1] = 'a';
    std::wcout << testWchar << hasSame << std::endl;

    mainModerns();

    mainUseMath(argc, argv);

    mainUseWinApi(argc, argv);

    testInternetCrackUrl();

    hello();

    PWSTR path;
    HRESULT result = getRoamingAppDataPath(&path);
    if (result == S_OK) {
        wprintf(L"lookKai invoke getKnownFolderPath success: %ls\n", path);
    } else {
        wprintf(L"lookKai invoke getKnownFolderPath failed: %lu\n", result);
    }

//    system("pause");

    return 0;
}
