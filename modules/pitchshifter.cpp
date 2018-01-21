/*
 * pitchshifter.cpp
 *
 *  Created on: 20 jan. 2018
 *      Author: MisterCavespider
 */

#include "pitchshifter.h"

PitchShifterModule::PitchShifterModule(uint8_t id) {
	mId = id;
	mValues = new BoundedValue[1]	{
		BoundedValue(-10, 0.1, 10, 5.0)
	};
	mInputs = new uint8_t[1]	{255};
	mOutputs = new uint8_t[1]	{255};
}

const char *PitchShifterModule::title()		{return "PSH";}
const char **PitchShifterModule::names()	{return new const char*[1] {"shift"};}
uint8_t PitchShifterModule::valueCount()	{return 1;}
uint8_t PitchShifterModule::inputCount()	{return 1;}
uint8_t PitchShifterModule::outputCount()	{return 1;}
uint8_t PitchShifterModule::paralsCount()	{return 1;}
void PitchShifterModule::createAudio(AudioStream *store)	{store = new StkPitchShift(128);}
