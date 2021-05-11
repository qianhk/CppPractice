#ifndef CMAKEDLL_LIBRARY_H
#define CMAKEDLL_LIBRARY_H

#include <Windows.h>


#ifdef KAI_DLL_EXPORTS
#define KAI_DECLSPEC_API __declspec(dllexport)
#else
#define KAI_DECLSPEC_API __declspec(dllimport)
#endif

EXTERN_C_START

KAI_DECLSPEC_API void WINAPI hello();

KAI_DECLSPEC_API HRESULT WINAPI getRoamingAppDataPath(PWSTR *ppszPath);

extern KAI_DECLSPEC_API int gDllInt;

EXTERN_C_END

#endif //CMAKEDLL_LIBRARY_H
