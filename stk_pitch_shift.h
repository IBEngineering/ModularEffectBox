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

#ifndef stk_pitch_shift_h_
#define stk_pitch_shift_h_

#include "Arduino.h"
#include "AudioStream.h"

class StkPitchShift : public AudioStream
{
public:
	StkPitchShift(uint16_t maxDelay_) : AudioStream(1, inputQueueArray) {
		_shift = 0.0f;
		maxDelay = maxDelay_;
		rate_ = 1.0f;
		delayLength_ = maxDelay - 24;
		halfLength_ = delayLength_ / 2;
		delay_[0] = 12;
		delay_[1] = maxDelay / 2;

/*
 		delayLine_[0].setMaximumDelay( maxDelay );
		delayLine_[0].setDelay( delay_[0] );
		delayLine_[1].setMaximumDelay( maxDelay );
		delayLine_[1].setDelay( delay_[1] );
		*/
		effectMix_ = 0.5;
		rate_ = 1.0;



	}
	void shift(float shift) {
		_shift = shift;
		if ( shift < 1.0 ) {
			rate_ = 1.0 - shift;
		}
		else if ( shift > 1.0 ) {
			rate_ = 1.0 - shift;
		}
		else {
			rate_ = 0.0;
			delay_[0] = halfLength_ + 12;
		}

	}
	virtual void update(void);
private:
	float delay_[2];
	float env_[2];
	float rate_;
	float effectMix_;
	uint16_t maxDelay;
	unsigned long delayLength_;
	unsigned long halfLength_;
	float _shift;
	audio_block_t *inputQueueArray[2];
protected:
	float tick( float input );

};

#endif
