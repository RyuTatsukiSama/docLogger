#ifndef DLLAPI_H
#define DLLAPI_H

#if defined(_WIN32) && defined(CMAKEDLL_EXPORTS)
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#endif