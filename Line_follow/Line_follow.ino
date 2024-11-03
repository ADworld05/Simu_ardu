const int rightSensorPin = 10; 
const int leftSensorPin = 12;  

const int motor1Pin1 = 7;  // Motor 1 (IN1)
const int motor1Pin2 = 6;  // Motor 1 (IN2)
const int motor2Pin1 = 5;  // Motor 2 (IN3)
const int motor2Pin2 = 4;  // Motor 2 (IN4)

void setup() {
  // Initialize motor pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Initialize sensor pins as input
  pinMode(rightSensorPin, INPUT);
  pinMode(leftSensorPin, INPUT);
}

void loop() {
  // Reading the sensor values
  int rightSensorValue = digitalRead(rightSensorPin);
  int leftSensorValue = digitalRead(leftSensorPin);

  // If both sensors are on the line, move forward
  if (rightSensorValue == LOW && leftSensorValue == LOW) {
    moveForward();
  }
  // If only the right sensor is on the line, turn left
  else if (rightSensorValue == LOW && leftSensorValue == HIGH) {
    turnLeft();
  }
  // If only the left sensor is on the line, turn right
  else if (rightSensorValue == HIGH && leftSensorValue == LOW) {
    turnRight();
  }
  // If both sensors are off the line, stop
  else {
    stopMotors();
  }
}

void moveForward() {
  // Move both motors forward
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnLeft() {
  // Stop left motor, move right motor forward
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnRight() {
  // Stop right motor, move left motor forward
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void stopMotors() {
  // Stop both motors
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
