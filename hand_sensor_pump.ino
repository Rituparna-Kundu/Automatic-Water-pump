// Pin definitions
const int trigPin = 10;
const int echoPin = 11;
const int relayPin = 7;

// Distance threshold (in cm)
const int distanceThreshold = 10;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);

  // Active LOW relay: start with HIGH to keep the pump OFF
  digitalWrite(relayPin, HIGH);

  Serial.begin(9600);
}

void loop() {
  long duration;
  int distance;

  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH);

  // Convert to distance in cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 1. If a hand is detected (distance within the valid range)
  if (distance > 0 && distance <= distanceThreshold) {
    Serial.println("Hand detected! Starting pump for 5 seconds...");

    digitalWrite(relayPin, LOW);  // Pump ON (Active LOW)
    delay(5000);                  // Pump runs for exactly 5 seconds, no sensor readings taken
    digitalWrite(relayPin, HIGH); // Pump OFF after 5 seconds (Active LOW)
    Serial.println("5 seconds done. Pump OFF.");

    // 2. Wait-for-hand-removal loop (prevents the pump from restarting)
    // If the hand is still in front after 5 seconds, the code stays here
    while (true) {
      // Check again whether the hand is still in front of the sensor
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;

      // Exit the loop only when the hand is removed (distance is 0 or above the threshold)
      if (distance <= 0 || distance > distanceThreshold) {
        Serial.println("Hand removed. Ready for next cycle.");
        break;
      }

      delay(200); // Short pause between hand-removal checks
    }
  }

  delay(100); // General loop delay
}