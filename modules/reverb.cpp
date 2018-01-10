/*
 * reverb.cpp
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#include "reverb.h"

ReverbModule::ReverbModule(uint8_t id) {
	mId = id;
	mValues = new BoundedValue[1] {BoundedValue(0.0, 0.1, 5.0, 0.2)};
	mInputs = new uint8_t[1]	{255};
	mOutputs = new uint8_t[1]	{255};
}

const char *ReverbModule::title()	{return "REV";}
const char **ReverbModule::names()	{return new const char*[1] {"reverb time"};}
uint8_t ReverbModule::valueCount()	{return 1;}
uint8_t ReverbModule::inputCount()	{return 1;}
uint8_t ReverbModule::outputCount()	{return 1;}
void ReverbModule::createAudio(AudioStream *store)	{store = new AudioEffectReverb();}

