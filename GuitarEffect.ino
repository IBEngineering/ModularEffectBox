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

#include "modules/input.h"
#include "modules/reverb.h"
#include "modules/filter.h"
#include "modules/flange.h"
#include "modules/waveshape.h"
#include "modules/legacymixer.h"
#include "modules/output.h"

#define PIN_CLOCK		14
#define PIN_DATA		7
#define PIN_CS			20

#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
short delayline[FLANGE_DELAY_LENGTH];

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=274,733
AudioAnalyzeRMS          rms1;           //xy=457,262
AudioFilterStateVariable filter1;        //xy=514,672
AudioAnalyzeNoteFrequency notefreq1;      //xy=583,457
AudioEffectWaveshaper    waveshape1;     //xy=592,615
AudioEffectReverb        reverb1;        //xy=713,676
AudioSynthWaveform       waveform1;      //xy=739,459
AudioMixer4              mixer1;         //xy=904,714
AudioOutputI2S           i2s2;           //xy=1080,636
AudioConnection          patchCord1(i2s1, 0, rms1, 0);
AudioConnection          patchCord2(i2s1, 0, filter1, 0);
AudioConnection          patchCord3(i2s1, 0, mixer1, 3);
AudioConnection          patchCord4(i2s1, 0, waveshape1, 0);
AudioConnection          patchCord5(i2s1, 0, notefreq1, 0);
AudioConnection          patchCord6(filter1, 0, reverb1, 0);
AudioConnection          patchCord7(waveshape1, 0, mixer1, 1);
AudioConnection          patchCord8(reverb1, 0, mixer1, 2);
AudioConnection          patchCord9(waveform1, 0, mixer1, 0);
AudioConnection          patchCord10(mixer1, 0, i2s2, 1);
AudioConnection          patchCord11(mixer1, 0, i2s2, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=288,350
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

float WAVESHAPE_EXAMPLE[17] = {
  -0.588,
  -0.579,
  -0.549,
  -0.488,
  -0.396,
  -0.320,
  -0.228,
  -0.122,
  0,
  0.122,
  0.228,
  0.320,
  0.396,
  0.488,
  0.549,
  0.579,
  0.588
};

void setup()
{
	//First allocate audiomemory
	AudioMemory(64);

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
	stateManager.states[1] = new DisplayState(&u8g2, &rms1, &encc1, &encc2, &encc3, &stateManager);
	stateManager.states[2] = new EditorState(&u8g2, &encc1, &encc2, &encc3, &stateManager);
	stateManager.states[3] = new TestState(&u8g2, &encc1, &encc2, &encc3, &stateManager);
	stateManager.setCurrentState(0);

	//Set default value for ecnoder 2 we use it for freq

	int i;
	for(i = 0; i < 17; i ++)
	{
		WAVESHAPE_EXAMPLE[i] = chebyshev(i/16.0 * 2.0 - 1.0, 4);
	}

	encc2.r.write(300/10);

	filter1.frequency(300);
	filter1.resonance(0.7);

	waveshape1.shape(WAVESHAPE_EXAMPLE, 17);

	notefreq1.begin(.15);
	waveform1.begin(.5, 110, WAVEFORM_SAWTOOTH);

//	flange1.begin(delayline, FLANGE_DELAY_LENGTH, FLANGE_DELAY_LENGTH/4, FLANGE_DELAY_LENGTH/4, .5);



	//Enable the audio shield, select input, and enable output
	sgtl5000_1.enable();
	sgtl5000_1.inputSelect(myInput);
	sgtl5000_1.volume(0.5);

	SPI.setSCK(PIN_CLOCK);
	SPI.setMOSI(PIN_DATA);
	SPI.setCS(PIN_CS);
	//SPI.setClockDivider(SPI_CLOCK_DIV128);

	u8g2.begin();

//	allocateForProtos(4);
//	// IN
//	addProto(new ModuleProto(ModuleEffectType::Input, "IN", 0, NULL, 0, 1));
//	// FIL
//	addProto(new ModuleProto(ModuleEffectType::Filter, "FIL", 3, new const char *[3] {"frequency", "resonance", "octave"}, 1, 1));
//	// REV
//	addProto(new ModuleProto(ModuleEffectType::Reverb, "REV", 1, new const char *[1] {"reverb time"}, 1, 1));
//	// OUT
//	addProto(new ModuleProto(ModuleEffectType::Output, "OUT", 0, NULL, 1, 0));


	Module *m;
	allocateForModules(7);
	// IN
	m = putModule(new InputModule(0));
	m->outputs()[0] = 1;
	// FIL
	m = putModule(new FilterModule(1));
	m->outputs()[0] = 2;
	// REV
	m = putModule(new ReverbModule(2));
	m->outputs()[0] = 3;
	// FLN
	m = putModule(new FlangeModule(3));
	m->outputs()[0] = 4;
	// WVS
	m = putModule(new WaveshapeModule(4));
	m->outputs()[0] = 5;
	// MIX
	m = putModule(new LegacyMixerModule(5));
	m->outputs()[0] = 6;
	// OUT
	m = putModule(new OutputModule(6));

	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_4x6_tr);
	stateManager.setup();
}

float chebyshev(float x, float n)
{
	if(n == 0) return 1;
	if(n == 1) return x;
	return 2.0 * x * chebyshev(x, n - 1.0) - chebyshev(x, n - 2.0);
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
	stateManager.loop();

//	char buf[40];
//	sprintf(buf, "%d->%d:%d|%d", encc3.c.lastread(), encc3.c.currentread(), encc3.c.deltaread(), encc3.r.read());
//	u8g2.drawStr(0, 64, buf);
//	sprintf(buf, "state=%s", stateManager.currentState->title);
//	u8g2.drawStr(0, 54, buf);

	u8g2.sendBuffer();

	//After drawing and recieving inputs, update audio
	filter1.frequency(getModule(1)->values()[0].value());
	filter1.resonance(getModule(1)->values()[1].value());
	filter1.octaveControl(getModule(1)->values()[2].value());

	reverb1.reverbTime(getModule(2)->values()[0].value());

//	flange1.voices(
//			FLANGE_DELAY_LENGTH/4,
//			FLANGE_DELAY_LENGTH/4,
//			getModule(3)->values()[2].value());

	mixer1.gain(0, getModule(5)->values()[0].value());
	mixer1.gain(1, getModule(5)->values()[1].value());
	mixer1.gain(2, getModule(5)->values()[2].value());
	mixer1.gain(3, getModule(5)->values()[3].value());

	if(notefreq1.available())
	{
		waveform1.frequency(notefreq1.read());
	}

	if(rms1.available())
	{
		waveform1.amplitude(rms1.read() * 2);
	}
}
