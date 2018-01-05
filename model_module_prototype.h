/*
 * model_module_prototype.h
 *
 *  Created on: 25 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef MODEL_MODULE_PROTOTYPE_H_
#define MODEL_MODULE_PROTOTYPE_H_

#include <stdint.h>

enum class ModuleEffectType
{
	/*
	 * Default
	 */
	Input, Output,

	/*
	 * From Audio Library
	 *  "effect"
	 */
//	FADE, CHORUS, FLANGE, REVERB, ENVELOPE,
//	MULTIPLY, DELAY, DELAY_EXT, BITCRUSHER,
//	MIDSIDE, WAVESHAPE,
	Envelope, Reverb,

	/*
	 * From Audio Library
	 *  "filter"
	 */
	Filter,

	/*
	 * From Audio Library
	 *  "analyze"
	 */
	Fourier256, RMS
};

class ModuleProto
{
public:
	ModuleProto();
	ModuleProto(ModuleEffectType type, const char* title, uint8_t valueSize, const char **names, uint8_t inputSize, uint8_t outputSize);

	ModuleEffectType type;
	const char* title;
	const char **names;
	uint8_t valueCount, inputCount, outputCount;
};

#endif /* MODEL_MODULE_PROTOTYPE_H_ */
