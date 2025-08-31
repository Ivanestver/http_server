#pragma once

#if defined(_WIN32)
#ifdef MY_DLL_EXPORTS
#define MY_API __declspec(dllexport)
#else
#define MY_API __declspec(dllimport)
#endif
#else // Linux and other platforms
#define MY_API __attribute__((visibility("default")))
#endif