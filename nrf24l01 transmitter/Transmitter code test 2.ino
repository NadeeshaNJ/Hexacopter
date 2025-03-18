#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo esc1, esc2, esc3, esc4, esc5, esc6;     // create servo object to control the ESC
int controls[4];

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
    // Attach the ESC on pins 9,2,3,4,5,6 on clockwise order in the hexacopter
  esc1.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  esc2.attach(2,1000,2000);
  esc3.attach(3,1000,2000);
  esc4.attach(4,1000,2000);
  esc5.attach(5,1000,2000);
  esc6.attach(6,1000,2000);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5);
  if (radio.available()) {
    int InputArray[4];
    radio.read(&text, sizeof(text));
  }
}