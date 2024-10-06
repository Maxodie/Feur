#pragma once

typedef unsigned char BYTE;
typedef BYTE BOOL;
typedef unsigned short WORD;

typedef BYTE Uint8;
typedef char Int8;
typedef short Int16;
typedef unsigned short Uint16;
typedef int Int32;
typedef unsigned int Uint32;


#define FE_API

#define FALSE 0
#define TRUE 1

#define BIT(x) (1 << x)

#define debugBreak(x) asm { int 3 }
#ifdef FE_ENABLE_ASSERTS

	#define FE_ASSERT(x, ...) \
	if(x) \
	{ }\
	else\
	{\
		FE_LOG_ERROR("%s Assertion Failed %s", #x, __VA_ARGS__); \
		__debugbreak(); \
	}

	#define FE_CORE_ASSERT(x, ...) \
	if(x) \
	{ }\
	else\
	{\
		FE_CORE_LOG_ERROR("%s Assertion Failed %s", #x, __VA_ARGS__); \
		__debugbreak(); \
	}
#else
#define FE_ASSERT(x, ...)
#define FE_CORE_ASSERT(x, ...)
#endif