#include "library.h"
#include <shlobj.h>
#include <shlwapi.h>
#include <iostream>

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "shlwapi.lib")

void hello() {
    std::cout << "Hello, World!" << std::endl;
}

//HRESULT SHGetKnownFolderPath(REFKNOWNFOLDERID rfid, DWORD dwFlags, HANDLE hToken, PWSTR *ppszPath);

HRESULT getRoamingAppDataPath(PWSTR *ppszPath) {
//    PWSTR path;
    HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, 0, ppszPath);
//    HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamedTileImages, 0, 0, &path);
//    char *patha = "abc中文123";
//    path = L"abc中文123";
//    path = L"abc\u4E2D\u6587123";
    if (result == S_OK) {
//        std::wcout << "lookKai GetKnownFolderPath success:" << path << std::endl;
        wprintf(L"lookKai w GetKnownFolderPath success: %ls\n", *ppszPath);
//        printf("lookKai GetKnownFolderPath success: %s\n", path);
    } else {
//        std::wcout << "lookKai GetKnownFolderPath failed:" << result << std::endl;
        wprintf(L"lookKai w GetKnownFolderPath failed: %lu\n", result);
//        printf("lookKai GetKnownFolderPath failed: \lu\n", result);
    }
    return result;
}

void onProcessAttach() {
    std::cout << "lookKai onProcessAttach" << std::endl;
    PWSTR path;
    getRoamingAppDataPath(&path);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            onProcessAttach();
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

