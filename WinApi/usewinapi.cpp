//
// Created by tianc on 2021/2/15.
//

#include "usewinapi.h"
#include <shlobj.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <iostream>
#include <wininet.h>
#include <direct.h>

#pragma comment( lib, "WinInet.lib" )
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "shlwapi.lib")

//HRESULT SHGetKnownFolderPath(REFKNOWNFOLDERID rfid, DWORD dwFlags, HANDLE hToken, PWSTR *ppszPath);

int mainUseWinApi(int argc, char *argv[]) {
    PWSTR path;
    HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, 0, &path);
//    HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamedTileImages, 0, 0, &path);
//    path = L"abc中文123";
//    path = L"abcd\u4E2D\u65871234";
    std::wstring wstr = L"abcdWstring中文defg";
    std::wcout << "lookKai wstr=" << wstr << std::endl;
    if (result == S_OK) {
        std::wcout << "lookKai wcout GetKnownFolderPath success:" << path << std::endl;
        wprintf(L"lookKai wprintf GetKnownFolderPath success: %ls\n", path);
//        printf("lookKai GetKnownFolderPath success: %s\n", path);
    } else {
//        std::wcout << "lookKai GetKnownFolderPath failed:" << result << std::endl;
        wprintf(L"lookKai w GetKnownFolderPath failed: %lu\n", result);
        printf("lookKai GetKnownFolderPath failed: %ld\n", result);
    }

    SYSTEM_INFO info{0};
    GetSystemInfo(&info);
    OSVERSIONINFOEX os{0};
    os.dwOSVersionInfoSize = sizeof(os);
    if (GetVersionEx((OSVERSIONINFO *) &os)) {
    } else {
        std::cout << "GetVersionEx failed=%ld\n" << GetLastError();
    }
    LPWSTR commandLine = GetCommandLine();
    int numArgs = 0;
    LPWSTR *cmdArgvs = CommandLineToArgvW(commandLine, &numArgs);
    LPWCH envStr = GetEnvironmentStrings();
    LPTSTR lpszVariable;
    for (lpszVariable = (LPTSTR) envStr; *lpszVariable; lpszVariable++) {
        int lineCount = wcslen(lpszVariable);
//        std::wcout << lpszVariable << std::endl;
        lpszVariable += lineCount;
//        while (*lpszVariable)
//            putchar(*lpszVariable++);
//        putchar('\n');
    }
    WCHAR envVar[MAX_PATH];
    DWORD dwResult = GetEnvironmentVariable(L"APPDATA", envVar, _countof(envVar));
    wprintf(L"GetEnvironmentVariable result=%u %ls\n", dwResult, envVar);
    ExpandEnvironmentStringsW(L"%USERPROFILE%/Test", envVar, _countof(envVar));
    wprintf(L"ExpandEnvironmentStringsW result=%u %ls\n", dwResult, envVar);
    _wchdir(L"c:\\temp");

    CONTEXT context{};
    context.ContextFlags = CONTEXT_FULL;
    GetThreadContext(GetCurrentThread(), &context);

    return 0;
}

void testInternetCrackUrl() {
    TCHAR scheme[1000];
    TCHAR hostName[1000];
    TCHAR userName[1000];
    TCHAR password[1000];
    TCHAR urlPath[1000];
    TCHAR extraInfo[1000];

    URL_COMPONENTS uc;
    memset(&uc, 0, sizeof(uc));
    uc.dwStructSize = sizeof(uc);

    uc.lpszScheme = scheme;
    uc.lpszHostName = hostName;
    uc.lpszUserName = userName;
//    uc.lpszPassword = password;
    uc.lpszUrlPath = urlPath;
    uc.lpszExtraInfo = extraInfo;

    uc.dwSchemeLength = _countof(scheme);
    uc.dwHostNameLength = _countof(hostName);
    uc.dwUserNameLength = _countof(userName);
//    uc.dwPasswordLength = _countof(password);
    uc.dwUrlPathLength = _countof(urlPath);
    uc.dwExtraInfoLength = _countof(extraInfo);

    PCWSTR testUrl = L"http://kai:pw@blog.csdn.net:8090/test/article/details/123456?id=123&name=kai2&key3=%41%61&key4=%%3";
    ::InternetCrackUrl(testUrl, wcslen(testUrl), ICU_DECODE, &uc);

    printf("scheme: '%ls'\n", uc.lpszScheme);
    printf("host name: '%ls'\n", uc.lpszHostName);
    printf("port: %d\n", uc.nPort);
    printf("user name: '%ls'\n", uc.lpszUserName);
    printf("password: '%ls'\n", uc.lpszPassword);
    printf("url path: '%ls'\n", uc.lpszUrlPath);
    printf("extra info: '%ls'\n", uc.lpszExtraInfo);

}

