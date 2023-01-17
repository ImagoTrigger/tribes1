#include "Mem.h"

/*
	These are the exported functions Tribes looks for in mem.dll.
	Why they would code support for a 3rd party memory management DLL
	and then not include it I have no idea.
*/

__naked void __cdecl MS_Calloc( ) {
}

__naked void __cdecl MS_Malloc( ) {
}

__naked void __cdecl MS_Free( ) {
}

__naked void __cdecl MS_Realloc( ) {
}
