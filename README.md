# <p align="center">ELECTRONICS ENGINEERING PROGRAM</p>
## <p align="center">ECEN 309: Digital Electronics 2: Microprocessor, Microcontroller Systems and Design</p>


## <p align="center">DESIGN PROJECT</p>
## <p align="center">Title: IoT Environmental Monitoring and Control with ESP32 and ESP RainMaker</p>


Leader:
<p align="center">                      Calvo, Shamyr Ivan</p>


Members:
<p align="center">1.	Abela, Mark Lawrence
<p align="center">2.	Canobas, Marc Angelo 
<p align="center">3.	Janega, Aj
<p align="center">4.	Tagustos, Aaron
<p align="center">5.	Parala, Justin Raphael

Facilitator:
<p align="center">                             Engr. Isagani G. Garcia

<p align="center"><ins>June 13, 2025</ins>
<p align="center">Date</p>
<br/><br/><br/>
<br/><br/><br/>
## Introduction and Project Overview
<br/><br/>
<p align="justify">The rapid advancement of the Internet of Things (IoT) has made it possible to develop intelligent, interconnected systems capable of monitoring and controlling physical environments in real time. This project focuses on the design and implementation of a comprehensive IoT-based environmental monitoring and control system, leveraging the powerful ESP32 microcontroller in conjunction with the ESP Rainmaker cloud platform. The system aims to provide an accessible, scalable solution for monitoring ambient environmental conditions and remotely managing actuators such as fans, LEDs, or relays through a user-friendly mobile application.</p>
<p align="justify">At its core, the system integrates multiple environmental sensors (e.g., temperature, humidity, pressure) with actuators (e.g., relays or motor drivers) on the ESP32 platform. Sensor data is collected periodically, processed locally on the device, and then published to the ESP Rainmaker cloud using a secure MQTT-based communication channel. This enables real-time data visualization, historical logging, remote control, and smart automation via the ESP Rainmaker mobile application, available on both Android and iOS platforms.
Key functionalities and capabilities of the system include:</p>

* Wi-Fi Provisioning and Cloud Connectivity: The ESP32 device is securely provisioned to a local Wi-Fi network using the Rainmaker app, either via QR code scanning or SoftAP (Soft Access Point) mode. Once provisioned, the device establishes a persistent, encrypted connection with the ESP Rainmaker cloud.

*	Sensor Data Acquisition and Real-Time Logging: The system interfaces with at least two distinct environmental sensors (e.g., DHT22 for temperature/humidity and BMP280 for pressure), acquiring sensor readings at defined intervals. These readings are transmitted to the Rainmaker cloud and visualized in the app, allowing users to track environmental conditions in real time.

*	Remote Actuator Control: Through the Rainmaker mobile app, users can remotely control connected actuators such as a relay switch that operates an LED or cooling fan. This interaction is facilitated via parameter changes in the Rainmaker data model, which are handled dynamically by the firmware.

*	Custom Parameters and Data Model Integration: The firmware defines custom parameters and attributes for each sensor and actuator, making it easy to configure and visualize each device’s status, state, and function through the cloud interface.

*	Automations and Smart Scheduling: The system supports intelligent automation based on sensor readings—for example, automatically turning on a fan when the temperature exceeds a predefined threshold. Additionally, users can set up scheduled tasks (e.g., turning a light on at 6:00 PM and off at 10:00 PM) using the app’s intuitive interface.

*	Over-the-Air (OTA) Firmware Updates: One of the most critical features of a robust IoT system is the ability to push firmware updates remotely. This system integrates Rainmaker’s OTA service to allow secure, wireless deployment of new firmware images, enabling bug fixes, feature enhancements, or security patches without physical access to the device.

*	End-to-End Security and Device Management: Using Espressif's cloud infrastructure, the system ensures secure authentication, encrypted data transmission, and user-device binding, providing a reliable and safe user experience.

<p align="justify">By combining embedded systems development with cloud-based IoT infrastructure, this project provides a complete, real-world example of an intelligent environmental monitoring solution. It not only demonstrates fundamental skills in hardware interfacing, real-time data processing, and mobile-cloud integration, but also explores advanced IoT features such as automation, scheduling, and OTA, which are critical in deploying scalable and maintainable IoT solutions in smart homes, greenhouses, industrial environments, and more.
 
## System Architecture Diagram
<p align="justify">The system architecture is designed to enable seamless integration between hardware components and cloud-based services for real-time environmental monitoring and remote control. The core elements of the architecture and their roles are described below:

-	ESP32 Microcontroller - The ESP32 serves as the central processing unit of the system. It is responsible for interfacing with sensors and actuators, collecting and processing sensor data, executing control logic, and communicating securely with the cloud. Leveraging the ESP Rainmaker SDK, it supports device provisioning, parameter management, and remote firmware updates.

-	Environmental Sensors - Sensors such as the DHT22 (for temperature and humidity) or the BMP280 (for atmospheric pressure and temperature) are connected to the ESP32 via GPIO or I²C interfaces. These sensors continuously monitor ambient environmental conditions, and their data is periodically read, processed, and published to the cloud.

-	Actuators - Actuation components such as a relay module or an LED are also connected to the ESP32 via digital GPIO pins. These components are controlled either manually through the mobile app or automatically via pre-defined automation rules (e.g., turning on a fan when temperature exceeds a threshold).
  
-	Wi-Fi Connectivity - The ESP32 connects to the internet using Wi-Fi, which enables real-time communication with the ESP Rainmaker cloud. Secure communication protocols ensure that data transmission and remote-control commands are protected from unauthorized access.
  
-	ESP Rainmaker Cloud Platform - Hosted by Espressif, the Rainmaker cloud platform acts as the backend infrastructure for the IoT system. It handles secure device provisioning, parameter synchronization, user association, real-time data streaming, scheduling, automation logic, and Over-the-Air (OTA) firmware updates. It also maintains persistent MQTT sessions with the device.
  
-	ESP Rainmaker Mobile App - Available on Android and iOS, the Rainmaker app provides a user-friendly interface for provisioning new devices, monitoring live sensor data, controlling actuators, setting automation triggers and schedules, and initiating OTA updates. It serves as the primary human-machine interface for the IoT system.

<br/><br/><br/>
 
<p align="center">
<img src="https://github.com/user-attachments/assets/feb2cc85-1e59-4b5c-80ea-92ce9f04bf12"/>
</p>

<br/><br/><br/>

Hardware Design Details
Components Used:
1. ESP32-WROOM-32
-	Type: Wi-Fi + Bluetooth SoC microcontroller module
-	Core: Dual-core Tensilica Xtensa LX6 @ up to 240 MHz
-	RAM: 520 KB SRAM
-	Flash: 4MB (typical)
-	I/O: ~30 GPIOs (ADC, DAC, UART, SPI, I2C, PWM, etc.)
-	Operating Voltage: 3.3V (logic level)
-	Power Supply: 5V input via regulator, or 3.3V direct
2. DHT22 (AM2302) – Temperature and Humidity Sensor
-	Temperature Range: -40 to +80°C, ±0.5°C accuracy
-	Humidity Range: 0–100%, ±2-5% accuracy
-	Power Supply: 3.3V to 6V
-	Signal: Single-wire digital (custom protocol)
-	Pull-up: Requires 10kΩ resistor on data line
3. LED
-	Type: Standard 5mm LED (red, green, etc.)
-	Forward Voltage: ~2V (varies by color)
-	Current: ~10–20 mA
-	Usage: Connected with current-limiting resistor (e.g., 1kΩ)
4. 1kΩ Resistor
-	Use: Current limiting for LEDs or base resistor for transistors
-	Power Rating: 1/4W typical
-	Tolerance: ±5% (carbon film), ±1% (metal film)
5. Buzzer
-	Type: Active (with built-in oscillator) or passive (needs PWM)
-	Voltage: 3.3V to 5V
-	Current: ~10–30 mA
-	Control: ON/OFF via GPIO (active), or tone() PWM (passive)
6. SRD-05V Relay
-	Type: SPDT (Single Pole Double Throw)
- Coil Voltage: 5V DC
-	Contacts: COM, NO (Normally Open), NC (Normally Closed)
-	Control: Needs transistor or optocoupler interface
-	Current Handling: Up to 10A @ 250VAC / 30VDc
7. HW-611 (BME280) – Environmental Sensor
-	Measures: Temperature, Humidity, Pressure
-	Interface: I2C or SPI
-	Voltage: 3.3V (some modules 5V tolerant with regulator)
-	Accuracy:
    -	Temp: ±1.0°C
    -	Humidity: ±3%
    -	Pressure: ±1 hPa
8. LM2596 DC-DC Buck Converter
-	Input Voltage: 4V – 40V
-	Output Voltage: Fixed 12V
-	Output Current: Up to 3A (with heat sinking)
-	Features: Voltage adjustment via potentiometer, onboard LED for power indication
9. 9V Battery
-	Type: 9V (PP3), typically alkaline or rechargeable (NiMH)
-	Nominal Voltage: 9V (drops as it discharges)
-	Capacity:
    -	~500–600 mAh (alkaline)
    -	~200–300 mAh (rechargeable)
-	Output: Unregulated DC voltage
10. Fan
-	Type: DC Brushless Fan (commonly 5V or 12V)
-	Voltage: Typically 5V or 12V (must match power source)
-	Current: 100–300 mA (depends on size and speed)
-	Control:
    -	Simple ON/OFF via relay
    -	Speed control possible via PWM (for 3-wire/4-wire fans)
-	Usage: Air circulation or cooling in enclosures

GPIO Assignments:
- GPIO4 is connected to the DHT22 sensor's DATA pin, used for reading temperature and humidity data.

- GPIO5 is used to drive both an LED and a buzzer in parallel through a 1kΩ resistor. When set high, it activates both components.
- GPIO18 controls the relay module (SRD-05VDC-SL-C). This relay switches a 9V-powered DC fan, allowing the ESP32 to turn the fan on or off.
- GPIO21 serves as the I²C SDA line, connected to the BMP280 sensor (HW-611).
- GPIO22 is the I²C SCL line, also connected to the BMP280 sensor for clock signaling


Wiring/Schematic:

<br/><br/>

<p align="center">
<img src="https://github.com/user-attachments/assets/696b5686-4b2f-46fc-a7b4-b8f2a7c2a6a6"/>
</p>

<br/><br/>
 
## Software Design Details

<p>Firmware Structure and Logic</p>

<p align="justify">The firmware for this IoT system is developed using the ESP-IDF (Espressif IoT Development Framework) and tightly integrates the ESP Rainmaker SDK, providing a robust framework for cloud connectivity, real-time control, and scalable IoT deployment. The firmware is structured in a modular fashion to ensure maintainability, clarity, and ease of extension.

<p>The application is organized into the following key components:</p>

-	System Initialization: Handles startup routines including GPIO initialization, I²C configuration, non-volatile storage setup, and system logging.

-	Sensor Management: Encapsulates the logic for reading environmental data from connected sensors (e.g., DHT22, BMP280). Includes error handling, retry mechanisms, and data formatting.

-	Rainmaker Integration Handlers: Responsible for provisioning, parameter registration, cloud communication, and managing user-device interactions via MQTT.

-	Actuator Control: Manages GPIO-based control of physical actuators (e.g., relays, LEDs) in response to user commands or automated triggers.
  
<p>Key Rainmaker Integration Steps</p>

<p>To enable seamless communication with the ESP Rainmaker cloud, the following integration steps are implemented:</p>

-	Parameter and Device Definition: Each sensor and actuator is represented as a Rainmaker device. Parameters (e.g., temperature, humidity, power state) are defined using the esp_rmaker_param_create() API and linked to their devices using esp_rmaker_device_add_param().

-	Callback Registration: Actuator devices are configured with write callbacks using esp_rmaker_device_add_cb() to handle remote control commands sent from the mobile app or automation routines.
  
-	Device Registration and Node Configuration: Devices and parameters are grouped under a Rainmaker node, which is registered and published to the cloud.
  
<p>Sensor Reading Logic</p>

-	Sensor readings are performed periodically using FreeRTOS timers or tasks to ensure non-blocking operation and efficient CPU utilization.
  
-	Each reading cycle collects data from connected sensors (e.g., temperature from DHT22, pressure from BMP280) and processes or filters it as needed.
  
-	The processed data is reported to the RainMaker cloud using the esp_rmaker_param_update_and_report() function, ensuring real-time visibility on the mobile app dashboard.

<p>Actuator Control Logic</p>

-	The firmware monitors parameter updates received from the Rainmaker cloud, such as ON/OFF commands for a relay.
  
-	When an actuator parameter changes, the registered callback function is invoked. The logic inside this callback uses GPIO output to control physical actuators (e.g., energizing a relay coil to activate a fan).
  
-	State synchronization ensures that the local state of the actuator is consistent with the cloud state, providing a reliable and accurate user experience.

<br/><br/>

##Implementation Challenges and Solutions

<p>Challenge 1: Unstable Sensor Readings</p>

<p align="justify"> Solution: Implemented a moving average filter to smooth out noise from sensor data and added debounce logic to prevent false triggers from transient fluctuations.

<p>Challenge 2: Wi-Fi Provisioning Failures</p>

<p align="justify"> Solution: Adopted SoftAP provisioning mode with a QR code fallback mechanism to enhance user accessibility, and reinforced error handling for more robust connectivity setup.
  
<p>Challenge 3: RainMaker Attribute Synchronization Issues</p>

<p align="justify"> Solution: Ensured reliable parameter registration and enforced strict data type matching during firmware initialization to maintain consistent synchronization with the RainMaker cloud.
  
<p>Challenge 4: OTA Update Failure Due to Binary Size</p>

<p align="justify"> Solution: Reduced firmware size by eliminating redundant modules and activating partition compression, allowing successful over-the-air (OTA) updates within memory constraints.

<br/><br/>

##Demonstration of Functionality

<p>Each project requirement has been successfully met:</p>

<br/><br/>

<table>
  <tr>
    <th>Requirement</th>
    <th>Status</th>
    <th>Description</th>
  </tr>
  <tr>
    <th>ESP32 Cloud Connection</th>
    <th>✅</th>
    <th>Device connects to RainMaker cloud and retains session.</th>
  </tr>
  <tr>
    <th>Wi-Fi Provisioning</th>
    <th>✅</th>
    <th>Successfully done via QR code and SoftAP.</th>
  </tr>
  <tr>
    <th>Sensor Integration</th>
    <th>✅</th>
    <th>DHT22 and BMP280 data visible in RainMaker app.</th>
  </tr>
  <tr>
    <th>Actuator Control</th>
    <th>✅</th>
    <th>Relay toggles based on app command.</th>
  </tr>
  <tr>
    <th>Custom Parameters</th>
    <th>✅</th>
    <th>Defined temperature, humidity, and relay power attributes.</th>
  </tr>
  <tr>
    <th>Real-time Data</th>
    <th>✅</th>
    <th>Continuously updates on the app dashboard.</th>
  </tr>
  <tr>
    <th>Automation</th>
    <th>✅</th>
    <th>E.g., Relay turns on if temperature exceeds threshold.</th>
  </tr>
  <tr>
    <th>Scheduling</th>
    <th>✅</th>
    <th>E.g., Relay turns on daily at 8 AM.</th>
  </tr>
  <tr>
    <th>OTA Updates</th>
    <th>✅</th>
    <th>Successfully pushed new firmware via the RainMaker app.</th>
  </tr>
</table>

<br/>

<p>Screenshots</p>

<br/>

<p align="center">
<img src="https://github.com/user-attachments/assets/9411c656-17e7-4c0d-9446-f0b67b636cb2"/>

<img src="https://github.com/user-attachments/assets/c05d1c9e-977f-492d-9ecb-326ef7e797ae"/>
</p>

<br/><br/>

<p align="center">
<img src="https://github.com/user-attachments/assets/e980a5ef-54f6-48a3-bebe-1c2f0e8b16e8"/>

<img src="https://github.com/user-attachments/assets/cb952364-0dee-48d3-9aa3-a78d92b055c0"/>
</p>

<br/><br/>

<p align="center">
<img src="https://github.com/user-attachments/assets/53db7364-e339-4d90-9d0a-e0aa14b49ddf"/>
</p>

<br/><br/>

##Lessons Learned and Future Work

Lessons Learned:

-	Importance of modular firmware design.
-	Hands-on experience with embedded cloud integration.
-	Deep understanding of OTA and security considerations.

Future Work:

-	Add more sensors (e.g., CO2, gas sensors).
-	Enhance the mobile app interface using custom widgets.
-	Implement a local fallback UI using Bluetooth or web interface.
-	Migrate to ESP32-S3 for additional performance and USB capabilities.

References:

-	Espressif Systems. ESP RainMaker Documentation
-	Espressif Systems. ESP-IDF Programming Guide
-	Open-source sensor libraries (e.g., DHT22 driver from Adafruit, BMP280 by Bosch)
 

