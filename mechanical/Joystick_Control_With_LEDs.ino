/* Read Jostick
   ------------

   Reads two analog pins that are supposed to be
   connected to a jostick made of two potentiometers

   We send three bytes back to the comp: one header and two
   with data as signed bytes, this will take the form:
       Jxy\r\n

   x and y are integers and sent in ASCII

   http://www.0j0.org | http://arduino.berlios.de
   copyleft 2005 DojoDave for DojoCorp
*/

int joyPin1 = A0;                 // slider variable connecetd to analog pin 0
int joyPin2 = A1;                 // slider variable connecetd to analog pin 1
int value1 = 0;                  // variable to read the value from the analog pin 0
int value2 = 0;                  // variable to read the value from the analog pin 1


int buttonPin = 2;     // the number of the joystick button pin
int buttonState = 0;         // variable for reading the joystick button status

#include <Servo.h>  //add '<' and '>' before and after servo.h
int servoPin = 5;
Servo servo;
int servoAngle = 0;   // servo position in degrees

/*-----( Import needed libraries )-----*/
#include <Stepper.h>
/*-----( Declare Constants, Pin Numbers )-----*/
//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 32
//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048  
// Then the pins are entered here in the sequence 1-3-2-4 for proper sequencing
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 8, 10, 9, 11);
int  Steps2Take;
int motorSpeed = 0;

#include <FastLED.h>
#define NUM_LEDS 60         //sets a macro definition so that anywhere that NUM_LEDS is seen later in the code gets replaced by 60
#define DATA_PIN 6          //DATA_PIN is set to 6
CRGB leds[NUM_LEDS];        //This sets up an array that we can manipulate to set/clear led data.

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(buttonPin, INPUT_PULLUP);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);    //This tells the library that there's a strand of NEOPIXEL's on pin 6 and those leds will use the led array leds, and there are NUM_PIXELS

}

int treatValue(int data) {
  return (data * 9 / 1024) + 48;
}

void loop() {

  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    // Button pushed
    servo.write(85);      // Turn SG90 servo Left to 45 degrees
    Serial.print("Down");
    Serial.print("\t");
  } else {
    // Button not pushed
    servo.write(115);      // Turn SG90 servo back to 90 degrees (center position)
    Serial.print("Up");
    Serial.print("\t");
  }

  // reads the value of the variable resistor
  value1 = analogRead(joyPin1);
  // this small pause is needed between reading
  // analog pins, otherwise we get the same value twice
  delay(100);
  // reads the value of the variable resistor
  value2 = analogRead(joyPin2);

  Serial.print (value1);
  Serial.print("\t");
  Serial.println (value2);


  if (value1 >= 615 && value1 <= 950) {
    Steps2Take  = - STEPS_PER_OUTPUT_REVOLUTION / 200;  // Rotate CCW
    small_stepper.setSpeed(350);
    small_stepper.step(Steps2Take);
    //    for (int dot = 0; dot < NUM_LEDS; dot++) {
    //      FastLED.setBrightness( 50);
    //      leds[dot] = CRGB::Red;
    //    }
    leds[0] = CRGB::Red;
    FastLED.show();

  }
  if (value1 > 950) {
    Steps2Take  = - STEPS_PER_OUTPUT_REVOLUTION / 50;  // Rotate CW
    small_stepper.setSpeed(700);
    small_stepper.step(Steps2Take);
    //    for (int dot = 0; dot < NUM_LEDS; dot++) {
    //      FastLED.setBrightness(255);
    //      leds[dot] = CRGB::Red;
    //
    //    }
    leds[0] = CRGB::Red;
    FastLED.show();
  }
  if (value1 <= 410 && value1 >= 60) {
    Steps2Take  = STEPS_PER_OUTPUT_REVOLUTION / 200;  // Rotate CW
    small_stepper.setSpeed(350);
    small_stepper.step(Steps2Take);
    //    for (int dot = 0; dot < NUM_LEDS; dot++) {
    //      FastLED.setBrightness(50);
    //      leds[dot] = CRGB::Blue;
    //    }
    leds[0] = CRGB::Blue;
    FastLED.show();

  }
  if (value1 < 110) {
    Steps2Take  = STEPS_PER_OUTPUT_REVOLUTION / 50;  // Rotate CW
    small_stepper.setSpeed(700);
    small_stepper.step(Steps2Take);
    //    for (int dot = 0; dot < NUM_LEDS; dot++) {
    //      FastLED.setBrightness(255);
    //      leds[dot] = CRGB::Blue;
    //    }
    leds[0] = CRGB::Blue;
    FastLED.show();

  }

  else {
    //    for (int dot = 0; dot < NUM_LEDS; dot++) {
    //      FastLED.setBrightness(255);
    //      leds[dot] = CRGB::Black;
    //    }
    leds[0] = CRGB::Black;
    FastLED.show();

  }
}

