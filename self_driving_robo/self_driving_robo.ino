#include <Servo.h>

#define trigPin 9
#define echoPin 8

// Motor pins
#define motorLeftForward 7
#define motorLeftBackward 6
#define motorRightForward 5
#define motorRightBackward 4

#define irLeft 2
#define irRight 3

Servo myServo;
long duration;
int distance;

// Functions to control motors
void moveForward() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
}

void turnLeft() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
}

void turnRight() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, LOW);
}

void stopCar() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, LOW);
}

void setup() {
  // Set motor pins as output
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);

  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo motor to pin 12
  myServo.attach(12);
  myServo.write(90); // Start with the servo at the center
  Serial.begin(9600);
}

void loop() {
  int leftSensor = digitalRead(irLeft);
  int rightSensor = digitalRead(irRight);

  // Check for line following condition
  if (leftSensor == HIGH && rightSensor == HIGH) {
    // Both sensors detect white surface, move forward
    moveForward();
  } else if (leftSensor == LOW && rightSensor == HIGH) {
    // Left sensor detects black (robot veering right), turn left
    turnLeft();
  } else if (leftSensor == HIGH && rightSensor == LOW) {
    // Right sensor detects black (robot veering left), turn right
    turnRight();
  } else if (leftSensor == LOW && rightSensor == LOW) {
    // Both sensors detect black (possibly off track), stop
    stopCar();
  }

  // Check for obstacles
  distance = getDistance();
  if (distance < 200) { // If obstacle detected within 20 cm
    avoidObstacle();
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int dist = duration * 0.032 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  
  return dist;
}

void avoidObstacle() {
  stopCar();
  delay(500);

  // Rotate servo to scan surroundings
  myServo.write(0);  // Check the right side
  delay(500);
  int rightDistance = getDistance();

  myServo.write(180);  // Check the left side
  delay(500);
  int leftDistance = getDistance();

  // Choose the direction with more space
  if (leftDistance > rightDistance) {
    turnLeft();
    delay(500);  // Adjust turning duration
  } else {
    turnRight();
    delay(500);
  }

  myServo.write(90);  // Reset servo to center
}
