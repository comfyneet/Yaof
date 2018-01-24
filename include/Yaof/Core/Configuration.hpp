#ifndef YAOF_CORE_CONFIGURATION_HPP
#define YAOF_CORE_CONFIGURATION_HPP

#include <climits>

#ifdef _MSC_VER
#  define YAOF_DLLEXPORT __declspec(dllexport)
#  define YAOF_DLLIMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#  define YAOF_DLLEXPORT __attribute__((visibility("default")))
#  define YAOF_DLLIMPORT
#else
#   error("Unknown compiler")
#endif

#ifdef YAOF_COMPILE
#  define YAOF_DLL YAOF_DLLEXPORT
#  define YAOF_TEMPLATE_DLL YAOF_DLLEXPORT
#  define YAOF_EXTERN
#else
#  define YAOF_DLL YAOF_DLLIMPORT
#  define YAOF_TEMPLATE_DLL
#  define YAOF_EXTERN extern
#endif

#ifdef _MSC_VER
#  pragma warning(disable: 4201) // nonstandard extension used: nameless struct/union
#  pragma warning(disable: 4251) // class 'X' needs to have dll-interface to be used by clients of class 'Y'
#endif

#define YAOF_CONTEXT_VERSION_MAJOR 3
#define YAOF_CONTEXT_VERSION_MINOR 3

static_assert(CHAR_BIT == 8, "CHAR_BIT != 8");
typedef unsigned char byte;

#endif
