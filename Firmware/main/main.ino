#include <SoftwereSerial.h>

// Define the RX and TX pins for NeoSWSerial
SoftwereSerial mySerial(4, 3);  // RX, TX pins for NeoSWSerial

// Pin definitions
const uint8_t INPUT_PIN = 2;  // PB2 on ATtiny85 (Input from RC receiver)
const uint8_t OUT1_PIN = 0;   // PB0 on ATtiny85 (Output 1 for H-bridge)
const uint8_t OUT2_PIN = 1;   // PB1 on ATtiny85 (Output 2 for H-bridge)

// Variables
volatile unsigned long lastTime = 0;   // Last time the rising edge was detected
volatile unsigned long pulseWidth = 1500; // Stores pulse width in microseconds (default to 1.5ms for safety)
uint8_t pwmDuty = 0;                   // Stores duty cycle (0-100%) derived from RC input

void setup() {
  // Set output pins
  pinMode(OUT1_PIN, OUTPUT);
  pinMode(OUT2_PIN, OUTPUT);
  
  // Initialize output pins to LOW
  digitalWrite(OUT1_PIN, LOW);
  digitalWrite(OUT2_PIN, LOW);

  // Set input pin
  pinMode(INPUT_PIN, INPUT);

  // Attach interrupt on INT0 (External Interrupt 0 on PB2)
  attachInterrupt(0, handlePWMInput, CHANGE);

  // Start NeoSWSerial with specified baud rate
  mySerial.begin(2400);  // Use 9600 baud, or adjust as needed
  delay(100);            // Short delay to stabilize the serial setup
  mySerial.println("ESC INITIATED"); // Test message
}

void loop() {
  // Map pulse width to duty cycle (0-100%)
  if (pulseWidth >= 1000 && pulseWidth <= 2000) {
    pwmDuty = map(pulseWidth, 1000, 2000, 0, 100);
  } else {
    pwmDuty = 0; // Default to 0% if pulse is out of range
  }

  // Set outputs based on the duty cycle from the RC receiver
  if (pwmDuty >= 50) {
    // For input 50% to 100%: OUT1 stays LOW, OUT2 has PWM from 0 to 100%
    analogWrite(OUT1_PIN, 0); // OUT1 stays low
    analogWrite(OUT2_PIN, map(pwmDuty, 50, 100, 0, 255)); // OUT2 varies from 0% to 100% duty cycle
  } else {
    // For input 0% to 49%: OUT1 has PWM from 0 to 100%, OUT2 stays LOW
    analogWrite(OUT1_PIN, map(pwmDuty, 0, 49, 255, 0)); // OUT1 varies from 0% to 100% duty cycle
    analogWrite(OUT2_PIN, 0); // OUT2 stays low
  }
  
  delay(20); // Slightly longer delay for stability
}

void handlePWMInput() {
  if (digitalRead(INPUT_PIN) == HIGH) {
    // Rising edge detected
    lastTime = micros(); // Record the time at the rising edge
  } else {
    // Falling edge detected
    pulseWidth = micros() - lastTime; // Calculate the pulse width
  }
}
