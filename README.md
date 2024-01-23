# CppGpioBackend
A C++ library for working with GPIO (General Purpose Input/Output) pins. This library provides a low-level, optimized, and flexible backend for controlling and reading data from GPIO pins. It is a wrapper around the MRAA library, allowing it to be used on boards such as the Raspberry Pi and BeagleBone. When developing on a PC, this library provides output via the terminal or an optional GUI.

## Features
Support for multiple platforms, including Raspberry Pi and BeagleBone, through the MRAA library.
Simple and easy-to-use API for controlling GPIO pins.
High-performance implementation optimized for real-time applications.
Support for interrupts, allowing you to detect changes in GPIO input states.
Extensive error handling to ensure reliable operation in production environments.
Terminal output for development on a PC, with an optional GUI for a visual representation of GPIO pin states.
## Installation
To install CppGpioBackend, follow these steps:

Clone the repository: git clone https://github.com/yourusername/CppGpioBackend.git
Build the library: cd CppGpioBackend && make
Install the library: sudo make install
Usage
Here's an example of how to use CppGpioBackend to control an LED connected to a GPIO pin:

c
Copy code
#include <CppGpioBackend/Gpio.h>
#include <iostream>

int main() {
using namespace CppGpioBackend;

// Create a GPIO object for pin 17
Gpio gpio(17);

// Configure the pin as an output
gpio.setDirection(Gpio::Direction::OUTPUT);

// Turn the LED on
gpio.setValue(Gpio::Value::HIGH);

std::cout << "LED is on!" << std::endl;

return 0;
}
For more information on how to use CppGpioBackend, please see the API reference documentation in the docs/ directory.

Contributing
We welcome contributions from the community! If you'd like to contribute, please read the contributing guidelines before getting started.

## License
CppGpioBackend is open-source software released under the GNU License.