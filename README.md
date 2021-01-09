# KeyPad_Library
KeypadLibrary compatible with keypad 4x4, 3x4, 4x3, 3x3, based on STM32 architecture and compatible with HAL_LIBRARY and Standard Library.

### Technology Used

* [C] - c language.
* [KEIL] - Keil software.
* [MC] - STM32xx
* [Standard Library] - std periph library and HAL_Driver_Library

### How To Use IT
  * 1) Configure Row and Column Pins in **KeyBoardMatrix_def.h**.
  * 2) In your program the first you must call is **keyboardInit()** to initialize KeyPad GPIOS.
  * 3) Call **getKeyPressed()** function to get wich key was pressed.
  
License
MIT License

