# NVIC Programming on TIVA C LaunchPad

## Overview
This project demonstrates NVIC (Nested Vectored Interrupt Controller) programming on the TIVA C LaunchPad (EK-TM4C123GXL, TM4C123GH6PM microcontroller). It configures multiple interrupts—SysTick for periodic timing and GPIO for button presses—with different priorities, toggling the onboard RGB LEDs (PF1, PF2, PF3) to indicate interrupt events. The project showcases embedded systems skills, including interrupt handling, priority configuration, and GPIO control, with applications in real-time systems and event-driven programming.

### Features
- Configures GPIO interrupts on PF0 and PF4 (onboard buttons) to toggle the green (PF1) and green (PF3) LEDs.
- Sets different interrupt priorities using the NVIC to demonstrate preemption.
- Sets the system clock to 16 MHz for accurate timing.

## Hardware Requirements
- **TIVA C LaunchPad**: EK-TM4C123GXL with TM4C123GH6PM microcontroller.
- **Onboard Components**:
  - RGB LED: Connected to PF1 (red), PF2 (blue), PF3 (green).
  - Push Buttons: SW1 on PF4, SW2 on PF0.
- **Optional External Components**:
  - External LED (with a 330-ohm resistor) and push button for additional testing.
  - Connections (if using external components):
    - External LED Anode → PA2 (or any GPIO pin)
    - External LED Cathode → GND (via resistor)
    - External Button → PA3 (or any GPIO pin) to GND (with pull-up resistor)

## Software Requirements
- **Code Composer Studio (CCS)**: Version 12.4.0 or later.
- **TivaWare**: Optional (this project uses direct register access for educational purposes).
- **Compiler**: TI ARM Compiler (included with CCS).

## Setup Instructions
1. **Hardware Setup**:
   - No additional connections are needed if using the onboard RGB LEDs and buttons.
   - If using external components, connect them as described above.
   - Power the LaunchPad via USB.
2. **Software Setup**:
   - Clone or download this repository.
