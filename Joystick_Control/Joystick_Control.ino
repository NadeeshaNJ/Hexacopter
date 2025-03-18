int yPinRight = A0;
int xPinRight = A1;
int yPinLeft = A2;
int xPinLeft = A3;
int buttonPinRight = 2;
int buttonPinLeft = 3;

int xValRight;
int yValRight;
int xValLeft;
int yValLeft;
int buttonStateRight;
int buttonStateLeft;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(xPinRight, INPUT);
  pinMode(yPinRight, INPUT);
  pinMode(xPinLeft, INPUT);
  pinMode(yPinLeft, INPUT);
  pinMode(buttonPinRight, INPUT_PULLUP);
  pinMode(buttonPinLeft, INPUT_PULLUP);


}

void loop() {
  // put your main code here, to run repeatedly:
  xValRight = analogRead(xPinRight);
  yValRight = analogRead(yPinRight);
  xValLeft = analogRead(xPinLeft);
  yValLeft = analogRead(yPinLeft);
  buttonStateRight = digitalRead(buttonPinRight);
  buttonStateLeft = digitalRead(buttonPinLeft);

  int inputValues[] = { xValLeft, yValLeft+4, xValRight+15, yValRight-7};
  int outputValues; 

  for (int element : inputValues){
    outputValues = map(element, -5, 1030, -10, 10);
    Serial.print(outputValues);
    Serial.print(" | ");
  }
  Serial.println("");



  // Serial.print("Rx: ");
  // Serial.print(xValRight);
  // Serial.print(" | Ry: ");
  // Serial.print(yValRight);
  // Serial.print(" || Lx: ");
  // Serial.print(xValLeft);
  // Serial.print(" | Ly: ");
  // Serial.print(yValLeft);
  // Serial.print(" || Button> R: ");
  // Serial.print(buttonStateRight);
  // Serial.print(" L: ");
  // Serial.println(buttonStateLeft);



  delay(100);

}
