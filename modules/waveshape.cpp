/*
 * waveshape.cpp
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#include "waveshape.h"

WaveshapeModule::WaveshapeModule(uint8_t id) {
	mId = id;
	mValues = NULL;
	mInputs = new uint8_t[1]	{255};
	mOutputs = new uint8_t[1]	{255};
}

const char *WaveshapeModule::title()	{return "WVS";}
const char **WaveshapeModule::names()	{return NULL;}
uint8_t WaveshapeModule::valueCount()	{return 0;}
uint8_t WaveshapeModule::inputCount()	{return 1;}
uint8_t WaveshapeModule::outputCount()	{return 1;}
uint8_t WaveshapeModule::paralsCount()	{return 1;}
void WaveshapeModule::createAudio(AudioStream *store)	{store = new AudioEffectWaveshaper();}
