//
// Created by KaiKai on 2021/1/16.
//

#include <iostream>
#include <cstring>
#include <random>
#include "ModernCpp/modernMain.h"
#include "UseMathFunctions/useMathMain.h"
#include "ModernCpp/leftright.h"

#ifdef WIN32

#include <tchar.h>
#include "WinApi/windealcstr.h"
#include "WinApi/usewinapi.h"

#endif

#ifdef WIN32
int _tmain(int argc, char *argv[]) {
#else

int main(int argc, char *argv[]) {
#endif

//    setlocale(LC_ALL, "UTF-8");
//    setlocale(LC_ALL, "zh_CN.UTF-8");


//    system("chcp 65001 > nul");

//    system("pause");

#if defined(KAI_DLL_EXPORTS)
    std::cout << "in exe: defined KAI_DLL_EXPORTS\n";
#else
    std::cout << "in exe: not defined KAI_DLL_EXPORTS\n";
#endif

    std::cout << "sizeof(int)=" << sizeof(int) << std::endl; //win:4  mac:4
    std::cout << "sizeof(long)=" << sizeof(long) << std::endl; //win:4  mac:8
    std::cout << "sizeof(long long)=" << sizeof(long long) << std::endl; //win:8  mac:8

#ifdef WIN32
    windeal_main();
#endif

    std::cout << "kaikai_test 011" << std::endl;

    const char testChars[][16] = {"kaichars1", "kaikaiChars2", "kaikaikaiChars3", "kaikai04"};
    std::cout << testChars[2] << std::endl;
    size_t totalLen = sizeof(testChars);
    size_t itemLen = sizeof(testChars[0]);
    int szLen = (int) (totalLen / itemLen);
    printf("strLen0=%zu szLen=%d totalLen=%zu itemLen=%zu\n", strlen(testChars[0]), szLen, totalLen, itemLen);
    char destChars[16];
//    strcpy(destChars, "IamShei_abcdefghijklmnopqrstuvwxyz");
#ifdef WIN32
    //    errno_t tmpErrNo = strcpy_s(destChars, sizeof(destChars), "IamShei_abcdefghijklmnopqrstuvwxyz");
        errno_t tmpErrNo = strcpy_s(destChars, sizeof(destChars), "IamShei");
        std::cout << "lookKai strcpy_s errno_t=" << tmpErrNo << std::endl;
#else
    strncpy(destChars, "IamShei", sizeof(destChars));
#endif

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 10.0);
    std::uniform_int_distribution<int> dist2(0, 10);

    for (int i = 0; i < 10; ++i) {
        printf("random: float=%.4f int=%d\n", dist(mt), dist2(mt));
    }

    destChars[2] = (char)('A' + dist2(mt));
    int hasSame;
    for (int idx = 0; idx < szLen; ++idx) {
        hasSame = strcmp(destChars, testChars[idx]);
        if (hasSame == 0) {
            break;
        }
    }

    const wchar_t *testWchar = L"abc";
    wcslen(testWchar);
    int cmpResult = wcscmp(testWchar, L"def");
//    lstrcpy(testWchar, L"abc");
//    testWchar = L"def";
//    testWchar[1] = 'a';
    std::wcout << testWchar << hasSame << std::endl;

    mainModerns();
    mainUseMath(argc, argv);

#ifdef WIN32
    mainUseWinApi(argc, argv);
    testInternetCrackUrl();
#endif
    mainLeftRight();
//    system("pause");

    return 0;
}
