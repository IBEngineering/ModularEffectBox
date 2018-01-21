/*
 * DelayL.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: borgert
 */

#include "DelayL.h"

DelayL :: DelayL( float delay, float * delayMemory, uint16_t delayMemSz )
{
  if ( delay < 0.0 ) {
	 return;
  }

  if ( delay > (float) delayMemSz ) {
    return;
  }

  this->delayMem = delayMemory;
  this->delayMemSize = delayMemSz;

  inPoint_ = 0;
  delay_ = delay;
  doNextOut_ = true;
  alpha_ = 0;
  omAlpha_ = 0;
  outPoint_ = 0;
  inPoint_ = 0;
  nextOutput_ = 0;
  gain_ = 1;


  this->setDelay( delay );
}

DelayL :: ~DelayL()
{
}


float DelayL :: tapOut( unsigned long tapDelay )
{
  long tap = inPoint_ - tapDelay - 1;
  while ( tap < 0 ) // Check for wraparound.
    tap += delayMemSize;

  return delayMem[tap];
}

void DelayL :: tapIn( float value, unsigned long tapDelay )
{
  long tap = inPoint_ - tapDelay - 1;
  while ( tap < 0 ) // Check for wraparound.
    tap += delayMemSize;

  delayMem[tap] = value;
}
