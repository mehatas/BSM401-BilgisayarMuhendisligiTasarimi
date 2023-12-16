#include "arduino_secrets.h"
#include "thingProperties.h"
#include <Servo.h>

#define ISITMA D4
#define FIRIN D5

Servo myservo;

int inputPin = A0;
int sogutucu0 = 15;
int sogutucu1 = 13;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);

  pinMode(sogutucu0, OUTPUT);
  pinMode(sogutucu1, OUTPUT);
  pinMode(ISITMA, OUTPUT);
  pinMode(FIRIN, OUTPUT);

  myservo.attach(12);

  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  onSicaklikChange();
}

void onSogutmaChange()  {
  if (sogutma == true) {
    digitalWrite(sogutucu0, HIGH);
    digitalWrite(sogutucu1, LOW);
  }
  else {
    digitalWrite(sogutucu0, LOW);
    digitalWrite(sogutucu1, LOW);
  }
}
void onIsitmaChange() {
  if (isitma == true) {
    digitalWrite(ISITMA, HIGH);
  }
  else {
    digitalWrite(ISITMA, LOW);
  }
}

void onKapiChange()  {
  if (kapi == true) {
    myservo.write(180);
  }
  else {
    myservo.write(90);
  }
}

void onFirinChange()  {
  if (firin == true) {
    digitalWrite(FIRIN, HIGH);
  }
  else {
    digitalWrite(FIRIN, LOW);
  }
}

void onSicaklikChange()  {
  if (sicaklik == true) {
    int analogValue = analogRead(inputPin);
    float millivolts = (analogValue / 1024.0) * 3300;
    float celsius = millivolts / 10;
    if (celsius > 25) {
      digitalWrite(sogutucu0, HIGH);
      digitalWrite(sogutucu1, LOW);
      digitalWrite(ISITMA, LOW);
    }
    else if (celsius < 15) {
      digitalWrite(ISITMA, HIGH);
      digitalWrite(sogutucu0, LOW);
      digitalWrite(sogutucu1, LOW);
    }
    Serial.print("in DegreeC=   ");
    Serial.println(celsius);
    delay(1000);
  }
  else {
    onIsitmaChange();
    onSogutmaChange();
  }
}
