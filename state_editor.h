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

class EditorState: public ProgramState {
public:
	EditorState(
			U8G2_ST7920_128X64_F_SW_SPI *u8g2,
			EncoderCapsule *encc1,
			EncoderCapsule *encc2,
			EncoderCapsule *encc3,
			StateManager *states)
			:ProgramState(u8g2, encc1, encc2, encc3, states, "EDITOR") {}

	void setup();
	void loop();

	virtual ~EditorState();
private:
	bool zoomed = false;

	void onZoomedIn(int32_t select);
	void whileZoomedIn(int32_t select);
	void onZoomedOut(int32_t select);
	uint8_t drawModule(int x, int y, Module *module, bool line);
};

#endif /* STATE_EDITOR_H_ */
