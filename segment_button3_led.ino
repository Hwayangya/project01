int btn = A5;  // Existing button (A5)
int btn1 = A3; // New button
int pushBtn = A7; // Push button to stop countdown
int num1 = 0, num2 = 3;  // Countdown digits
int counter = 0;         // Counter for the new button
int FND2[7] = {41, 42, 43, 44, 45, 46, 47};  // FND2: 10's digit pins
int FND1[7] = {34, 35, 36, 37, 38, 39, 40};  // FND1: 1's digit pins
int FND_data[10] = {0xC0, 0xF9, 0xA4, 0xB0,  // FND data for 0-9
                    0x99, 0x92, 0x82, 0xF8,
                    0x80, 0x90};
bool isCounting = false; // Countdown status flag
bool btn1Pressed = false; // Track if the new button is pressed
bool pushBtnPressed = false; // Track if push button is pressed
unsigned long buttonPressStart = 0;  // Track button press duration
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
  Serial.begin(9600); // Initialize serial monitor

  // Initialize button pins
  pinMode(btn, INPUT_PULLUP);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(pushBtn, INPUT_PULLUP);
  
  // 초음파 센서
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Set LED pin as output
  pinMode(ledPin, OUTPUT);

  // Initialize FND pins
  for (int i = 0; i < 7; i++) {
    pinMode(FND1[i], OUTPUT);
    pinMode(FND2[i], OUTPUT);
    digitalWrite(FND1[i], HIGH);
    digitalWrite(FND2[i], HIGH);
  }

  // Display initial counter value
  displayNumber(counter / 10, counter % 10);
  // Turn off the LED initially
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Handle new button press
  if (!digitalRead(btn1)) {
    if (!btn1Pressed) {
      btn1Pressed = true;
      buttonPressStart = millis();
    }
    if (millis() - buttonPressStart >= 200) {
      btn1Pressed = false;
      counter++;
      if (counter > 7) counter = 7; // Limit counter to 7
      displayNumber(counter / 10, counter % 10); // Display counter on 7-segment display
    }
  } else {
    btn1Pressed = false;
  }

  // Handle push button press to stop countdown (only during countdown)
  if (isCounting && !digitalRead(pushBtn)) {
    if (!pushBtnPressed) {
      pushBtnPressed = true;
      stopCountdown(); // Stop countdown and handle the display logic
    }
  } else {
    pushBtnPressed = false;
  }

  // Handle existing button press to start countdown
  if (counter > 0 && !digitalRead(btn) && !pushBtnPressed) {
    if (millis() - buttonPressStart >= 200) {
      while (!digitalRead(btn)); // Wait for button release

      resetCountdown(); // Reset countdown
      isCounting = true; // Start countdown
    }
  }

  // Handle countdown logic
  if (isCounting) {
    displayNumber(num2, num1); // Show countdown
    delay(1000); // Wait 1 second

    if (num1 == 0) {
      if (num2 > 0) {
        num1 = 9;
        num2--;
      } else {
        // num2 == 0 && num1 == 0
        displayNumber(0, 0); // Show `00`
        delay(3000); // Hold for 3 seconds

        // After 3 seconds, decrement the counter and display the new button counter value
        counter--; 
        if (counter < 0) counter = 0; // Prevent counter from going negative
        displayNumber(counter / 10, counter % 10); // Display the counter value
        isCounting = false; // Stop countdown
      }
    } else {
      num1--;
    }
  }

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

// Stop countdown and display interrupted value
void stopCountdown() {
  if (!isCounting) return; // Only stop if counting

  isCounting = false;
  displayNumber(num2, num1); // Show interrupted countdown value
  delay(3000); // Wait for 3 seconds
  counter--; // Decrease counter by 1
  if (counter < 0) counter = 0; // Prevent counter from going negative
  displayNumber(counter / 10, counter % 10); // Show the new button counter value
}

// Reset countdown to 30 seconds
void resetCountdown() {
  num1 = 0;
  num2 = 3;
}

// Display numbers on the 7-segment display
void displayNumber(int tens, int ones) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(FND2[i], bitRead(FND_data[tens], i));
    digitalWrite(FND1[i], bitRead(FND_data[ones], i));
  }
}

// Turn off 7-segment display
void displayOff() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(FND2[i], HIGH);
    digitalWrite(FND1[i], HIGH);
  }
}