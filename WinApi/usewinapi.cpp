//
// Created by tianc on 2021/2/15.
//

#include "usewinapi.h"
#include <shlobj.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <iostream>

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "shlwapi.lib")

//HRESULT SHGetKnownFolderPath(REFKNOWNFOLDERID rfid, DWORD dwFlags, HANDLE hToken, PWSTR *ppszPath);

int mainUseWinApi(int argc, char *argv[]) {
    PWSTR path;
    HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, 0, &path);
//    HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamedTileImages, 0, 0, &path);
    char *patha = "abc中文123";
    path = L"abc中文123";
    path = L"abc\u4E2D\u6587123";
    if (result == S_OK) {
//        std::wcout << "lookKai GetKnownFolderPath success:" << path << std::endl;
        wprintf(L"lookKai w GetKnownFolderPath success: %ls\n", path);
        printf("lookKai GetKnownFolderPath success: %s\n", path);
    } else {
//        std::wcout << "lookKai GetKnownFolderPath failed:" << result << std::endl;
        wprintf(L"lookKai w GetKnownFolderPath failed: %lu\n", result);
        printf("lookKai GetKnownFolderPath failed: \lu\n", result);
    }
    return 0;
}
