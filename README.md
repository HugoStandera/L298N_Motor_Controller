# Arduino Motor Control Project

An Arduino-based motor control system developed as part of an elctromechanical devices and interfacing project.  
The system uses user input to control a DC motor via a motor driver and external components.

## Features

- Controls a DC motor using an Arduino Uno.
- Motor speed adjusted via a potentiometer.
- Motor operation controlled using a push-button input.
- Uses an L298N motor driver for safe motor control.
- Demonstrates basic hardware–software integration.

## Equipment & Components

### Equipment
- Arduino Uno  
- L298N Motor Driver  
- DC Motor  
- DC Power Supply  

### Components
- Potentiometer – 1× 2 kΩ  
- Resistor – 1× 10 kΩ  
- Push-button  
- Jumper wires  

## Hardware Setup

The hardware setup consists of an Arduino Uno connected to an L298N motor driver, which controls a DC motor powered by an external DC supply.  
User input is provided via a potentiometer (for speed control) and a push-button (for motor control).

Refer to the included image for the physical hardware layout.

## How It Works

- The Arduino reads the potentiometer value as an analogue input.
- The input value is mapped to control the motor speed.
- The push-button enables or disables motor operation.
- The L298N motor driver handles current delivery to the motor.

## Notes

- This project requires the specified hardware setup to function.
- Circuit diagram provided as part of the E.D.I. laboratory materials. Used here for documentation purposes only.
