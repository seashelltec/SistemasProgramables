
int RED =14;
int BLUE=13;
int GREEN=12;
void setup() {
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  analogWrite(RED, 255);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
  delay(1000);
  analogWrite(RED, 0);
  analogWrite(BLUE, 255);
  analogWrite(GREEN, 0);
  delay(1000);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 255);
  delay(1000);
}
