/*
 * model_module_prototype.cpp
 *
 *  Created on: 25 dec. 2017
 *      Author: MisterCavespider
 */

#include "model_module_prototype.h"

ModuleProto::ModuleProto()
{

}

ModuleProto::ModuleProto(ModuleEffectType type, const char* title, uint8_t valueSize, const char **names, uint8_t inputSize, uint8_t outputSize)
{
	this->type = type;
	this->title = title;
	this->valueCount = valueSize;
	this->names = names;
	this->inputCount = inputSize;
	this->outputCount = outputSize;
}
