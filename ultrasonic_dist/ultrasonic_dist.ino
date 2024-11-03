#include <LiquidCrystal.h>

// Initialize the LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);  // Set up the LCD's number of columns and rows
  
  // Set up the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Display a startup message
  lcd.setCursor(0, 0); // Set cursor to column 0, row 0
  lcd.print("Distance:");
  delay(1000);         // Wait for a second
}

void loop() {
  long duration, distance;

  // Send a 10us pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin and calculate the distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Convert duration to distance in cm

  // Clear the second line and display the distance
  lcd.setCursor(0, 1);      // Set cursor to column 0, row 1
  lcd.print("Dist: ");
  lcd.print(distance);      // Print the distance value
  lcd.print(" cm   ");      // Add units

  delay(500);  // Update the reading every 500ms
}
