#include "Loader.h"
#include "Tribes.h"
#include "Mem.h"

// suppress "no return value"
#pragma warning( disable: 4035 )

void *__assert_plugin, 
     *__cmdline_startup;

void* __game_endframe_jmp = (void*)0x0050D354;

int __loader_started = 0;

bool __loader_flag = false;

void sendtohook() {
}

void loader_init( ) {
	__asm {

		lea eax, loader_endframe
		mov ds : [0x62f794] , eax // game::endframe

		mov eax, ds:[ 0x6315E8 ]
		mov [ __assert_plugin ], eax		
		mov dword ptr ds:[ 0x6315E8 ], offset loader_startup_stub

		mov eax, ds:[ 0x62F734 ]
		mov [ __cmdline_startup ], eax
		mov dword ptr ds:[ 0x62F734 ], offset loader_cmdline_stub

 		lea eax, sendtohook
 		mov ds:[ 0x641d04 ], eax

		mov ds:[ 0x688EDC ], 1
	}
}

__naked void loader_endframe() {
	__asm {
		pushad

		cmp[__loader_flag], 1
		je __loader_skipstartup

		call loader_startup
		mov[__loader_started], 1

		__loader_skipstartup:
		call game_endframe

			popad

			jmp __game_endframe_jmp
	}
}

/*
	This lets us construct our variables and functions
	before console.cs is run, so $pref:: variables can
	take precedence over our defaults
*/
__naked void loader_startup_stub( ) {
	__asm {
		call [ __assert_plugin ]

		pushad
		call DLLStaticConstructors
		popad
		retn
	}
}

/*
	Start up the console, then our announce
*/

__naked void loader_cmdline_stub( ) {
	__asm {
		call [ __cmdline_startup ]
		
		pushad
		call [ loader_startup_announce ]
		popad
		retn
	}
}


/*
	Statically constructed functions/variables don't like to start immediately
*/

void loader_setstarted( bool started ) {
	__loader_flag = ( started );
}

bool loader_started( ) {
	return ( __loader_flag );
}



/*
	Add code here!
*/

void loader_startup( ) {
	// Startup code goes here
	Tribes::Echo( "Example::Var was setting to %s", "LOL" );
}

void loader_shutdown( ) {
	// Shutdown code goes here
	Tribes::Echo( "Example::Var was setting to %s", "LOL" );

}

void loader_startup_announce( ) {
	// Do announces here so they're at the bottom of the console
	Tribes::Echo( "mem.dll(nude imago build) starting.." );
}


