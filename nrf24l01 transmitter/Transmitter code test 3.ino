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
    scaleMotorSpeeds(motorSpeeds, 1000, 2000,controls);  
    
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
  delay(800);
 radio.write(&motorSpeeds, sizeof(motorSpeeds));
    // Transmit every 20ms for smooth control
}

void scaleMotorSpeeds(int motorSpeeds[], int minSpeed, int maxSpeed, int controls[]) {
  // Find the maximum speed in the array
  int maxMotorSpeed = motorSpeeds[0];
  int minMotorSpeed = motorSpeeds[0];
  for (int i = 1; i < 6; i++) {
    if (motorSpeeds[i] > maxMotorSpeed) {
      maxMotorSpeed = motorSpeeds[i];
    }
    if (motorSpeeds[i] < minMotorSpeed) {
      minMotorSpeed = motorSpeeds[i];

    }

  }
    // Serial.println(maxMotorSpeed);
    // Serial.println(minMotorSpeed);
  // Scale all motor speeds if maxMotorSpeed exceeds max limit
  if (maxMotorSpeed > maxSpeed /*|| minMotorSpeed < minSpeed*/) {
    // float scaleFactor = (float)(maxSpeed-controls[0]) / (maxMotorSpeed-controls[0]); //controls[0] is throttle
    // Serial.println(scaleFactor);

    for (int i = 0; i < 6; i++) {
      // motorSpeeds[i] = controls[0] + (int)((motorSpeeds[i] - controls[0]) * scaleFactor);
      // Serial.println((int)((motorSpeeds[i] - controls[0]) * scaleFactor));
      motorSpeeds[i]=constrain(motorSpeeds[i], 1000, 2000);
    }
  }
}
