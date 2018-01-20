/*
 * output.cpp
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#include "output.h"

OutputModule::OutputModule(uint8_t id) {
	mId = id;
	mInputs = new uint8_t[1]	{255};
	mOutputs = NULL;
}

const char *OutputModule::title()	{return "OUT";}
const char **OutputModule::names()	{return NULL;}
uint8_t OutputModule::valueCount()	{return 0;}
uint8_t OutputModule::inputCount()	{return 1;}
uint8_t OutputModule::outputCount()	{return 0;}
uint8_t OutputModule::paralsCount()	{return 0;}	// No outputs
void OutputModule::createAudio(AudioStream *store)	{store = new AudioOutputI2S();}

