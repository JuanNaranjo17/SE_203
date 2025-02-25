# Juan Carlos Naranjo Jaramillo

Repository of the subject Outils, langages et pratique des systèmes à microprocesseurs.

## TD project

For this project, the development was done using arm-none-eabi-gcc, a cross-compilation toolchain specifically designed for ARM-based microcontrollers like the STM32L475VGT6. This toolchain allows for efficient compilation, linking, and debugging of embedded C code for ARM architecture. It supports a variety of optimization options and integrates well with low-level hardware programming, making it ideal for working with the STM32 microcontroller. The toolchain was used in conjunction with makefiles for building the project and managing dependencies efficiently.

This project involves the development of code for the STM32L475VGT6 microcontroller, focusing on a variety of peripheral functionalities. Key components include:

* Clock Management: Configuring the system clock to ensure stable operation.
* LED Control: Driving an LED matrix, utilizing functions for initialization and pixel manipulation.
* USART Communication: Establishing serial communication at 38400 baud for data exchange.
* Interrupt Handling: Using external interrupts for button presses and internal interrupts for timers.
* Timer Management: Configuring timers for precise delays and periodic tasks.

Additionally, the project integrates image rendering and manipulation on an LED matrix by testing images from external memory. It serves as a practical demonstration of managing various embedded system tasks, handling real-time operations, and interacting with hardware peripherals on the STM32L475VGT6 microcontroller.
