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
		mdd = NULL;
	}

	void setup();
	void loop();
private:
	bool zoomed = false;
	selector_t selI, selO;
	drawdata_t *mdd;
	Module *m = NULL;	// !!!

	void onZoomedIn();
	void whileZoomedIn();
	void onZoomedOut();
	void whileZoomedOut();
	void highlightModule(Module *m);
	void drawModule(Module *m);
};

struct drawdata
{
	bool calcd	= false;	// Is it calculated?
	bool drawn	= false;	// Is it drawn?
	uint8_t x	= 0;		// Drawn x (left)
	uint8_t y	= 0;		// Drawn y (center)
	uint8_t w	= 0;		// Frame width (String width + 3)
};

#endif /* STATE_EDITOR_H_ */
