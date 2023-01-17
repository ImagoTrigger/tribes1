#include "Tribes.h"

/*
	Vars can be int, float, or bool
*/

BuiltInVariable( "MyInt", int, __my_int, 0 ); // creates: int __my_int = 0;
BuiltInVariable( "MyFloat", float, __my_float, 0.0f ); // creates: float __my_float = 0.0f;
BuiltInVariable( "MyBool", bool, __my_bool, false ); // creates: bool __my_bool = false;
BuiltInVariable( "MyDouble", double, __my_double, 0.0 ); // creates: double __my_double = 0.0;


// Example arg function
BuiltInFunction( "Vector::Double", Vector_Double ) {
	BuiltInFunctionGetArgs( ); // must have this first if we use argc/argv/self

	if ( argc != 1 ) {
		Tribes::Echo( "Wrong argcount to %s( <f f f> )", self );
		return ( "0 0 0" );
	}

	Vector3f tmp( argv[ 0 ] );
	tmp *= 2;
	return ( tmp.ToString( Tribes::sprintBuffer ) );
}

// Example non-arg (and useful!) function
BuiltInFunction( "Timestamp", Timestamp ) {
	SYSTEMTIME systime;
	GetLocalTime( &systime );
	Tribes::Sprintf( Tribes::sprintBuffer, "%04d/%02d/%02d %02d:%02d:%02d.%03d", systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds );
	return ( Tribes::sprintBuffer );
}


// Test out a bit of everything
BuiltInFunction( "Tribes::Test", Tribes_Test ) {	
	BuiltInFunctionGetArgs( ); // must have this first if we use argc/argv

	// some args
	Tribes::Echo( " * %d arguments passed to %s", argc, self );
	for ( int i = 0; i < argc; i++ )
		Tribes::Echo(" * + Arg %d: %s", i, argv[ i ] );

	// get/set variable
	Tribes::SetVariable( "Tribes::Testing", "Abc 123 Test string" );
	Tribes::Echo( " * Reading value of variable $Tribes::Testing = %s", Tribes::GetVariable( "Tribes::Testing" ) );

	// test some stubs
	Tribes::Echo( " * Atof (9.283571) = %f", Tribes::Atof( "9.283571" ) );
	Tribes::Echo( " * GetWord( 'One Two', 1 ) = %s", Tribes::ExecFunction( 2, "GetWord", "One Two", "1" ) );

	// Hex to ascii, and back
	unsigned char _testHex[] = { 0, 13, 255, 9, 27, 192, 0, 32 }, _testHex2[32], _testAscii[32];
	Tribes::Htoa( (char *)_testHex, (char *)_testAscii, 8, 32 );
	Tribes::Echo( " * Htoa result (Source: 0, 13, 255, 9, 27, 192, 0, 32): %s", _testAscii );
	Tribes::Atoh( (char *)_testAscii, (char *)_testHex2, 32 );
	Tribes::Echo( " * Htoa->Atoh memcmp: %s", memcmp( _testHex, _testHex2, 8 ) ? "FAILED" : "PASSED" );

	// Changes to the tribes variables reflect in our program variables
	Tribes::SetVariable( "MyFloat", "3895.385f" );
	__my_double = __my_float * 200;
	Tribes::Echo( "My float = %f, my int = %d, my bool = %d, my double = %f", __my_float, __my_int, __my_bool, __my_double );
	
	// Test vectors & scanf
	Tribes::SetVariable( "Tribes::Testing", "0 -3.28356325 8233" );
	Vector3f tmp = Vector3f( Tribes::GetVariable( "Tribes::Testing" ) ); // string contsruction
	tmp *= 2;
	tmp += Vector3f( "1 1 1" );
	tmp += Vector3f( Tribes::GetVariable( "ponzi" ) ); // should default to "0 0 0"
	Tribes::Echo( "Vector = %s (should be ~1 -5.56 16467)", tmp.ToString( Tribes::sprintBuffer ) );
	
	// execfunction
	Tribes::Echo( "Current time is %s", Tribes::ExecFunction( 0, "Timestamp" ) );

	// eval
	Tribes::Eval( "echo('Tribes::Eval test %x');", GetTickCount( ) );

	return ( Tribes::True );
}
