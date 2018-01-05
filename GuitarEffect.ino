#include <Arduino.h>
#include <Audio.h>
#include <Bounce.h>
#include "enc.h"
#include <Encoder.h>
#include <Math.h>
#include "model.h"
#include <SPI.h>
#include "state_manager.h"
#include "state_display.h"
#include "state_editor.h"
#include "state_mainmenu.h"
#include "state_test.h"
#include <string.h>
#include <U8g2lib.h>
#include <Wire.h>

#define PIN_CLOCK		14
#define PIN_DATA		7
#define PIN_CS			20

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=265,455
AudioAnalyzeRMS          rms1;           //xy=444,354
AudioFilterStateVariable filter1;        //xy=476,464
AudioEffectReverb        reverb1;        //xy=689,315
AudioOutputI2S           i2s2;           //xy=821,519
AudioConnection          patchCord1(i2s1, 0, rms1, 0);
AudioConnection          patchCord2(i2s1, 0, filter1, 0);
AudioConnection          patchCord3(filter1, 0, i2s2, 0);
AudioConnection          patchCord4(filter1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=325,273
// GUItool: end automatically generated code


#define ENCODER1BUTTON	26
#define ENCODER2BUTTON	29
#define ENCODER3BUTTON	32

EncoderCapsule encc1 = {Encoder(25,24), EncoderButton(ENCODER1BUTTON)};
EncoderCapsule encc2 = {Encoder(28,27), EncoderButton(ENCODER2BUTTON)};
EncoderCapsule encc3 = {Encoder(31,30), EncoderButton(ENCODER3BUTTON)};

const int myInput = AUDIO_INPUT_LINEIN;


U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R2, PIN_CLOCK, PIN_DATA, PIN_CS);
//U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R2, PIN_CS);

StateManager stateManager = StateManager(new ProgramState*[4], 4);
//MainMenuState mainMenuState = ;
//DisplayState displayState = ;
//EditorState editorState = ;

void setup()
{
	//First allocate audiomemory
	AudioMemory(30);

	//Set as inputs
	pinMode(ENCODER1BUTTON, INPUT);
	pinMode(ENCODER2BUTTON, INPUT);
	pinMode(ENCODER3BUTTON, INPUT);

	//Enable pullups on buttons
	digitalWrite(ENCODER1BUTTON, HIGH);
	digitalWrite(ENCODER2BUTTON, HIGH);
	digitalWrite(ENCODER3BUTTON, HIGH);

	//Order states
	stateManager.states[0] = new MainMenuState(&u8g2, &encc1, &encc2, &encc3, &stateManager);
	stateManager.states[1] = new DisplayState(&u8g2, &encc1, &encc2, &encc3, &stateManager);
	stateManager.states[2] = new EditorState(&u8g2, &encc1, &encc2, &encc3, &stateManager);
	stateManager.states[3] = new TestState(&u8g2, &encc1, &encc2, &encc3, &stateManager);
	stateManager.setCurrentState(0);

	//Set default value for ecnoder 2 we use it for freq

	encc2.r.write(300/10);

	filter1.frequency(300);
	filter1.resonance(0.7);

	//Enable the audio shield, select input, and enable output
	sgtl5000_1.enable();
	sgtl5000_1.inputSelect(myInput);
	sgtl5000_1.volume(0.5);

	SPI.setSCK(PIN_CLOCK);
	SPI.setMOSI(PIN_DATA);
	SPI.setCS(PIN_CS);
	//SPI.setClockDivider(SPI_CLOCK_DIV128);

	u8g2.begin();

	allocateForProtos(4);
	// IN
	addProto(new ModuleProto("IN", 0, NULL, 0, 1));
	// FIL
	addProto(new ModuleProto("FIL", 3, new const char *[3] {"frequency", "resonance", "octave"}, 1, 1));
	// REV
	addProto(new ModuleProto("REV", 1, new const char *[1] {"reverb time"}, 1, 1));
	// OUT
	addProto(new ModuleProto("OUT", 0, NULL, 1, 0));

	allocateForModules(4);
	// IN
	addModule(0);
	getModule(0)->outputs[0][0] = 1;
	// FIL
	addModule(1);
	getModule(1)->outputs[0][0] = 2;
	getModule(1)->values[0] = BoundedValue(20.0, 1.0, 800.0, 440.0);
	getModule(1)->values[1] = BoundedValue(0.7, .1, 5.0, 0.7);
	getModule(1)->values[2] = BoundedValue(0.0, 0.2, 7.0);
	// REV
	addModule(2);
	getModule(2)->outputs[0][0] = 3;
	getModule(2)->values[0] = BoundedValue(0.0, 0.1, 5.0, 0.0);
	// OUT
	addModule(3);

	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_4x6_tr);
	stateManager.setup();
}

int32_t lasttime = 0;

void loop()
{
	/*
	 * INPUT GETTING
	 */
	encc1.c.read();
	encc2.c.read();
	encc3.c.read();

	/*
	 * STATE LOOPS
	 */
	stateManager.currentState->loop();

	char buf[40];
	sprintf(buf, "%d->%d:%d|%d", encc3.c.lastread(), encc3.c.currentread(), encc3.c.deltaread(), encc3.r.read());
	u8g2.drawStr(0, 64, buf);
//	sprintf(buf, "state=%s", stateManager.currentState->title);
//	u8g2.drawStr(0, 54, buf);

	u8g2.sendBuffer();

	//After drawing and recieving inputs, update audio
	filter1.frequency(getModule(1)->values[0].value());
	filter1.resonance(getModule(1)->values[1].value());
	filter1.octaveControl(getModule(1)->values[2].value());
	reverb1.reverbTime(getModule(2)->values[0].value());
}
