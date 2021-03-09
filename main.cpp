//
// Created by KaiKai on 2021/1/16.
//

#include <iostream>
#include <cstring>
#include "ModernCpp/modernMain.h"
#include "UseMathFunctions/useMathMain.h"

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

    std::cout << "sizeof(long)=" << sizeof(long) << std::endl; //win:4  mac:8
    std::cout << "sizeof(long long)=" << sizeof(long long) << std::endl;

#ifdef WIN32
    windeal_main();
#endif

    std::cout << "kaikai_test 01" << std::endl;

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
    destChars[2] = 'A' + rand() % 2;
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
//    system("pause");

    return 0;
}
