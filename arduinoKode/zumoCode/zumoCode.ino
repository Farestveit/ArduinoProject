#include <ZumoMotors.h>
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>
#include <PLab_ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

ZumoMotors motors;

#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     100
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms


const int echoPin = 6;
const int triggerPin = 3;
const int LED_PIN = 13;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12


// edge ---------------

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors;
// --------------------

float distance = 0; // Store ultraSound measurements here to prevent delays jamming nav.
int edgy = 0; // Tracking variable for edge-detection.

 
void setup() {
  Serial.begin(9600);
  button.waitForButton();

  
  sensors.init();

  
  pinMode(LED_PIN, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
};
 
 
void loop() {
  distance = getDistance();
  edgy = edgeDetection();
  sensors.read(sensor_values);

  if (edgy) {
    // Rygg unna kanten.
    setSpeed(-400,-400);
    delay(150);
    edgy = 0; // Reset tracking variable after maneuvre.
    ledLight(1);
  }
  else{
    ledLight(0);
  };
  
  if (distance < 0.6) {
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

int edgeDetection() {
  // venstre: sensor_values[0]
  // høyre: sensor_values[5]
  if (sensor_values[0] < 10 ||sensor_values[5] < 10)
  {
    return 1;
  }
  else {
    return 0;
  }
  
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
