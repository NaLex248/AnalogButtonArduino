/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/arduino-analog-button-array-example

   This example reads the pressed button from an array of buttons connected to single analog pin and prints it to Serial Monitor.

   ***************************************************************

   Debounce modification from NaLex Software, 2023

   nalexsoft@gmail.com
*/

#include <ezAnalogKeypad.h>

#define ADC_MAX 1023 // 10-bit ADC
#define ANALOG_KEYS_PIN A0 // analog pin
#define BUTTON_DEBOUNCE 50 // debounce, ms
#define VOLTAGE_INVERSION // uncomment for voltage inversion

ezAnalogKeypad buttonArray(ANALOG_KEYS_PIN);  // create ezAnalogKeypad object that attach to analog pin

bool buttOn = false;

void setup() {
  Serial.begin(9600);

  // MUST READ: You MUST run the calibration example, press button one-by-one to get the analog values
  // The below values is just an example, your button's value may be different
#ifdef VOLTAGE_INVERSION
  buttonArray.setNoPressValue(ADC_MAX);  // analog value when no button is pressed
#else
  buttonArray.setNoPressValue(0);  // analog value when no button is pressed
#endif
  buttonArray.registerKey(1, 512); // analog value when the button 1 is pressed
  buttonArray.registerKey(2, 341); // analog value when the button 2 is pressed
  buttonArray.registerKey(3, 256); // analog value when the button 3 is pressed
  buttonArray.registerKey(4, 205); // analog value when the button 4 is pressed
  buttonArray.registerKey(5, 170); // analog value when the button 5 is pressed

  // ADD MORE IF HAS MORE
}

void loop() {
  static const int adcMaxOffset = ADC_MAX * 0.01; // 1% offset setup
#ifdef VOLTAGE_INVERSION
  bool butt = analogRead(ANALOG_KEYS_PIN) < (ADC_MAX - adcMaxOffset);
#else
  bool butt = analogRead(ANALOG_KEYS_PIN) > adcMaxOffset;
#endif
  if (butt && !buttOn) {
    buttOn = true;
    delay(BUTTON_DEBOUNCE);

    unsigned char button = buttonArray.getKey();
    if (button) {
      Serial.print("The button ");
      Serial.print((int)button);
      Serial.println(" is pressed");
    }
  }
  if (!butt && buttOn) {
    buttOn = false;
    delay(BUTTON_DEBOUNCE);
    buttonArray.getKey();
  }
}
