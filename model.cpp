/*
 * model.cpp
 *
 *  Created on: 25 dec. 2017
 *      Author: MisterCavespider
 */

#include "model.h"


static uint8_t moduleCount = 0;
static uint8_t connectionCount = 0;

static uint8_t mSize = 0;

static Module **modules;
static AudioStream **streams;
static AudioConnection **connections;


void allocateForModules(uint8_t size)
{
	modules = new Module*[size];
	streams = new AudioStream*[size];
	connections = new AudioConnection*[2*size];	// Average of 2 unique connections per module

	mSize = size;
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
	if(index > mSize)	return NULL;
	return modules[index];
}

/*
 * It cannot be assumed that all the modules
 * are in order, because of the putModule function.
 *
 * Just run the tree.
 */
void bakeModules()
{
	// Clean the array
	for(int i = 0; i < mSize; i++)
	{
		streams[i] = NULL;	// Set all pointers to null
	}

	Module *starter = getModule(0);	// TODO: Risky
	starter->createAudio(streams[starter->id()]);

}

void bakeModule(Module *m)
{
	// Create audio
	m->createAudio(streams[m->id()]);

	// Connect
	for(int i = 0; i < m->outputCount(); i++)
	{
		Module *t = getModule(m->outputs()[i]);
		if(t->inputCount() > 0 && containsInput(t, m->id()) && connectionCount < mSize*2)	// Mutually recognised
		{
			if(streams[t->id()])	// Init?
			{
				bakeModule(t);
			}
			connections[connectionCount] = new AudioConnection(*streams[m->id()], 0, *streams[t->id()], 0);
		}
	}
}

bool containsInput(Module *m, uint8_t input)
{
	for(int i = 0; i < m->inputCount(); i++)
	{
		if(m->inputs()[i] == input) return true;
	}
	return false;
}

uint8_t getSize()
{
	return mSize;
}
