/*
 * envelope.cpp
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#include "envelope.h"

EnvelopeModule::EnvelopeModule(uint8_t id) {
	mId = id;
	mValues = new BoundedValue[6] {
		BoundedValue(0.0, .5, 1000.0, 0.0),
		BoundedValue(0.0, .5, 1000.0, 10.5),
		BoundedValue(0.0, .5, 1000.0, 2.5),
		BoundedValue(0.0, .5, 1000.0, 35.0),
		BoundedValue(0.0, 0.05, 1.0, 0.5),
		BoundedValue(0.0, .5, 1000.0, 300.0)
	};
	mInputs = new uint8_t[1]	{255};
	mOutputs = new uint8_t[1]	{255};
}

const char *EnvelopeModule::title()		{return "ENV";}
const char **EnvelopeModule::names()	{return new const char*[6] {"delay", "attack", "hold", "decay", "sustain", "release"};}
uint8_t EnvelopeModule::valueCount()	{return 6;}
uint8_t EnvelopeModule::inputCount()	{return 1;}
uint8_t EnvelopeModule::outputCount()	{return 1;}
uint8_t EnvelopeModule::paralsCount()	{return 1;}
void EnvelopeModule::createAudio(AudioStream *store)	{store = new AudioEffectEnvelope();}

