Wii Mouse Project Description

Overview

This project will create a device that allows the Wii Nunchuck to function as generic HID USB mouse. The device has a  female Wii Nunchuck connector on one end and a male USB type-A connector on the other. After connecting the Wii Nunchuck (wire or wireless) to the device and the device to a PC ( Mac, Linux?), the Wii Nunchuck controls the PC’s mouse pointer.

The device also has a customized driver. A user application with a GUI uses this driver to:
Update the device’s firmware
Calibrate the device
Modify the device’s settings


Development Areas
This project requires the following development areas:
Device firmware
Driver software
User application software
PCB
Website
Promotional video


Firmware:
The firmware is written in C and divided into two areas: kernel space and device space.
- Kernel space contains all core functionality such as the microcontroller bootloader, interrupt vectors, UART, I2C, EEPROM, core USB features. This is the code that executes on startup or reset. The kernel contains the bare minimum required functionality as it remains static (i.e. is never updated during a firmware update).

- Device space contains the main functionality of the device. This includes WiiNunchuck algorithms and settings, USB settings. The device space is overwritten with each firmware update. The device space code starts at a known address. This address is the entry point into the device space. All calls from kernel space start here.

Driver Software:
The driver software is written in C and implemented as a DLL providing an API to the WiiMouse. It uses WinUSB, a generic kernel mode USB driver provided by Microsoft, to communicate with the device via USB. The driver software will provide the following functionality:
Connect/disconnect from the device
Update the device firmware
Retrieve/update the device settings
Receive continuous device mouse information (X/Y position, left/right button status, etc)
Calibrate the device


User Application:
The user application is written in Java and provides a GUI interface for the user. It uses JNA to interface with the driver software.

Website:
The website is written in (PHP?). It provides a detailed description of the Wii Mouse, links to the YouTube promotional video, Ebay listing, and PayPal purchasing site.

Promotional Video:
The video will show the Wii Mouse in action, demonstrating all it capabilities.