#pragma once

typedef unsigned char Byte;
typedef Byte Bool;
typedef unsigned short Word;

typedef signed char Int8;
typedef Byte Uint8;
typedef signed short Int16;
typedef Word Uint16;
typedef signed int Int32;
typedef unsigned int Uint32;
typedef signed long long Int64;
typedef unsigned long long Uint64;
typedef float Float32;
typedef double Double;
typedef size_t SizeT;
typedef uintptr_t UintptrT;
typedef Double MaxAlignT; //based on the cstddef c++ using : most aligned type
typedef clock_t ClockT;


#define FE_DECL _cdecl

#define FE_EXTERN extern
#define FE_INLINE_FUN FE_EXTERN inline
#define FE_FORCEINLINE_FUN FE_EXTERN __forceinline

#define FALSE 0
#define TRUE 1

#define BIT(x) (1 << x)

#if defined(_MSC_VER)
#	define FE_CORE_DEBUG_BREAK __debugbreak()
#elif defined(__GNUC__) || defined(__GNUG__)
#	define FE_CORE_DEBUG_BREAK asm("int $3")//won't compile with -masm=intel
#else
#	define FE_CORE_DEBUG_BREAK FE_CORE_LOG_ERROR("FE_CORE_DEBUG_BREAK don't do anything")
#endif

#define FE_CORE_ABORT abort()

#ifdef FE_ENABLE_ASSERTS

#	define FE_ASSERT(x, ...) \
	if(x) \
	{ }\
	else\
	{\
		FE_LOG_ERROR("%s Assertion Failed : %s", #x, __VA_ARGS__); \
		FE_CORE_DEBUG_BREAK; \
		FE_CORE_ABORT; \
	}

#	define FE_CORE_ASSERT(x, ...) \
	if(x) \
	{ }\
	else\
	{\
		FE_CORE_LOG_ERROR("%s Assertion Failed : %s", #x, __VA_ARGS__); \
		FE_CORE_DEBUG_BREAK; \
		FE_CORE_ABORT; \
	}

#	define CORE_COMPILE_TIME_ASSERTx(COND, msg) typedef char core_static_assertion_##msg[(!!(COND))*2-1]
#	define CORE_COMPILE_TIME_ASSERT2(X, L) CORE_COMPILE_TIME_ASSERTx(X,at_line_##L)
#	define CORE_COMPILE_TIME_ASSERT(X, LINE) CORE_COMPILE_TIME_ASSERT2(X, LINE)

#	define FE_CORE_STATIC_ASSERT(x) CORE_COMPILE_TIME_ASSERT(x, __LINE__)


#	define COMPILE_TIME_ASSERTx(COND, msg) typedef char static_assertion_##msg[(!!(COND))*2-1]
#	define COMPILE_TIME_ASSERT2(X, L) COMPILE_TIME_ASSERTx(X,at_line_##L)
#	define COMPILE_TIME_ASSERT(X, LINE) COMPILE_TIME_ASSERT2(X, LINE)
#	define FE_STATIC_ASSERT(x, msg) COMPILE_TIME_ASSERT(x, __LINE__)
#else
#	define FE_ASSERT(...)
#	define FE_CORE_ASSERT(...)
#	define FE_CORE_STATIC_ASSERT(...)
#	define FE_STATIC_ASSERT(...)
#endif