#ifndef __SYS_H__
#define __SYS_H__

#if !defined(NULL)
	#define NULL ( 0 )
#endif


#include "libc.h"

#define __dllapi    __declspec(dllexport)
#define __naked     __declspec(naked)
#define __inline__  __forceinline

#endif // __SYS_H__
