# CADPAD

A Numberpad with navigation controls with a secondary macro layer. Made to improve my CAD experience.

<img width="1403" height="1241" alt="Screenshot_20260824_121713" src="https://github.com/user-attachments/assets/55af7a9f-fbdc-472d-863b-1474fc101c6b" />

## Navigation Knob

Featuring navigation accessibility especially for when entering numbers. 

The arrow key outputs give a tactile way to move around the numbers to correct mistakes on the same input device. The tab button also allows for quick navigation between text fields.

<img width="2588" height="2304" alt="Screenshot_20260829_170127" src="https://github.com/user-attachments/assets/fb54316c-bc99-4d84-b504-3e9d8c447bc7" />

## PCB and Schematic Design

The Schematic and PCB can also be viewed HERE >>
https://kicanvas.org/?repo=https%3A%2F%2Fgithub.com%2Fxuealex2010-blip%2Fhackpad-alex%2Ftree%2Fmain%2FPCB

### Schematic Overview

The GPIO pins are optimized to support a larger 4x5 matrix, making this design able to be used for even more projects.

The encoder switch is wired into the matrix to reduce the pins used.

<img width="969" height="1241" alt="Screenshot_20260824_121826" src="https://github.com/user-attachments/assets/b128ca72-f7d0-4bef-b92e-795bef0ccfcd" />

### PCB (GND Fill Hidden)

This design also makes use of 2 special hybrid footprints.

The **Hybrid Switch** footprint supports both MX style and Choc switches, making the design more customizable.

The **Hybrid Diode** which I actually created myself supports common SOD-123 and Through Hole 1N4148 diodes to make it fit the users choice.

<img width="968" height="1241" alt="Screenshot_20260829_163841" src="https://github.com/user-attachments/assets/0fa8d44c-a43d-445e-b478-3140d686845b" />

### PCB Render

<img width="1153" height="1298" alt="Screenshot_20260829_163910" src="https://github.com/user-attachments/assets/be071666-6e69-4d81-a21d-435937168825" />


## Case Assembly
Using a sandwich mount for ease of assembly.

The case is also designed with a slight tilt to make the front lip lower to be more comfortable.

The advantage of 3D printing also means that if I want to use different keyswitches, the complex PCB can remain the same, the case can be further customized for that setup.

<img width="1001" height="1379" alt="Screenshot_20260829_172108" src="https://github.com/user-attachments/assets/07b6df96-0c6a-49cf-98ac-8012022a19ae" />

## Keymap

The layout for the Cadpad follows the common number arrangement of calculators, helping muscle memory carry over.

The `.` and `Enter` keys also utilize QMK's Tap Dance feature.

`.` When double clicked will register a backspace input, this was chosen since a double decimal is not used.

`Enter` acts as the layer modifier when held, accessing the extra function buttons set for macros, as well as common volume controls with the encoder.

<img width="397" height="488" alt="Screenshot_20260830_122651" src="https://github.com/user-attachments/assets/1c0909b7-0a10-4dba-9d4b-b29cdf691c91" />

