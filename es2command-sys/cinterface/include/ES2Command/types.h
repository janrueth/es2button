// This file is a mixture of things found in epsonscan2 6.7.43.0-1
// These types are useful to interface with the es2command API
// The source is licensed as LGPL 2.1
#pragma once

#include <stdint.h>

#include <string>

#define STATIC_CONST_KEY static const char* const
#define ES_STRING(str) str

#define ESString std::string
#define _ASSERT(x)

// Types use in interfaces
typedef char ES_CHAR;
typedef const ES_CHAR* ES_CHAR_CPTR;
typedef ES_CHAR* ES_JSON_PTR;
typedef ES_CHAR_CPTR ES_JSON_CPTR;
typedef uint8_t UInt8;
typedef float ESFloat;
typedef int BOOL;