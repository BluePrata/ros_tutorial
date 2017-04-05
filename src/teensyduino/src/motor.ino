#if (ARDUINO >=100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include <ros.h>
#include <ros/time.h>

#define E1 7  // Enable Pin for motor 1
//#define E2 11  // Enable Pin for motor 2

#define I1 5  // Control pin 1 for motor 1
#define I2 6  // Control pin 2 for motor 1
//#define I3 12  // Control pin 1 for motor 2
//#define I4 13  // Control pin 2 for motor 2

void setup() {
    nh.initNode();

    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);

    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);
}

void loop()
{
    analogWrite(E1, 153); // Run in half speed
    //analogWrite(E2, 255); // Run in full speed

    digitalWrite(I1, HIGH);
    igitalWrite(I2, LOW);


    delay(10000);

    // change direction

    digitalWrite(E1, LOW);


    delay(200);

    analogWrite(E1, 255);  // Run in full speed

    digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);

    delay(10000);
}
