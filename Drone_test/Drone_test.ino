#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo esc1, esc2, esc3, esc4, esc5, esc6;     // create servo object to control the ESC
int motorSpeeds[6];

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
    // Attach the ESC on pins 9,2,3,4,5,6 on clockwise order in the hexacopter
  esc1.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  esc2.attach(2,1000,2000);
  esc3.attach(3,1000,2000);
  esc4.attach(4,1000,2000);
  esc5.attach(5,1000,2000);
  esc6.attach(6,1000,2000);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()) {
    radio.read(&motorSpeeds, sizeof(motorSpeeds));
       for (int i = 0; i < 6; i++) {
      Serial.print("|");
      Serial.print(i);
      Serial.print("| ");
      Serial.println(motorSpeeds[i]);
    }
    Serial.println("------------");
    // Write scaled motor speeds to ESCs
    esc1.writeMicroseconds(motorSpeeds[0]);
    esc2.writeMicroseconds(motorSpeeds[1]);
    esc3.writeMicroseconds(motorSpeeds[2]);
    esc4.writeMicroseconds(motorSpeeds[3]);
    esc5.writeMicroseconds(motorSpeeds[4]);
    esc6.writeMicroseconds(motorSpeeds[5]);
  }
}

