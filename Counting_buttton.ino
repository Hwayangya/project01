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
int isCounting = 0;  // Countdown status flag
int isDisplayingSerial = 0; // Prevent interaction during serial output
unsigned long countdownStartTime = 0; // Track countdown start time
unsigned long buttonPressStart = 0;  // Track button press duration
unsigned long pushButtonPressStart = 0;  // Track push button press duration
bool btn1Pressed = false; // Track if the new button is pressed
bool pushBtnPressed = false; // Track if push button is pressed
bool isCounterDisplayed = false; // Flag to check if counter is displayed

void setup() {
  Serial.begin(9600); // Initialize serial monitor

  // Initialize button pins
  pinMode(btn, INPUT_PULLUP);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(pushBtn, INPUT_PULLUP); // Push button for interrupt

  // Initialize FND pins
  for (int i = 0; i < 7; i++) {
    pinMode(FND1[i], OUTPUT);
    pinMode(FND2[i], OUTPUT);
    digitalWrite(FND1[i], HIGH);
    digitalWrite(FND2[i], HIGH);
  }

  // Display initial counter value
  displayNumber(counter / 10, counter % 10);
}

void loop() {
  if (isDisplayingSerial || isCounterDisplayed) {
    return; // Prevent interaction during serial output or counter display
  }

  // Handle new button press
  if (!digitalRead(btn1) && !pushBtnPressed) {
    if (!btn1Pressed) {
      btn1Pressed = true;
      buttonPressStart = millis();
    }
    if (millis() - buttonPressStart >= 200) {
      btn1Pressed = false;
      counter++;
      if (counter > 7) {
        counter = 7; // Limit counter to 7
      }
      displayNumber(counter / 10, counter % 10); // Display counter on 7-segment display

      if (counter >= 2) {
        isDisplayingSerial = 1;
        Serial.print("ONE MORE? Counter: ");
        Serial.println(counter);
        delay(2000); // Display serial message for 2 seconds
        isDisplayingSerial = 0;
      }
    }
    return;
  } else {
    btn1Pressed = false;
  }

  // Handle push button press
  if (!digitalRead(pushBtn)) {
    if (!pushBtnPressed) {
      pushBtnPressed = true; // Push button is pressed
      pushButtonPressStart = millis(); // Record press start time
    }
    if (millis() - pushButtonPressStart >= 200) {
      stopCountdown(); // Stop the countdown
      isCounterDisplayed = true; // Display the interrupted counter for 3 seconds
    }
  } else {
    pushBtnPressed = false; // Reset push button press state
  }

  // Handle existing button press to start countdown
  if (counter > 0 && !digitalRead(btn) && !pushBtnPressed) {
    if (millis() - buttonPressStart >= 200) { // Only trigger if pressed for more than 0.2 seconds
      while (!digitalRead(btn)); // Wait for button release

      resetCountdown(); // Reset countdown
      isCounting = 1; // Start countdown
      countdownStartTime = millis();
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
        isCounting = 0; // Stop countdown
      }
    } else {
      num1--;
    }
  }
}

// Stop countdown and display interrupted value
void stopCountdown() {
  isCounting = 0;
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
