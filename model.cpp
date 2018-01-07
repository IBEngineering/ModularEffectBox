/*
 * model.cpp
 *
 *  Created on: 25 dec. 2017
 *      Author: MisterCavespider
 */
#include "model.h"
#include <stdlib.h>
#include <stdint.h>
#include "modules/input.h"

static uint8_t protoCount = 0;
static uint8_t moduleCount = 0;
static ModuleProto *protos;
static Module **modules;

void allocateForProtos(uint8_t size)
{
	protos = new ModuleProto[size];
}

void allocateForModules(uint8_t size)
{
	modules = new Module*[size];
}

int addProto(ModuleProto *proto)
{
	//check size?

	protos[protoCount] = *proto;
	protoCount++;
	return protoCount-1;
}

void addModule(int protoIndex)
{
	modules[moduleCount] = new InputModule(moduleCount);
	moduleCount++;
}

void addModule(Module *module)
{
	modules[moduleCount] = module;
	moduleCount++;
}

Module *putModule(Module *module)
{
	modules[module->id()] = module;
	return module;
}

Module *getModule(int index)
{
	return modules[index];
}

