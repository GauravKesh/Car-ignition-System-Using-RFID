# 🚗 Car Ignition System with RFID and Enhanced Security Features

## System Overview

Our project showcases a car ignition system utilizing RFID technology to enhance security. Authorized users receive RFID tags that interact with an RFID reader to either start the car or trigger an alarm in case of unauthorized access.

### Key Components:

- 🏷️ **RFID Tags:** Unique ID tags assigned to authorized users.
- 📡 **RFID Reader:** Checks if the presented tag is approved.
- ✅ **Authentication Process:** Starts the car for approved IDs. Triggers a buzzer and red light for unauthorized access.

## Hardware Components

- 🖥️ **Arduino Microcontroller:** Central unit controlling the system.
- 📟 **RFID Reader:** Reads RFID tags for authentication.
- 🏷️ **RFID Tags:** Assigned to each authorized user.
- 🔌 **Relay Module:** Controls the ignition switch based on authentication.
- 🔋 **Power Supply:** Provides power to all components.

## Software Components

- 💻 **Embedded C:** Code for integrating components and controlling the system.
- 📚 **RFID Library:** Manages communication between the Arduino and RFID reader.
- 💾 **EEPROM Storage:** Stores authorized RFID tag IDs and logs data.

## Future Prospects

### Planned Enhancements

- 📍 **GPS and GSM Technology:**
  - 📲 **SMS Notifications:** Sends vehicle's location to the owner upon correct key usage.
  - 🚨 **Unauthorized Access Alerts:** Immediate notifications for multiple wrong attempts.
- 🗺️ **Location Data Storage:**
  - 📜 **History Logging:** Stores location data in EEPROM for tracking.
  - 🛰️ **User-Friendly Format:** Converts raw GPS data into accessible formats like Google Maps links.

Example of Location Format:
- The location will be sent in a format like this: [Google Maps Link](https://lnkd.in/gh6buEky), enabling direct access to the car's location.

## Project Significance

This project demonstrates the integration of microcontrollers and RFID technology to create a secure and reliable car ignition system. The planned enhancements will further improve the system's functionality and security.

## Installation

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/car-ignition-system.git



2. **Upload the Code to Arduino:** Open the project in the Arduino IDE, connect your Arduino board, and upload the code.

## Wiring

Connect the RFID reader, relay module, and other components as per the provided schematics.

## Power Up

Connect the power supply to the Arduino and other components.

## Usage

- **Tag Registration:** Register authorized RFID tags by updating the EEPROM storage.
- **Starting the Car:** Present an authorized RFID tag to the reader. If authenticated, the relay module activates the ignition switch.
- **Unauthorized Access:** If an unauthorized tag is presented, the system triggers a buzzer and red light.

## Contributions

Feel free to fork this repository, create issues, or submit pull requests to improve the project. Your contributions are highly appreciated!

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contact

For any questions or suggestions, please reach out to us at gkrcoder@gmail.com.
