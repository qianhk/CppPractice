#ifndef CMAKEDLL_LIBRARY_H
#define CMAKEDLL_LIBRARY_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) void WINAPI hello();

__declspec(dllexport) HRESULT WINAPI getRoamingAppDataPath(PWSTR *ppszPath);

#ifdef __cplusplus
}
#endif

#endif //CMAKEDLL_LIBRARY_H
