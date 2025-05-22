# DAC Output with Button Control 

This project demonstrates the use of the Digital-to-Analog Converter (DAC) on the STM32L4 Nucleo board. A pushbutton is used to increment and decrement the DAC output voltage, which is then read back by the ADC. The system adjusts LED brightness based on this feedback.

## Features

- DAC setup on PA4 (DAC1 Channel 1)
- Output analog voltage in 12-bit resolution (0–4095)
- Button-controlled voltage increment/decrement
- Feedback loop using ADC (on PA1) to monitor DAC output
- Real-time LED brightness control based on DAC value

## Hardware Requirements

- STM32L4 Nucleo Board  
- Breadboard and jumper wires  
- Pushbutton (user button on Nucleo or external)  
- USB cable for power/debug  
- Jumper wire: PA4 connected to PA1

## Circuit Setup

| Signal        | Pin       |
|---------------|-----------|
| DAC Output    | PA4       |
| ADC Input     | PA1       |
| Button Input  | PC13 (user button) |
| LED Output    | Onboard green LED |

- PA4 and PA1 should be connected with a jumper wire

## Configuration Summary

- DAC Output Pin: PA4
- DAC Resolution: 12-bit
- DAC Trigger: Software (trigger disabled)
- ADC Input Pin: PA1 
- DAC Mode: Normal mode with buffer enabled
- Button: External interrupt on falling edge

## Behavior

- Each button press increases DAC output by a fixed increment until max value is reached
- Once maximum is hit, direction reverses and next press decreases output
- At minimum, direction reverses again to increase output
- LED brightness updates according to the voltage read by the ADC on PA1

## Output Range

- DAC output: 0 V to 3.3 V
- DAC steps: (e.g., 100 per press → ~80 steps full range)
- LED brightness follows DAC value linearly
