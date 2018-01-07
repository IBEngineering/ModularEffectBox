/*
 * flange.cpp
 *
 *  Created on: 7 jan. 2018
 *      Author: MisterCavespider
 */

#include "flange.h"

FlangeModule::FlangeModule(uint8_t id) {
	mId = id;
	mValues = new BoundedValue[3] {
		BoundedValue(0.0, 1.0, 10.0, 0.0),
		BoundedValue(0.0, 1.0, 10.0, 0.0),
		BoundedValue(0.0, .1, 10.0, 0.0),
	};
	mInputs = new uint8_t[1];
	mOutputs = new uint8_t[1];
}

const char *FlangeModule::title()	{return "FLN";}
const char **FlangeModule::names()	{return new const char *[3] {"offset", "depth", "delay rate"};}
uint8_t FlangeModule::valueCount()	{return 3;}
uint8_t FlangeModule::inputCount()	{return 1;}
uint8_t FlangeModule::outputCount()	{return 1;}
