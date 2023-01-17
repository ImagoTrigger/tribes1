#include "libc.h"
#include "Tribes.h"
#include "Mem.h"
#include "Loader.h"

#pragma data_seg(".CRT$XCA")
_PVFV ___xc_a[] = { 0 };
#pragma data_seg(".CRT$XCZ")
_PVFV ___xc_z[] = { 0 };
#pragma data_seg()

static _PVFV *_pf_atexitlist = 0;
static unsigned _max_atexitlist_entries = 0;
static unsigned _cur_atexitlist_entries = 0;

// Static Constructors
void __cdecl __initterm( _PVFV * pfbegin, _PVFV * pfend ) {
	while ( pfbegin < pfend ) {
		if ( *pfbegin != NULL )
			(**pfbegin)( );
		++pfbegin;
	}
}

void __cdecl __atexit_init( ) {
	_max_atexitlist_entries = 64;
	_pf_atexitlist = (_PVFV *)malloc( _max_atexitlist_entries * sizeof(_PVFV*) );

}

#if defined(__CUSTOM_LIBC__)
int __cdecl atexit (_PVFV func ) {
	if ( _cur_atexitlist_entries < _max_atexitlist_entries ) {
		_pf_atexitlist[ _cur_atexitlist_entries++ ] = func; 
		return 0;
	}

	return -1;
}
#endif


BOOL APIENTRY DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved ) {
	switch ( ul_reason_for_call ) {
		case DLL_PROCESS_ATTACH: {
			loader_init( );
		} break;

		case DLL_PROCESS_DETACH: {
			loader_shutdown( );
		}
	}

    return TRUE;
}

/*
	Static constructors
*/
void DLLStaticConstructors( ) {
	loader_setstarted( true );	

	__atexit_init( );
	__initterm( ___xc_a, ___xc_z );	

	loader_startup( );
}

// imago added for testing
void game_endframe() {
	Tribes::Echo("mem.dll(nude imago build) game_endframe..");

	// execfunction
	Tribes::Echo("Current time is %s", Tribes::ExecFunction(0, "Timestamp"));

	// eval
	Tribes::Eval("echo('Tribes::Eval tic count %x');", GetTickCount());
}
