#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Sys.h"

class Vector2i {
public:
	int x, y;
};

class Vector2f {
public:
	float x, y;

	Vector2f( );
	Vector2f( float x, float y );
	Vector2f( const char *s );

	Vector2f operator -( ) const;
	Vector2f &operator =( const Vector2f &a ); 
	
	Vector2f operator +( const Vector2f &a ) const;
	Vector2f operator -( const Vector2f &a ) const;

	float operator *( const Vector2f &a ) const;
	
	Vector2f operator *( const float &f ) const;
	Vector2f operator /( const float &f ) const;

	Vector2f &operator +=( const Vector2f &a );
	Vector2f &operator -=( const Vector2f &a );

	Vector2f &operator *=( const float &f );
	Vector2f &operator /=( const float &f );

	float &operator[]( int index );

	float Dot( const Vector2f &a ) const;

	float Length( ) const;
	Vector2f &Normalize( );
	char *ToString( char *s );
};

__inline__ Vector2f::Vector2f( float x, float y ) {
	this->x = x;
	this->y = y;
}

__inline__ Vector2f::Vector2f( ) {
}

__inline__ Vector2f Vector2f::operator -( ) const {
	return ( Vector2f( -x, -y ) );
}

__inline__ Vector2f &Vector2f::operator =( const Vector2f &a ) {
	x = a.x;
	y = a.y;

	return ( *this );
}


__inline__ Vector2f Vector2f::operator +( const Vector2f &a ) const {
	return ( Vector2f( x + a.x, y + a.y ) );
}

__inline__ Vector2f Vector2f::operator -( const Vector2f &a ) const {
	return ( Vector2f( x - a.x, y - a.y ) );
}


__inline__  float Vector2f::operator *( const Vector2f &a ) const {
	return ( x * a.x + y * a.y );
}


__inline__ Vector2f Vector2f::operator *( const float &f ) const {
	return ( Vector2f( x * f, y * f ) );
}

__inline__ Vector2f Vector2f::operator /( const float &f ) const {
	return ( *this * ( 1.0f / f ) );
}


__inline__ Vector2f &Vector2f::operator +=( const Vector2f &a ) {
	*this = ( *this + a );
	return ( *this );
}

__inline__ Vector2f &Vector2f::operator -=( const Vector2f &a ) {
	*this = ( *this - a );
	return ( *this );
}



__inline__ Vector2f &Vector2f::operator *=( const float &f ) {
	*this = ( *this * f );
	return ( *this );
}

__inline__ Vector2f &Vector2f::operator /=( const float &f ) {
	float inv = ( 1.0f / f );
	*this *= ( inv );
	return ( *this );
}

__inline__ float &Vector2f::operator []( int index ) {
	return ( ( (float *)this )[ index ] );
}

__inline__ float Vector2f::Dot( const Vector2f &a ) const {
	return ( *this * a );
}

__inline__ float Vector2f::Length( ) const {
	return ( sqrtf( x * x + y * y ) );
}

__inline__ Vector2f &Vector2f::Normalize( ) {
	float l = Length( );
	if ( l > 0.0f ) {
		*this /= l;
	} else {
		*this = Vector2f( 1, 0 ); // what else
	}

	return ( *this );
}




/*
	Vector3f
*/

class Vector3f {
public:
	float x, y, z;

	Vector3f( );
	Vector3f( float x, float y, float z );
	Vector3f( const char *s );

	Vector3f operator -( ) const;
	Vector3f &operator =( const Vector3f &a );
	
	Vector3f operator +( const Vector3f &a ) const;
	Vector3f operator -( const Vector3f &a ) const;

	float operator *( const Vector3f &a ) const;
	
	Vector3f operator *( const float &f ) const;
	Vector3f operator /( const float &f ) const;

	Vector3f &operator +=( const Vector3f &a );
	Vector3f &operator -=( const Vector3f &a );

	Vector3f &operator *=( const float &f );
	Vector3f &operator /=( const float &f );

	float &operator[]( int index );

	Vector3f Cross( const Vector3f  &a ) const;
	Vector3f &Cross( const Vector3f  &a, const Vector3f &b );
	float Dot( const Vector3f &a ) const;

	float Length( ) const;
	float LengthSquared( ) const;
	Vector3f &Normalize( );
	Vector2f &ToVector2f( );	
	char *ToString( char *s );
};

__inline__ Vector3f::Vector3f( float x, float y, float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

__inline__ Vector3f::Vector3f( ) {
}


__inline__ Vector3f Vector3f::operator -( ) const {
	return ( Vector3f( -x, -y, -z ) );
}

__inline__ Vector3f &Vector3f::operator =( const Vector3f &a ) {
	x = a.x;
	y = a.y;
	z = a.z;

	return ( *this );
}


__inline__ Vector3f Vector3f::operator +( const Vector3f &a ) const {
	return ( Vector3f( x + a.x, y + a.y, z + a.z ) );
}

__inline__ Vector3f Vector3f::operator -( const Vector3f &a ) const {
	return ( Vector3f( x - a.x, y - a.y, z - a.z ) );
}


__inline__  float Vector3f::operator *( const Vector3f &a ) const {
	return ( x * a.x + y * a.y + z * a.z );
}


__inline__ Vector3f Vector3f::operator *( const float &f ) const {
	return ( Vector3f( x * f, y * f, z * f ) );
}

__inline__ Vector3f Vector3f::operator /( const float &f ) const {
	return ( *this * ( 1.0f / f ) );
}


__inline__ Vector3f &Vector3f::operator +=( const Vector3f &a ) {
	*this = ( *this + a );
	return ( *this );
}

__inline__ Vector3f &Vector3f::operator -=( const Vector3f &a ) {
	*this = ( *this - a );
	return ( *this );
}



__inline__ Vector3f &Vector3f::operator *=( const float &f ) {
	*this = ( *this * f );
	return ( *this );
}

__inline__ Vector3f &Vector3f::operator /=( const float &f ) {
	float inv = ( 1.0f / f );
	*this *= ( inv );
	return ( *this );
}

__inline__ float &Vector3f::operator []( int index ) {
	return ( ( (float *)this )[ index ] );
}

__inline__ Vector3f Vector3f::Cross( const Vector3f &a ) const {
	return ( Vector3f( y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x ) );
}

__inline__ Vector3f &Vector3f::Cross( const Vector3f &a, const Vector3f &b ) {
	*this = a.Cross( b );
	return ( *this );
}

__inline__ float Vector3f::Dot( const Vector3f &a ) const {
	return ( *this * a );
}

__inline__ float Vector3f::Length( ) const {
	return ( sqrtf( x * x + y * y + z * z ) );
}

__inline__ float Vector3f::LengthSquared( ) const {
	return ( x * x + y * y + z * z );
}

__inline__ Vector3f &Vector3f::Normalize( ) {
	float l = Length( );
	if ( l > 0.0f ) {
		*this /= l;
	} else {
		*this = Vector3f( 1, 0, 0 ); // what else
	}

	return ( *this );
}

__inline__ Vector2f &Vector3f::ToVector2f( ) {
	return ( (Vector2f &)*this );
}




#endif // __VECTOR_H__
