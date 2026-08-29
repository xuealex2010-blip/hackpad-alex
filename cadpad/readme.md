# cadpad

An open source numpad and macropad combination designed for CAD design work.
Sponsored by YSWS program from Hack Club.


Keyboard Maintainer: [Alex](https://github.com/lightgoldsquare-blip)
Hardware Supported: SEEED XIAO RP2040
Hardware Availability: Files available on github: https://github.com/lightgoldsquare-blip

Make example for this keyboard (after setting up your build environment):

    make cadpad:default

Flashing example for this keyboard:

    make cadpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. 
## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
