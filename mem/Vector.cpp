#include "Tribes.h"
#include "Vector.h"

Vector2f::Vector2f( const char *s ) {
	x = y = 0.0f;
	Tribes::Scanf( s, "%f %f", &x, &y );
}

char *Vector2f::ToString( char *s ) {
	Tribes::Sprintf( s, "%f %f", x, y );
	return ( s );
}



Vector3f::Vector3f( const char *s ) {
	x = y = z = 0.0f;
	Tribes::Scanf( s, "%f %f %f", &x, &y, &z );
}

char *Vector3f::ToString( char *s ) {	
	Tribes::Sprintf( s, "%f %f %f", x, y, z );
	return ( s );
}

