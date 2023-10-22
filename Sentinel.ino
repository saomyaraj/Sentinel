#include <Servo.h>

// Define ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Define motor control pins
const int leftMotor1 = 5;
const int leftMotor2 = 6;
const int rightMotor1 = 10;
const int rightMotor2 = 11;

// Create a Servo object for the servo motor
Servo servoMotor;

void setup() {
  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Initialize motor control pins
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  
  // Attach the servo motor to pin 3
  servoMotor.attach(3);
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Calculate the distance from the ultrasonic sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;  // Divide by 29.1 to convert to centimeters

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Set a distance threshold for obstacle avoidance
  int threshold = 20; // Adjust as needed

  if (distance < threshold) {
    // Obstacle detected, change direction
    Serial.println("Obstacle detected!");
    moveBackward();
    delay(1000);
    turnRight();
  } else {
    // No obstacle, move forward
    moveForward();
  }
}

// Move the robot forward
void moveForward() {
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}

// Move the robot backward
void moveBackward() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
}

// Turn the robot to the right
void turnRight() {
  servoMotor.write(180); // Rotate the servo motor to turn right
  delay(500); // Adjust the delay for the turn duration
  servoMotor.write(90); // Bring the servo motor back to the center position
}
