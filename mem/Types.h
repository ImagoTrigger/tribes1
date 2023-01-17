#ifndef __TYPES_H__
#define __TYPES_H__

#pragma pack(push)
#pragma pack(1)

#include "Vector.h"

class RGBAf {
public:
	float r, g, b, a;
};

class RGBA {
public:
	unsigned char r, g, b, a;
};

class RGB {
public:
	unsigned char r, g, b;
};

class RGBf {
public:
	float r, g, b;
};


class BGRA {
public:
	unsigned char b, g, r, a;
};

#pragma pack(pop)

#endif // __TYPES_H__
