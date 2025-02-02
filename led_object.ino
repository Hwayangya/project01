// Pin definitions for the first ultrasonic sensor
const int trigPin1 = 24;
const int echoPin1 = 22;

// Pin definitions for the second ultrasonic sensor
const int trigPin2 = 28;
const int echoPin2 = 26;

// LED pin
const int ledPin = 32;

// Threshold distance in mm
const int thresholdDistance = 10;

// Time window for the second detection in milliseconds
const int detectionWindow = 2000;

bool firstSensorDetected = false; // Tracks if the first sensor detected an object
unsigned long firstDetectionTime = 0; // Stores the time of the first detection

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set ultrasonic sensor pins as input/output
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Set LED pin as output
  pinMode(ledPin, OUTPUT);

  // Turn off the LED initially
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Measure distance using the first ultrasonic sensor
  long distance1 = measureDistance(trigPin1, echoPin1);

  // Check if the first sensor detects an object within the threshold
  if (!firstSensorDetected && distance1 <= thresholdDistance) {
    Serial.println("First sensor detected an object!");
    firstSensorDetected = true;
    firstDetectionTime = millis(); // Record the time of first detection
  }

  // If the first sensor has detected an object, check the second sensor
  if (firstSensorDetected) {
    // Measure distance using the second ultrasonic sensor
    long distance2 = measureDistance(trigPin2, echoPin2);

    // Check if the second sensor detects an object within the time window
    if (distance2 <= thresholdDistance && (millis() - firstDetectionTime <= detectionWindow)) {
      Serial.println("Second sensor detected an object within the time window!");
      digitalWrite(ledPin, HIGH); // Turn on the LED
      Serial.println("1");
      delay(2000); // Keep the LED on for 2 seconds
      digitalWrite(ledPin, LOW); // Turn off the LED
      Serial.println("0");
      firstSensorDetected = false; // Reset for the next detection
    }

    // If time window has elapsed and second sensor did not detect
    if (millis() - firstDetectionTime > detectionWindow) {
      Serial.println("Time window elapsed. Resetting...");
      firstSensorDetected = false; // Reset for the next detection
    }
  }

  delay(100); // Small delay for stability
}

// Function to measure distance using an ultrasonic sensor
long measureDistance(int trigPin, int echoPin) {
  // Send a 10-microsecond pulse to trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin and calculate the distance
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration * 0.0343) / 2; // Convert to mm
  return distance;
}