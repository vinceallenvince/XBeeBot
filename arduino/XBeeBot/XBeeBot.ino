#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include <Servo.h>

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

Servo servoLeft;
Servo servoRight;

static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };
    
void setup () {
  Serial.begin(57600);
  matrix.begin(0x70);  // pass in the address
  matrix.clear();
  
  servoLeft.attach(9);
  servoLeft.writeMicroseconds(1500);
  
  servoRight.attach(10);
  servoRight.writeMicroseconds(1500);
}

void loop() {
  
  if (Serial.available() > 0) {
    int data = Serial.read() - '0';
    
    if (data == 1) {
      servoLeft.writeMicroseconds(1000);
      servoRight.writeMicroseconds(2000);
    }
    
    if (data == 2) {
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(2000);
    }

    if (data == 3) {
      servoLeft.writeMicroseconds(2000);
      servoRight.writeMicroseconds(1000);
    }

    if (data == 4) {
      servoLeft.writeMicroseconds(1000);
      servoRight.writeMicroseconds(1500);
    }
    
    if (data == 5) {
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
    }
    
    if (data == 6) {
        matrix.clear();
        matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_GREEN);
        matrix.writeDisplay();
    } else if (data == 7) {
        matrix.clear();
        matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_YELLOW);
        matrix.writeDisplay();      
    } else if (data == 8) {
        matrix.clear();
        matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_RED);
        matrix.writeDisplay();    
    } else if (data == 9) {
        matrix.clear();
        matrix.drawRect(0,0, 8,8, LED_RED);
        matrix.fillRect(2,2, 4,4, LED_GREEN);
        matrix.writeDisplay();    
    }
    
    Serial.print(data);
  }
}




