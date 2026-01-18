# Microcontroller-Based RFID Access Control System

## Project Overview
Designed and prototyped a contactless security system to address vulnerabilities in traditional cylinder locks. This project explores RFID technology to reduce reliance on physical keys, utilizing an Arduino microcontroller to grant access via key cards.

## Technical Implementation
* **Embedded System Integration:** Integrated an Arduino Uno, MFRC522 RFID module (**SPI protocol**), and a 16x2 LCD (**I2C bus**) to manage system status.
* **Firmware Logic:** Developed C++ firmware to handle UID authentication. Implemented dynamic key assignment logic where the system initializes the first scanned tag as the "Master Key."
* **Electromechanical Control:** Interfaced a servo motor to simulate a physical latching mechanism, calibrating PWM signals for precise 90-degree actuation.

## Documentation
* [**Full Engineering Report**](./Docs/Engineering_Report.pdf) - *Includes Abstract, Methodology, and Vulnerability Assessment.*
* [**Schematic Diagram**](./Docs/Schematic_Diagram.pdf)

## Key Features
* **SPI & I2C Communication:** Optimized pin usage by leveraging different communication protocols for the reader and display.
* **Dynamic Key Assignment:** System allows for "Master Key" reset upon startup.
* **Visual Feedback:** LCD integration provides real-time "Access Granted/Denied" status.

## Future Improvements
* **Non-Volatile Storage:** Moving UID storage to EEPROM to retain keys after power loss.
* **Power Optimization:** Implementing interrupt-based sleep modes to extend battery life beyond the current 9V limitations.
