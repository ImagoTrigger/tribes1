#ifndef __MEM_H__
#define __MEM_H__

#include "Sys.h"

void DLLStaticConstructors( );

#ifdef __cplusplus
extern "C" {
#endif

__dllapi void __cdecl MS_Calloc(  );
__dllapi void __cdecl MS_Malloc(  );
__dllapi void __cdecl MS_Free(  );
__dllapi void __cdecl MS_Realloc(  );

#ifdef __cplusplus
}
#endif


void game_endframe();

#endif // __MEM_H__
