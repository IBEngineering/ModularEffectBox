/* Audio Library for Teensy 3.X
 * Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 * Development of this audio library was funded by PJRC.COM, LLC by sales of
 * Teensy and Audio Adaptor boards.  Please support PJRC's efforts to develop
 * open source software by purchasing Teensy or other PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "arm_math.h"
#include "stk_pitch_shift.h"
#include "DelayL.h"


#define DELAY_SZ 4096

static float delayBuf1[DELAY_SZ];
static float delayBuf2[DELAY_SZ];

static DelayL delayLine0(0.0f, delayBuf1, DELAY_SZ);
static DelayL delayLine1(0.0f, delayBuf2, DELAY_SZ);

float StkPitchShift::tick( float input )
{
	float32_t output= 0;
	// Calculate the two delay length values, keeping them within the
	// range 12 to maxDelay-12.
	delay_[0] += rate_;
	while ( delay_[0] > DELAY_SZ-12 ) delay_[0] -= delayLength_;
	while ( delay_[0] < 12 ) delay_[0] += delayLength_;

	delay_[1] = delay_[0] + halfLength_;
	while ( delay_[1] > DELAY_SZ-12 ) delay_[1] -= delayLength_;
	while ( delay_[1] < 12 ) delay_[1] += delayLength_;

	// Set the new delay line lengths.
	delayLine0.setDelay( delay_[0] );
	delayLine1.setDelay( delay_[1] );

	// Calculate a triangular envelope.
	env_[1] = fabs( ( delay_[0] - halfLength_ + 12 ) * ( 1.0 / (halfLength_ + 12 ) ) );
	env_[0] = 1.0 - env_[1];

	// Delay input and apply envelope.
	output =  env_[0] * delayLine0.tick( input );
	output += env_[1] * delayLine1.tick( input );

	// Compute effect mix and output.
	output *= effectMix_;
	output += ( 1.0 - effectMix_ ) * input;

	return output;
}


void StkPitchShift::update(void)
{
	audio_block_t *in;
	unsigned int channel;

	in = receiveWritable(0);

	if (!in) {
		return;
	}

	int i =0;
	for (i =0; i< AUDIO_BLOCK_SAMPLES; i++) {

	in->data[i] = 0;

		float32_t input = 0.0;

		arm_q15_to_float(&in->data[i], &input, 1);

		float32_t sample = tick(input);

		arm_float_to_q15(&sample, &in->data[i], 1);

	}


	transmit(in);
	release(in);
}
