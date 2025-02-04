//running on a Teensy 3.5

#include <Audio.h>

AudioSynthWaveform       waveform1;
AudioOutputAnalog  dac1;
AudioConnection          patchCord1(waveform1, dac1);

#define ON_DURATION 10000
#define VOL_PIN A0
#define FREQ_PIN A1
#define BTN_PIN A2

//
void setup() {
  Serial.begin(9600);

  pinMode(BTN_PIN, INPUT_PULLUP);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(10);

  // configure waveform for 440 Hz and maximum amplitude
  waveform1.frequency(440);
  waveform1.amplitude(1.0);

  waveform1.begin(WAVEFORM_SINE);
}

//
void loop() {
  static uint32_t startTime = 0;

  if (!digitalRead(BTN_PIN))
    startTime = millis();

  float vol = constrain(map((float)analogRead(VOL_PIN), 1023.0 * 0.1, 1023 * 0.9, 0.0, 1.0), 0.0, 1.0);
  vol = fmod(vol + 0.75, 1.0); //rotation offset
  float freq = constrain(map((float)analogRead(FREQ_PIN), 1023.0 * 0.1, 1023 * 0.9, 0.0, 1.0), 0.0, 1.0);
  freq = fmod(freq + 0.25, 1.0); //rotation offset

  Serial.printf("knob pos; vol:%.1f freq:%.1f\r\n", vol, freq);

  //AudioNoInterrupts();
  //if (millis() - startTime > ON_DURATION)
  //  vol = 0;
  waveform1.amplitude(vol);

  #define FREQ_LO 20.0
  #define FREQ_HI 750.0
  //float freq = constrain(map((float)analogRead(FREQ_PIN), 1023.0 * 0.1, 1023 * 0.9, FREQ_LO, FREQ_HI), FREQ_LO, FREQ_HI);
  freq = map(freq, 0.0, 1.0, FREQ_LO, FREQ_HI);
  waveform1.frequency(freq);


  delay(10);
}

