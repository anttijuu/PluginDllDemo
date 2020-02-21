//
//  EasyCryptoDefines.hpp
//  EasyCryptoLib
//
//  Created by Antti Juustila on 19.4.2017.
//  Copyright © 2017 Antti Juustila. All rights reserved.
//

#pragma once

// Generic helper definitions for shared library support
#if defined WIN32 || defined __CYGWIN__
#define EC_HELPER_DLL_IMPORT __declspec(dllimport)
#define EC_HELPER_DLL_EXPORT __declspec(dllexport)
#define EC_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4 || defined __llvm__ || defined __clang__ || defined __APPLE__
#define EC_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#define EC_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#define EC_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define EC_HELPER_DLL_IMPORT
#define EC_HELPER_DLL_EXPORT
#define EC_HELPER_DLL_LOCAL
#endif
#endif

// Now we use the generic helper definitions above to define EC_API and EC_LOCAL.
// EC_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// EC_LOCAL is used for non-api symbols.

#ifdef EC_DLL_EXPORTS // defined if we are building the EC DLL (instead of using it)
#define EC_API EC_HELPER_DLL_EXPORT
#else
#define EC_API EC_HELPER_DLL_IMPORT
#endif // EC_DLL_EXPORTS

#define EC_LOCAL EC_HELPER_DLL_LOCAL
