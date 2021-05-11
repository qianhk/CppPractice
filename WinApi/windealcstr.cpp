//
// Created by kaikai on 2021/3/9.
//

#include "windealcstr.h"
#include <iostream>
#include "DllFunc/library.h"

void invalidParameterErrorHandler(PCTSTR expression, PCTSTR function, PCTSTR file, unsigned int line , uintptr_t /*pReserved*/) {
    wprintf(L"invalidParameter expresion=%s func=%s file=%s line=%d\n"
            , expression, function, file, line);
}

void windeal_main() {
    _set_invalid_parameter_handler(invalidParameterErrorHandler);
    _CrtSetReportMode(_CRT_ASSERT, 0);

    hello();

    int tmpInt = gDllInt;
    gDllInt = 667;
    printf("windeal gDllInt=%d %d\n", tmpInt, gDllInt);

    PWSTR path;
    HRESULT result = getRoamingAppDataPath(&path);
    if (result == S_OK) {
        wprintf(L"lookKai invoke getKnownFolderPath success: %ls\n", path);
    } else {
        wprintf(L"lookKai invoke getKnownFolderPath failed: %lu\n", result);
    }
}