#pragma once
#ifdef Arduino

#include <Arduino.h>
#include "MaxMatrix.h"
#define GetTickCount millis
int clockPin = 5;
int latchPin = 4;
int dataPin  = 3;
int maxInUse = 2;

MaxMatrix m(dataPin, latchPin, clockPin, maxInUse);

int leftButton = 8;
int rightButton = 9;
int speedUpButton  = 10;
int rotateButton = 11;

bool readDebounced(int buttonPin)
{
	bool matrix = digitalRead(buttonPin);
	static const int debouncePeriod = 50;

	for(int i=0; i<debouncePeriod; ++i, delay(1))
	{
		if(matrix != digitalRead(buttonPin))
			return false;
	}

	return true;
}

#endif