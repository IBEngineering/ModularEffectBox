/*
 * filter.cpp
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#include "filter.h"

FilterModule::FilterModule(uint8_t id) {
	mId = id;
	mValues = new BoundedValue[3] {
		BoundedValue(40.0, 1.0, 1000.0, 220.0),
		BoundedValue(0.7, 0.1, 5.0, 0.7),
		BoundedValue(0.0, 0.1, 7.0, 2.5)
	};
	mInputs = new uint8_t[2]	{255, 255};
	mOutputs = new uint8_t[3]	{255, 255, 255};	// TODO: 2 per port
}

const char *FilterModule::title()	{return "FIL";}
const char **FilterModule::names()	{return new const char *[3] {"frequency", "resonance", "octave control"};}
uint8_t FilterModule::valueCount()	{return 3;}
uint8_t FilterModule::inputCount()	{return 2;}
uint8_t FilterModule::outputCount()	{return 3;}
void FilterModule::createAudio(AudioStream *store)	{store = new AudioFilterStateVariable();}
