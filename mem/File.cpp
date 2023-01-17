#include "Tribes.h"

/*
	Example plugin for files. Provides:

	- <handle> File::Open( <path..>, [truncate] )
		Opens a file. Paths are relative to the base Tribes directory
		unless you give a full pathname.

		Ex: File::Open( "hey\\test.txt" ) will try to open Tribes\hey\text.txt

		[truncate] is an optional bool, and specifies if the file should be
		truncated to 0 bytes if it already exists

	- File::Close( <handle> )
		Pass the <handle> you got from File::Open to close the file

	- File::WriteLine( <handle>, <string> )
		Writes a line to the file. A "\n" is appended for you

	- <string> File::ReadLine( <handle> )
		Reads a line from the file. Because it is possible to read lines
		such as "false", "-1", and "", you must check File::IsEOF before each
		call to File::ReadLine to tell if you're at the end or not

	- <bool> File::IsEOF( <handle> )
		Returns whether the position of the specified file handle is at 
		the end of the file. Returns true if there's an error just to be
		safe
*/

BuiltInFunction( "File::Open", File_Open ) {
	BuiltInFunctionGetArgs( );

	if ( argc < 1 ) {
		Tribes::Echo( "Wrong argcount to %s( <path>, [truncate] )", self );
		return ( Tribes::False );
	}

	int createDisposition = ( OPEN_ALWAYS );
	if ( argc > 1 ) {
		if ( Tribes::Atob( argv[ 1 ] ) )
			createDisposition = ( CREATE_ALWAYS );
	}

	/*
		Maybe validate directory/path is ok to write to, 
		make sure nobody is escaping out with "../", etc..
	*/

	HANDLE f = CreateFile( 
		argv[ 0 ], 
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ,
		NULL, 
		createDisposition, 
		FILE_ATTRIBUTE_ARCHIVE, 
		NULL );

	if ( f == INVALID_HANDLE_VALUE ) {
		Tribes::Echo( "%s: Unable to open file \"%s\"! Error %d", self, argv[ 0 ], GetLastError( ) );
		return ( Tribes::False );
	}

	// Use Tribes::Htoa to turn the pointer into a string
	PointerToString( f, Tribes::sprintBuffer );
	return ( Tribes::sprintBuffer );
}

BuiltInFunction( "File::Close", File_Close ) {
	BuiltInFunctionGetArgs( );

	if ( argc != 1 ) {
		Tribes::Echo( "Wrong argcount to %s( <handle> )", self );
		return ( Tribes::False );
	}
	
	HANDLE h;

	// Use Tribes::Atoh to turn ascii into hex data, this can fail if they 
	// don't pass a large enough string for the pointer
	if ( !StringToPointer( argv[ 0 ], h ) ) {
		Tribes::Echo( "%s: Bad handle passed: %s", self, argv[ 0 ] );
		return ( Tribes::False );
	}

	CloseHandle( h );
	return ( Tribes::True );
}

BuiltInFunction( "File::WriteLine", File_WriteLine ) {
	BuiltInFunctionGetArgs( );

	if ( argc != 2 ) {
		Tribes::Echo( "Wrong argcount to %s( <handle>, <string> )", self );
		return ( Tribes::False );
	}
	
	HANDLE h;
	if ( !StringToPointer( argv[ 0 ], h ) ) {
		Tribes::Echo( "%s: Bad handle passed: %s", self, argv[ 0 ] );
		return ( Tribes::False );
	}

	if ( strlen( argv[ 1 ] ) >= ( sizeof( Tribes::sprintBuffer ) - 2 ) ) {
		Tribes::Echo( "%s: Too much data passed!", self );
		return ( Tribes::False );
	}

	DWORD dummy;
	strcpy( Tribes::sprintBuffer, argv[ 1 ] );
	strcat( Tribes::sprintBuffer, "\n" );

	WriteFile( h, Tribes::sprintBuffer, strlen( Tribes::sprintBuffer ), &dummy, NULL );

	return ( Tribes::True );
}

BuiltInFunction( "File::ReadLine", File_ReadLine ) {
	BuiltInFunctionGetArgs( );

	if ( argc != 1 ) {
		Tribes::Echo( "Wrong argcount to %s( <handle> )", self );
		return ( Tribes::False );
	}

	HANDLE h;
	if ( !StringToPointer( argv[ 0 ], h ) ) {
		Tribes::Echo( "%s: Bad handle passed: %s!", self, argv[ 0 ] );
		return ( Tribes::False );
	}
		
	DWORD read = 0;
	char *pos = &Tribes::sprintBuffer[ 0 ], *endl = NULL;

	// Since we aren't using buffers, read from the current position until we hit a
	// \n, then seek back if we went past the \n
	while ( !endl ) {
		// 512 byte chunks
		if ( !ReadFile( h, pos, 512, &read, NULL ) ) {
			Tribes::Echo( "%s: Unable to read from file! Error %d", self, GetLastError( ) );
			break;
		} else if ( read == 0 ) {
			break;
		}

		pos[ read ] = NULL;
		if ( ( endl = Tribes::Strchr( pos, '\n' ) ) ) {
			int overflow = ( read - ( endl - pos ) - 1 );
			if ( overflow > 0 )
				SetFilePointer( h, -overflow, NULL, FILE_CURRENT );

			pos = endl;
		} else {
			pos += read;
		}
	}

	*pos = NULL; // end of whatever
	return ( Tribes::sprintBuffer );
}

BuiltInFunction( "File::IsEOF", File_IsEOF ) {
	BuiltInFunctionGetArgs( );

	if ( argc != 1 ) {
		Tribes::Echo( "Wrong argcount to %s( <handle> )", self );
		return ( Tribes::True );
	}
	
	HANDLE h;
	if ( !StringToPointer( argv[ 0 ], h ) ) {
		Tribes::Echo( "%s: Bad handle passed: %s", self, argv[ 0 ] );
		return ( Tribes::True );
	}

	DWORD dummy;
	unsigned int size = GetFileSize( h, &dummy );
	return ( ( SetFilePointer( h, 0, NULL, FILE_CURRENT ) == size ) ? Tribes::True : Tribes::False );
}

BuiltInFunction( "File::SeekToEnd", File_SeekToEnd ) {
	BuiltInFunctionGetArgs( );

	if ( argc != 1 ) {
		Tribes::Echo( "Wrong argcount to %s( <handle> )", self );
		return ( Tribes::False );
	}
	
	HANDLE h;
	if ( !StringToPointer( argv[ 0 ], h ) ) {
		Tribes::Echo( "%s: Bad handle passed: %s", self, argv[ 0 ] );
		return ( Tribes::False );
	}

	DWORD dummy;
	unsigned int size = GetFileSize( h, &dummy );
	return ( ( SetFilePointer( h, size, NULL, FILE_BEGIN ) == size ) ? Tribes::True : Tribes::False );
}
