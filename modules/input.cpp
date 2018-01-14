/*
 * input.cpp
 *
 *  Created on: 6 jan. 2018
 *      Author: MisterCavespider
 */

#include "input.h"

InputModule::InputModule(uint8_t id) {
	mId = id;
	mInputs = NULL;
	mOutputs = new uint8_t[4]	{255, 255, 255, 255};
}

const char *InputModule::title()	{return "IN";}
const char **InputModule::names()	{return NULL;}
uint8_t InputModule::valueCount()	{return 0;}
uint8_t InputModule::inputCount()	{return 0;}
uint8_t InputModule::outputCount()	{return 1;}
void InputModule::createAudio(AudioStream *store)	{store = new AudioInputI2S();}
