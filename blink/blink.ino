/*
  Simple test code for the Wemos D1 RGBW Shield.
  https://github.com/RiRomain/wemos-rgbw-shield
*/

#define RED_PIN D5
#define GREEN_PIN D6
#define BLUE_PIN D7
#define WHITE_PIN D8

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(WHITE_PIN, OUTPUT);
  Serial.begin(115200);
}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Turning red ON");
  analogWrite(RED_PIN, PWMRANGE);
  delay(3000);
  analogWrite(RED_PIN, 0);

  Serial.println("Turning green ON");
  analogWrite(GREEN_PIN, PWMRANGE);
  delay(3000);
  analogWrite(GREEN_PIN, 0);

  Serial.println("Turning blue ON");
  analogWrite(BLUE_PIN, PWMRANGE);
  delay(3000);
  analogWrite(BLUE_PIN, 0);

  Serial.println("Turning white ON");
  analogWrite(WHITE_PIN, PWMRANGE);
  delay(3000);
  analogWrite(WHITE_PIN, 0);

  Serial.println("Turning RGB ON");
  analogWrite(RED_PIN, PWMRANGE);
  analogWrite(GREEN_PIN, PWMRANGE);
  analogWrite(BLUE_PIN, PWMRANGE);
  delay(3000);

  Serial.println("Turning all channel ON");
  analogWrite(WHITE_PIN, PWMRANGE);
  delay(3000);
  analogWrite(RED_PIN, 0);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN, 0);
  analogWrite(WHITE_PIN, 0);

}
