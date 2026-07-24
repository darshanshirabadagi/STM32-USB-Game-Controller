# STM32 USB Game Controller

A custom USB HID game controller built using the **STM32F103C8 Blue Pill**. The controller emulates a USB keyboard and mouse, allowing it to control PC games without requiring additional drivers.

## Features

- Dual analog joysticks
- USB HID Keyboard and Mouse
- WASD movement
- Mouse cursor control
- Left and Right mouse click
- Multiple programmable buttons
- Plug-and-play on Windows
- Built using Arduino IDE

## Hardware

- STM32F103C8 (Blue Pill)
- 2 × Analog Joysticks
- Push Buttons
- USB Cable

## Pin Connections

### Joysticks

| Function | STM32 Pin |
|----------|-----------|
| Left Joystick X | PA0 |
| Left Joystick Y | PA1 |
| Right Joystick X | PA2 |
| Right Joystick Y | PA3 |

### Buttons

| Function | STM32 Pin |
|----------|-----------|
| Enter | PA4 |
| Esc | PA5 |
| Backspace | PA6 |
| Left Shift | PA7 |
| Left Ctrl | PB0 |
| Windows | PB1 |
| R | PB10 |
| E | PB11 |
| F | PB12 |
| Tab | PB13 |
| C | PB14 |
| V | PB15 |
| Arrow Up | PA8 |
| Arrow Down | PA9 |
| Arrow Left | PA10 |
| Arrow Right | PA15 |
| Left Mouse Click | PB3 |
| Right Mouse Click | PB4 |

## Folder Structure

```
Code/
Images/
Videos/
Circuit_Diagram/
```

## Future Improvements

- Add a complete circuit schematic
- Design and manufacture a custom PCB
- Add support for additional HID features
- Create a 3D-printed enclosure

## License

This project is released under the MIT License.
