#pragma once

#include "Timer.h"

class InputHandler
{
	RealF rValue;
	RealF rTarget;
	bool fAnalogStick;
	bool rAnalogStickRange;
	float rAnalogStickValue;
	Timer timer;
	void* diAnalog;
	void* diDigital;
	void* diMouse;
	void** diFocus;


public:
	
	InputHandler();
	virtual ~InputHandler();
	void sample(float rDelta, int iDevice);
	void sampleDigital(float rDelta, bool fIsKeyboard);
	void sampleAnalog(float rDelta);
	void sampleMouse(float rDelta);
	void reset();
	float getInput();
};
