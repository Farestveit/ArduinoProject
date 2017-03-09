const int echoPin = 7;
const int triggerPin = 6;
 
void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
 
void loop() {
  Serial.println(ultraSound());
  delay(100);
}

float ultraSound() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.00017;
  
  if (distance > 1) {
    return ultraSound();
  }
  else {
    return distance;
  };
};
