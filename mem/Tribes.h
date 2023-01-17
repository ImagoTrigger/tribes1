#ifndef __TRIBES_H__
#define __TRIBES_H__

#include "Sys.h"
#include "Types.h"
#include "Loader.h"

/*
	Needs to be first thing in function if you're using args
*/

#define BuiltInFunctionGetArgs( )    \
	int argc;                        \
	__asm { mov [ argc ], ecx }      \
	                                 \
	const char *self = argv[ 0 ];    \
	argc--;	                         \
	argv++;                          \


#define BuiltInVariable( __scripted__, __type__, __name__, __default__ ) \
__type__ __name__ = __default__; \
static const VariableConstructor vc##__name__( __scripted__, &__name__, VAR_##__type__ );

#define BuiltInVariable_Class( __scripted__, __type__, __class__, __name__, __default__ ) \
__type__ __class__::__name__ = __default__; \
static const VariableConstructor vc##__class__##__name__( __scripted__, &__class__::__name__, VAR_##__type__ );

#define BuiltInFunction( __scripted__, __name__ ) \
char * __stdcall __name__( const char *argv[] ); \
static const ConsoleConstructor cc##__name__( __scripted__, __name__ ); \
char * __stdcall __name__( const char *argv[] )

// Should already be prototyped in the class declaration
#define BuiltInFunction_Class( __scripted__, __class__, __name__ ) \
static const ConsoleConstructor cc##__class__##__name__( __scripted__, __class__::__name__ ); \
char * __stdcall __class__::__name__( const char *argv[] )


#define BuiltInFunction_Prototype( __scripted__, __name__ ) \
static char * __stdcall __name__( const char *argv[] );

#define BuiltInFunction_NoConstruct( __scripted__, __name__ ) \
char * __stdcall __name__( const char *argv[] )

/*
	Macros for saving to hex and back. Pointer to String needs
	at least 9 bytes for the string..
*/

// read 4 bytes, write a max of 9
#define PointerToString( ptr, str ) \
( Tribes::Htoa( (char *)&ptr, str, 4, 9 ) )

// make sure the input string was exactly 4 bytes
#define StringToPointer( str, ptr ) \
( Tribes::Atoh( str, (char *)&ptr, 4 ) == 4 )


/*
	Internal typedefs straight to Tribes
*/
typedef int (__cdecl *type_AtoI )( const char *val );
typedef float (__cdecl *type_AtoF )( const char *val );
typedef void (__cdecl *type_Free )( void *addr );
typedef void *(__cdecl *type_Malloc )( int amt );
typedef void *(__cdecl *type_ReAlloc )( void *addr, int new_amt );
typedef int (__cdecl *type_StrICmp )( const char *a, const char *b );
typedef char *(__cdecl *type_Strchr )( const char *src, char c );

#define Stricmp( a, b ) ( !Tribes::Stricmp( a, b ) )

#define PTR_CONSOLE_OBJ            ( 0x6583c4 )

#define VAR_bool                   (        1 )
#define VAR_int                    (        2 )
#define VAR_float                  (        3 )
#define VAR_double                 (        4 )

#if defined(__USE_TRIBES_MALLOC__)
	#define malloc( amt ) Tribes::Malloc( ( amt ) )
	#define free( block ) Tribes::Free( (void *)block )
	#define realloc( block, amt ) Tribes::Realloc( (void *)block, ( amt ) );
#endif

class Tribes {
public:
	static char Ctob( char c );
	static int Htoa( const char *src, char *dst, int src_len, int max_dst );
	static bool Atob( const char *ascii );
	static int Atoh( const char *src, char *dst, int max_dst );
	

	static void AddFunction( const char *name, const void *address );
	static void AddVariable( const char *name, const void *address, int var_type );

	static void Echo( const char *str, ... );	
	static void Eval( const char *str, ... );
	static char *ExecFunction( int argc, char *function, ... );

	static int GetTicks( );
	static char *GetVariable( const char *name );
	
	static void SetVariable( const char *name, const char *value );

	static int Scanf( const char *buf, const char *ftm, ... );
	static int Sprintf( char *buf, const char *fmt, ... );
	static int SprintfVarArg( char *buf, const char *fmt, va_list args );
	static void StaticEval( const char *cmd );
	static const char *Stristr( const char *haystack, const char *needle );

	/*
		Variables / etc
	*/

	static char sprintBuffer[ 32768 ];
	static char ctob_table[ 256 ];
	static bool ctob_loaded;
	static char *True, *False, *Zero, *One, *NegOne;

	/*
		Straight-through functions
	*/
	
	static type_AtoI Atoi;
	static type_AtoF Atof;
	static type_Free Free;
	static type_Malloc Malloc;
	static type_ReAlloc Realloc;
	static type_Strchr Strchr;
	static type_StrICmp Stricmp;
};

/*
	Scripted constructors. These will get statically constructed twice 
	if you're using a CRT since the CRT constructs on module load, which
	is bad. We want to construct after Tribes has created the script
	system, aka after loader_started( ) is true
*/

class ConsoleConstructor {
public:
	ConsoleConstructor( const char *name, const void *address ) {
#if !defined(__CUSTOM_LIBC__)
		if ( loader_started( ) )
#endif
			Tribes::AddFunction( name, address );
	}
};

class VariableConstructor {
public:
	VariableConstructor( const char *name, const void *address, int type ) {
#if !defined(__CUSTOM_LIBC__)
		if ( loader_started( ) )
#endif
			Tribes::AddVariable( name, address, type );
	}
};


#endif // __TRIBES_H__
