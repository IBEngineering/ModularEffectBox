/*
 * enc.h
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef ENC_H_
#define ENC_H_

#include <Arduino.h>
#include <Encoder.h>
#include <stdint.h>

#define PRESSEDV(enc)	enc.c.deltaread()
#define PRESSEDP(enc)	enc->c.deltaread()

#define	READV(enc)		enc.r.read()
#define READP(enc)		enc->r.read()
#define WRITEV(enc,v)	enc.r.write(v)
#define WRITEP(enc,v)	enc->r.write(v)

class EncoderButton {
public:
	EncoderButton(uint8_t pin);
	void	read();
	uint8_t	currentread();
	uint8_t	lastread();
	int8_t	deltaread();
	virtual ~EncoderButton();
private:
	uint8_t pin;
	uint8_t curr, last, delta;
};

typedef struct EncoderCapsule {
	Encoder r;
	EncoderButton c;
} EncoderCapsule;

#endif /* ENC_H_ */
