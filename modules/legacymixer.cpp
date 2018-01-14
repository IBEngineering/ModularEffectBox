/*
 * legacymixer.cpp
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#include "legacymixer.h"

LegacyMixerModule::LegacyMixerModule(uint8_t id) {
	mId = id;
	mValues = new BoundedValue[4] {
		BoundedValue(-3., 0.1, 3.0, 1.0),
		BoundedValue(-3., 0.1, 3.0, 1.0),
		BoundedValue(-3., 0.1, 3.0, 1.0),
		BoundedValue(-3., 0.1, 3.0, 1.0)
	};
	mInputs = new uint8_t[4]	{255, 255, 255, 255};
	mOutputs = new uint8_t[1]	{255};
}

const char *LegacyMixerModule::title()		{return "MIX";}
const char **LegacyMixerModule::names()		{return new const char*[4] {"gain0", "gain1", "gain2", "gain3"};}
uint8_t LegacyMixerModule::valueCount()		{return 4;}
uint8_t LegacyMixerModule::inputCount()		{return 4;}
uint8_t LegacyMixerModule::outputCount()	{return 1;}
uint8_t LegacyMixerModule::paralsCount()	{return 1;}
void LegacyMixerModule::createAudio(AudioStream *store)	{store = new AudioMixer4();}
