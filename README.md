# Interactive Display with Keypad and LCD on Arduino

This project demonstrates the use of a 4x4 keypad, a 4-digit 7-segment display (using the TM1637 driver), and a 16x2 I2C LCD with Arduino. It provides multiple modes of interaction, including segment blinking, ADC value display, and interrupt-driven countdown, all navigated via keypad input or a push button.

## Features

- **4x4 Keypad Control**: Navigate between modes and trigger display actions.
- **16x2 I2C LCD**: Shows current mode and status messages.
- **4-Digit 7-Segment Display (TM1637)**: Displays numbers, blinking patterns, and segment control.
- **Push Button Interrupt**: Initiates a countdown from 9 to 0 on the 7-segment display.
- **ADC Value Display**: Read and display analog values from pin A0.
- **Multiple display modes**: Easily switch between different display behaviors using the keypad.

## Hardware Requirements

- Arduino board (Uno, Nano, etc.)
- 4x4 Matrix Keypad
- TM1637 4-Digit 7-Segment Display
- 16x2 I2C LCD
- Push button
- Connecting wires

## Wiring Overview

- **Keypad**: Connect rows to pins 3, 4, 5, 6 and columns to pins 7, 8, 9, 10.
- **TM1637 Display**: CLK to pin 12, DIO to pin 13.
- **LCD**: Connect via I2C (default address 0x27).
- **Push Button**: Connect to pin 2 (with INPUT_PULLUP).
- **Analog Input**: Use pin A0 for ADC readings.

## How to Use

1. **Power up the Arduino**. The LCD will display initialization messages.
2. **Default Mode**: The system starts in "Mode 1", showing segment patterns on the 7-segment display.
3. **Keypad Controls**:
    - Press `'1'` to enter ADC mode. The LCD will show the ADC reading from pin A0, and the 7-segment will display its value.
    - Press `'5'` to enter Blink mode. The 7-segment display will blink all segments.
    - Press `'C'` at any time in ADC or Blink mode to return to the default mode.
4. **Push Button Interrupt**:
    - Press the button connected to pin 2 to trigger the interrupt mode. The LCD shows "SUCCESS" and the 7-segment display counts down from 9 to 0.

## File Overview

- **main.ino**: The main Arduino sketch containing all initialization, mode management, interrupt handling, and display logic.

## Important Notes

- The code uses several third-party libraries: `TM1637Display`, `Keypad`, and `LiquidCrystal_I2C`. Please install these in your Arduino IDE before uploading.
- The code and comments are documented in Indonesian; this README summarizes the features and usage in English.
- You can modify pin assignments in the code to match your hardware setup.

## License

This project is open-source and free to use. Check the repository for further information on licensing.

## Credits

Developed by [JustFTan](https://github.com/JustFTan).
