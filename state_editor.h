/*
 * state_editor.h
 *
 *  Created on: 29 dec. 2017
 *      Author: MisterCavespider
 */

#ifndef STATE_EDITOR_H_
#define STATE_EDITOR_H_

#include "enc.h"
#include "model.h"
#include "state_state.h"

typedef struct drawdata drawdata_t;

class EditorState: public ProgramState {
public:
	EditorState(
			U8G2_ST7920_128X64_F_SW_SPI *u8g2,
			EncoderCapsule *encc1,
			EncoderCapsule *encc2,
			EncoderCapsule *encc3,
			StateManager *states)
			:ProgramState(u8g2, encc1, encc2, encc3, states, "EDITOR")
	{
		moduleDrawData = NULL;
	}

	void setup();
	void loop();
private:
	bool zoomed = false;
	uint8_t lastselect=-1, currselect=-1;
	drawdata_t *moduleDrawData;
	Module *m = NULL;	// !!!

	void onZoomedIn();
	void whileZoomedIn();
	void onZoomedOut();
	uint8_t drawModule(int x, int y, Module *module, bool line);
};

struct drawdata
{
	bool drawn	= false;
	uint8_t x	= 0;
	uint8_t y	= 0;
};

#endif /* STATE_EDITOR_H_ */
