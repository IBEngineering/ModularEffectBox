/*
 * DelayL.h
 *
 *  Created on: Jan 6, 2018
 *      Author: borgert
 */

#ifndef DELAYL_H_
#define DELAYL_H_

#include <stdint.h>

class DelayL
{
public:

  //! Default constructor creates a delay-line with maximum length of 4095 samples and zero delay.
  /*!
    An StkError will be thrown if the delay parameter is less than
    zero, the maximum delay parameter is less than one, or the delay
    parameter is greater than the maxDelay value.
   */
  DelayL( float delay , float * delayMemory, uint16_t delayMemSz );

  //! Class destructor.
  ~DelayL();

  //! Get the maximum delay-line length.
  unsigned long getMaximumDelay( void ) { return delayMemSize - 1; };

  //! Set the maximum delay-line length.
  /*!
    This method should generally only be used during initial setup
    of the delay line.  If it is used between calls to the tick()
    function, without a call to clear(), a signal discontinuity will
    likely occur.  If the current maximum length is greater than the
    new length, no memory allocation change is made.
  */
  void setMaximumDelay( unsigned long delay );

  //! Set the delay-line length.
  /*!
    The valid range for \e delay is from 0 to the maximum delay-line length.
  */
  void setDelay( float delay );

  //! Return the current delay-line length.
  float getDelay( void ) const { return delay_; };

  //! Return the value at \e tapDelay samples from the delay-line input.
  /*!
    The tap point is determined modulo the delay-line length and is
    relative to the last input value (i.e., a tapDelay of zero returns
    the last input value).
  */
  float tapOut( unsigned long tapDelay );

  //! Set the \e value at \e tapDelay samples from the delay-line input.
  void tapIn( float value, unsigned long tapDelay );


  //! Return the value which will be output by the next call to tick().
  /*!
    This method is valid only for delay settings greater than zero!
   */
  float nextOut( void );

  //! Input one sample to the filter and return one output.
  float tick( float input );



 protected:
  uint16_t delayMemSize;
  float * delayMem;
  unsigned long inPoint_;
  unsigned long outPoint_;
  float delay_;
  float alpha_;
  float omAlpha_;
  float nextOutput_;
  float gain_;
  bool doNextOut_;
};

inline float DelayL :: nextOut( void )
{
  if ( doNextOut_ ) {
    // First 1/2 of interpolation
    nextOutput_ = delayMem[outPoint_] * omAlpha_;
    // Second 1/2 of interpolation
    if (outPoint_+1 < delayMemSize) {
      nextOutput_ += delayMem[outPoint_+1] * alpha_;
    } else {
      nextOutput_ += delayMem[0] * alpha_;
    }
    doNextOut_ = false;
  }

  return nextOutput_;
}

inline void DelayL :: setDelay( float delay )
{
  if ( delay + 1 > delayMemSize ) { // The value is too big.
    return;
  }

  if (delay < 0 ) {
     return;
  }

  float outPointer = inPoint_ - delay;  // read chases write
  delay_ = delay;

  while ( outPointer < 0 )
    outPointer += delayMemSize; // modulo maximum length

  outPoint_ = (long) outPointer;   // integer part

  alpha_ = outPointer - outPoint_; // fractional part
  omAlpha_ = (float) 1.0 - alpha_;

  if ( outPoint_ == delayMemSize ) outPoint_ = 0;
  doNextOut_ = true;
}

inline float DelayL :: tick( float input )
{
  delayMem[inPoint_++] = input * gain_;

  // Increment input pointer modulo length.
  if ( inPoint_ == delayMemSize )
    inPoint_ = 0;

  doNextOut_ = true;

  // Increment output pointer modulo length.
  if ( ++outPoint_ == delayMemSize )
    outPoint_ = 0;

  return nextOut();
}


#endif /* DELAYL_H_ */
