#include <ZumoMotors.h>

ZumoMotors motors;

const int echoPin = 2;
const int triggerPin = 3;
const int LED_PIN = 13;

float distance = 0;


 
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
};
 
 
void loop() {
  distance = getDistance();
  
  // TODO: Implementer logikk for å snu hvis teip.
  
  if (distance < 1) {
    // Fiende klokken tolv. Angrip!
    ledLight(1);
    setSpeed(400, 400);
    
  } else {
    // Let etter fiende.
    ledLight(0);
    setSpeed(200, -200);
  };
  delay(10);
};

float getDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.00017;
};

void setSpeed(int speed1, int speed2) {
  motors.setRightSpeed(speed1);
  motors.setLeftSpeed(speed2);
};

void ledLight (int light) {
  digitalWrite(LED_PIN, light);
};
