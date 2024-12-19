# Bidirectional Brushed Motor ESC with ATtiny85

This project is a bidirectional Electronic Speed Controller (ESC) for brushed DC motors, designed around the ATtiny85 microcontroller. 
The ESC interprets standard RC PWM signals to control motor speed and direction through an H-bridge MOSFET configuration. The project 
is structured with code in the Arduino framework and provides an initial simulation schematic to help users understand and test the design. 
A printed circuit board (PCB) schematic is currently under development.

Features

Bidirectional Motor Control: Control motor direction and speed through an RC PWM signal.
PWM Signal Interpretation: Reads input PWM signals from an RC receiver and converts the pulse width into a motor control output.
H-Bridge Configuration: Utilizes a MOSFET H-bridge for robust and efficient motor control.
Compact ATtiny85 Design: Built around the ATtiny85 microcontroller, making it ideal for small-scale or embedded projects.
Project Structure
Firmware: Contains Arduino-based code for interpreting PWM signals and driving the motor.
Simulation: Provides a simulation schematic to visualize the circuit layout and operation.
PCB Schematic (in progress): Ongoing development of a PCB layout to improve the compactness and usability of the ESC.

Code Overview

The firmware is designed to:

Interpret PWM signals from a standard RC transmitter.
Map the PWM signal to control motor speed and direction.
Drive the H-bridge using PWM outputs from the ATtiny85.

Setup and Usage

ATtiny85 Pin Configuration:

Input Pin: Reads PWM signal from RC receiver.
Output Pins (H-Bridge Control): Control the direction and speed of the motor through an H-bridge MOSFET configuration.

Connections:

Connect the RC PWM signal to the designated input pin on the ATtiny85.
H-bridge connections from the output pins to the MOSFETs as shown in the simulation schematic.

Flashing the Code:

Upload the Arduino-based code to the ATtiny85.
Ensure that the baud rate in the code matches the communication requirements if using serial for debugging.

Operation:

The ESC will interpret the RC signal pulse width and adjust motor speed and direction accordingly.
Default Safety: If the input pulse is out of range, the motor output will default to zero for safety.

Files in Repository

Firmware: Source code for the ATtiny85, compatible with the Arduino framework.
Simulation Schematic: Visual reference for wiring and component placement.
PCB Design: (In progress) Schematic and layout for creating a compact, ready-to-deploy ESC.

Future Improvements

Finalizing and testing the PCB layout.
Additional testing with different RC signal ranges and H-bridge configurations.
Implementing potential features like fault detection and fail-safes.
Enabling the Serial communication by resolving bug.
