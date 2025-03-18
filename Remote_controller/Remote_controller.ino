#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int throttle, yaw, pitch, roll;
int buttonPinRight = 2;
int buttonPinLeft = 10;

int ReconnectButton = 10;


int xValRight;
int yValRight;
int xValLeft;
int yValLeft;
int buttonStateRight;
int buttonStateLeft;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int OutputArray[4];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(buttonPinRight, INPUT_PULLUP);
  pinMode(buttonPinLeft, INPUT_PULLUP);

  pinMode(ReconnectButton,INPUT);
////////////////////////////
  radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_HIGH);
    radio.stopListening();
    delay(10);

}

void loop() {
  
  // if (ReconnectButton == HIGH){
  
  // }
    // put your main code here, to run repeatedly:
  throttle = analogRead(A1);  // Left joystick vertical axis
  yaw = analogRead(A0);       // Left joystick horizontal axis
  pitch = analogRead(A3);     // Right joystick vertical axis
  roll = analogRead(A2);      // Right joystick horizontal axis
  buttonStateRight = digitalRead(buttonPinRight);
  buttonStateLeft = digitalRead(buttonPinLeft);

  int controls[4] = {
    constrain(map(throttle, 0, 1023, 0, 2000),1000,2000), //positive y is 0 while negative y is 1023 in a joystick also throttle joystick it is upside down in the RC
    map(yaw, 0, 1023, 500, -500), //positive x is 1023 while negative x is 0 in a joystick
    map(pitch, 0, 1023, 500, -500), 
    map(roll, 0, 1023, -500, 500)
  };
    // Calculate individual motor speeds based on throttle and joystick values
    //  motorspeed  = throttle      pitch         tilt          yaw
    int motorSpeed1 = controls[0] - controls[2] + abs(controls[3]) - controls[1];
    int motorSpeed2 = controls[0] - controls[2] - controls[3] + controls[1];
    int motorSpeed3 = controls[0] + controls[2] - controls[3] - controls[1];
    int motorSpeed4 = controls[0] + controls[2] + abs(controls[3]) + controls[1];
    int motorSpeed5 = controls[0] + controls[2] + controls[3] - controls[1];
    int motorSpeed6 = controls[0] - controls[2] + controls[3] + controls[1];  

    int motorSpeeds[6] = {motorSpeed1, motorSpeed2, motorSpeed3, motorSpeed4, motorSpeed5, motorSpeed6};

    for (int i = 0; i < 6; i++) {
    motorSpeeds[i]=constrain(motorSpeeds[i], 1000, 2000);
  } 
    
      // Serial.print("throttle ");
      // Serial.println(controls[0]);
      // Serial.print("yaw      ");
      // Serial.println(controls[1]);
      // Serial.print("pitch    ");
      // Serial.println(controls[2]);
      // Serial.print("tilt     ");
      // Serial.println(controls[3]);
     
  for (int i = 0; i < 6; i++) {
      Serial.print("motor[");
      Serial.print(i+1);
      Serial.print("]: ");
      Serial.println(motorSpeeds[i]);
      }
      Serial.println("------------------");

int ButtonState = digitalRead(ReconnectButton);
// if (ButtonState == LOW ){
//   Serial.println("HIGH");
//   }
// else{
//   Serial.println("LOW");
//   }  
  radio.write(&motorSpeeds, sizeof(motorSpeeds));
  delay(20);// Transmit every 20ms for smooth control
}

