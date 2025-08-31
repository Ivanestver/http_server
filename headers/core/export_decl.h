#pragma once

#if defined(_WIN32)
#ifdef CORE_EXPORTS
#define CORE __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define CORE __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif
#else // Linux and other platforms
#define CORE __attribute__((visibility("default")))
#endif
