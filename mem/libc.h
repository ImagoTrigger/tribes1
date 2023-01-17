#ifndef __LIBC_H__
#define __LIBC_H__

#include <windows.h>
#include <math.h>
#include <string.h>

// static constructors/destructors
typedef void (__cdecl *_PVFV)( void );

// .CRT is readonly in vs8
#if ( _MSC_FULL_VER >= 140050214 ) 
	#pragma comment(linker, "/merge:.CRT=.rdata")
#else
	#pragma comment(linker, "/merge:.CRT=.data")
#endif


// comment this out to use a default CRT
#define __CUSTOM_LIBC__ 1

// comment this to use the CRT malloc instead of tribes
#define __USE_TRIBES_MALLOC__ 1

#if defined(__CUSTOM_LIBC__)
	#pragma comment(linker, "/NODEFAULTLIB")
	#pragma comment(linker, "/ENTRY:DllMain")

	#if !defined(__USE_TRIBES_MALLOC__)
		#define __USE_TRIBES_MALLOC__ 1
	#endif
#endif

// yeah no
#define toupper( c ) ( c & 0xdf ) 


#endif // __LIBC_H__
