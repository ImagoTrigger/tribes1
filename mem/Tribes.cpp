#include <stdarg.h> // _vsnprintf
#include "Tribes.h"

// suppress "no return value"
#pragma warning( disable: 4035 )

// statics for functions
char *Tribes::False = "False";
char *Tribes::True = "True";
char *Tribes::Zero = "0";
char *Tribes::One = "1";
char *Tribes::NegOne = "-1";
char Tribes::sprintBuffer[ 32768 ];
char Tribes::ctob_table[ 256 ];
bool Tribes::ctob_loaded = false;

type_AtoI Tribes::Atoi = (type_AtoI )0x6070C8;
type_AtoF Tribes::Atof = (type_AtoF )0x6070B4;
type_Free Tribes::Free = (type_Free )0x488854;
type_Malloc Tribes::Malloc = (type_Malloc )0x4887C4;
type_ReAlloc Tribes::Realloc = (type_ReAlloc )0x488974;
type_StrICmp Tribes::Stricmp = (type_StrICmp )0x488150;
type_Strchr Tribes::Strchr = (type_Strchr )0x601160;

// built in function addresses
int __asciitobool      = 0x5F47D8;
int __echo             = 0x5F3DDC;
int __execfunction     = 0x5F42BC;
int __getvariable      = 0x5f3ff8;
int __internaleval     = 0x5f41a8;
int __addfunction      = 0x5F4138;
int __addvariable      = 0x5F40D8;
int __scanf            = 0x603EE8;
int __setvariable      = 0x5F3F10;
int __sprintf          = 0x604E44;

int __temp;

/*
	Character to Byte, interprets character as hex
*/

char Tribes::Ctob( char c ) {
	if ( c >= '0' && c <= '9' ) 
		c -= '0';
	else if ( c >= 'A' && c <= 'F' )
		c -= ( 'A' - 10 );
	else if ( c >= 'a' && c <= 'f' )
		c -= ( 'a' - 10 );
	else
		c = -1;

	return ( c );
}

/*
	Hex to ascii, converts raw data to a string
*/

int Tribes::Htoa( const char *src, char *dst, int src_len, int max_dst ) {
	static char *hex_table = "0123456789abcdef";
	int bytes_written = 0;

	while ( ( src_len-- > 0 ) && ( bytes_written + 3 <= max_dst ) ) {
		*dst++ = hex_table[ *(unsigned char*)src >>   4 ];
		*dst++ = hex_table[ *(unsigned char*)src  & 0xf ];
		src++;
		bytes_written += 2;
	}

	if ( bytes_written < max_dst ) {
		*dst = 0;
		bytes_written++;
	}

	return ( bytes_written );
}

bool Tribes::Atob( const char *ascii ) {
	__asm {
		mov eax, [ ascii ]
		call [ __asciitobool ]
	}
}

/*
	Ascii to hex, converts a hex encoded string to raw data
*/

int Tribes::Atoh( const char *src, char *dst, int max_dst ) {
	if ( !Tribes::ctob_loaded ) {
		for ( int i = 0; i < 256; i++ ) 
			Tribes::ctob_table[ i ] = Tribes::Ctob( i );
		Tribes::ctob_loaded = true;
	}

	int bytes_written = 0;
	char upper, lower;

	if ( !src )
		return ( bytes_written );
	
	while ( *src && *(src + 1) ) {
		upper = Tribes::ctob_table[ *src++ ];
		lower = Tribes::ctob_table[ *src++ ];

		if ( upper == -1 || lower == -1 )
			break;

		if ( bytes_written++ < max_dst )
			dst[ bytes_written - 1 ] = ( upper << 4 ) | ( lower );
	}

	return ( bytes_written );
}


void Tribes::AddFunction( const char *name, const void *address ) {
	__asm {
		push [ address ]
		push 0
		mov ecx, [ name ]
		xor edx, edx
		mov eax, ds:[ PTR_CONSOLE_OBJ ]
		call ds:[ __addfunction ]
	}
}

void Tribes::AddVariable( const char *name, const void *address, int var_type ) {
	__asm {
		push [ var_type ]
		push [ address ]
		mov ecx, name
		xor edx, edx
		mov eax, ds:[ PTR_CONSOLE_OBJ ]
		call ds:[ __addvariable ]
	}
}


/*
  function: echo
  purpose: formats and echos the message
  ------------------------------------------------------------
*/

__naked void Tribes::Echo( const char *str, ... ) {
	__asm {
		pop [ __temp ]
		
		mov eax, ds:[ PTR_CONSOLE_OBJ ]
		push eax
		call [ __echo ]

		add esp, 4
		push [ __temp ]
		retn
	}
}


/*
  function: eval
  purpose: executes a command in the tribes interpreter
  ------------------------------------------------------------
*/

void Tribes::StaticEval( const char *cmd ) {
	__asm {	
		push 0
		push 0
		
		mov edx, [ cmd ]
		xor ecx, ecx
		mov eax, ds:[ 0x6583c4 ]
		call [ __internaleval ]
	}
}


/*
  function: getVariable
  purpose: returns the value of the specified variable
  ------------------------------------------------------------
*/

char *Tribes::GetVariable( const char *name ) {
	__asm {
		mov edx, name
		mov eax, ds:[ PTR_CONSOLE_OBJ ]
		call ds:[ __getvariable ]
	}
}

/*
 function execFunction
 purpose: Executes a function with the specified arguments and returns a string result
 ex: Tribes::ExecFunction( 2, "GetWord", "One Two", "1" ) returns "Two"
                               GetWord(  "One Two", "1" );
 -------------------------------------------------------
*/ 

__naked char *Tribes::ExecFunction( int argc, char *function, ... ) {
	__asm {
		pop [ __temp ]
		
		mov eax, ds:[ PTR_CONSOLE_OBJ ]
		push eax
		inc dword ptr [ esp + 0x4 ] // argc
		call [ __execfunction ]

		add esp, 4
		push [ __temp ]
		retn
	}
}


/*
  function: Eval
  purpose: Evals a script fragment
  ------------------------------------------------------------
*/

void Tribes::Eval( const char *str, ... ) {
	va_list args;
	char message[ 2048 ];

	va_start( args, str );
	Tribes::SprintfVarArg( message, str, args );
	va_end( args );

	Tribes::StaticEval( message );
}


/*
  function: setVariable
  purpose: sets the value of the specified variable
  ------------------------------------------------------------
*/

void Tribes::SetVariable( const char *name, const char *value ) {
	__asm {
		mov ecx, [ value ]
		mov edx, [ name ]
		mov eax, ds:[ PTR_CONSOLE_OBJ ]
		call ds:[ __setvariable ]
	}
}


int Tribes::Sprintf( char *buf, const char *fmt, ... ) {
	__asm {
		mov eax, [ buf ]
		mov byte ptr [ eax ], 0
		lea ecx, [ buf ]
		lea eax, [ fmt + 4 ]
		push eax
		push fmt
		push ecx
		push 0x604a1c
		call [ __sprintf ]
		add esp, 0x10
	}
}

int Tribes::Scanf( const char *buf, const char *fmt, ... ) {
	__asm {
		lea ecx, [ buf ]
		lea eax, [ fmt + 4 ]
		push eax
		push fmt
		push ecx
		push 0x604AAC
		push 0x604A8C
		call [ __scanf ]
		add esp, 0x14
	}
}

int Tribes::SprintfVarArg( char *buf, const char *fmt, va_list args ) {
	__asm {
		mov eax, [ buf ]
		mov byte ptr [ eax ], 0
		lea ecx, [ buf ]
		mov eax, [ args ]
		push eax
		push fmt
		push ecx
		push 0x604a1c
		call [ __sprintf ]
		add esp, 0x10
	}
}

/*
  function: Stristr
  purpose: case insensitive version of strstr
  ------------------------------------------------------------
*/


const char *Tribes::Stristr( const char *haystack, const char *needle ) {
	if ( *needle == NULL )
		return ( haystack );

	const char *hend, *a, *b;
	hend = haystack + strlen( haystack ) - strlen( needle ) + 1;

	while ( haystack < hend ) {
		if ( toupper( *haystack ) == toupper( *needle ) ) {
			a = haystack;
			b = needle;
	
			for ( ; ; )  {
				if ( *b == NULL ) 
					return ( haystack );

				if ( toupper( *a++ ) != toupper( *b++ ) )
					break;
			}
		}

		haystack++;
	}

	return ( NULL );
}


/*
	Memory
*/

 void *__cdecl operator new( size_t amt ) {
	return ( malloc( amt ) );
}

void *__cdecl operator new[]( size_t amt ) {
	return ( malloc( amt ) );
}

void __cdecl operator delete( void *mem ) {
	free( mem );
}

void __cdecl operator delete[]( void *mem ) {
	free( mem );
}


