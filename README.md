# iot-temp-humidity-monitor-esp8266
### Minor Project | GlowLogics Solutions Pvt. Ltd. Internship 2025-26
This project is a wireless environmental monitoring system designed to provide timely tracking of ambient temperature and relative humidity. It utilizes an ESP8266 NodeMCU to process digital signals from a DHT11 sensor and transmits the data to a cloud-based analytics platform for remote visualization.

## Overview
A wireless environmental monitoring system that continuously reads real-time temperature and humidity data using a DHT11 sensor and uploads it to the ThingSpeak cloud platform for live visualization and trend analysis.

## How It Works
1. DHT11 sensor measures ambient temperature and humidity
2. ESP8266 NodeMCU reads the sensor data every 15 seconds
3. Data is transmitted over Wi-Fi to ThingSpeak cloud
4. ThingSpeak displays live graphs and gauge visualizations
5. Arduino IDE Serial Monitor shows real-time local readings

## Hardware Required
- ESP8266 NodeMCU microcontroller board
- DHT11 / DHT22 temperature and humidity sensor
- Breadboard and jumper wires
- 10kΩ resistor
- USB micro cable for programming and power

## Wiring
| DHT11 Pin | NodeMCU Pin |
|-----------|-------------|
| VCC       | 3.3V        |
| GND       | GND         |
| DATA      | D4 (GPIO2)  |

## Software Required
- Arduino IDE
- ESP8266 board core installed in Arduino IDE
- DHT sensor library (by Adafruit)
- ThingSpeak library (by MathWorks)

## Cloud Platform
- ThingSpeak — https://thingspeak.com
- Field 1 → Temperature (°C)
- Field 2 → Humidity (%)

## Setup Instructions
1. Install Arduino IDE and ESP8266 board core
2.  Add ESP8266 board URL in File → Preferences → Additional Board URLs:
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
3. Install ESP8266 Community board package via Boards Manager.
   • Install libraries via Sketch → Include Library → Manage Libraries: DHT sensor library (Adafruit),
    Adafruit Unified Sensor, ThingSpeak.
4. Open ESP8266_THINGSPEAK.ino
5. Create a free ThingSpeak account at https://thingspeak.com, make a channel with Field 1 =
Temperature, Field 2 = Humidity, and copy your Write API Key.
6. Replace the following with your own credentials inside the Nodemcu firmware:
   - YOUR_WIFI_SSID → your WiFi network name
   - YOUR_WIFI_PASSWORD → your WiFi password
   - YOUR_CHANNEL_ID → your ThingSpeak channel ID
   - YOUR_WRITE_API_KEY → your ThingSpeak Write API Key
7. Select board: NodeMCU 1.0 (ESP-12E Module)
8. Upload the code
9. Open Serial Monitor at 115200 baud to view readings

## System Block Diagram representation
<img width="903" height="328" alt="image" src="https://github.com/user-attachments/assets/62a1bfa7-f4ac-43b9-8ec4-a9ecc5f555b5" />
Figure 1: Block diagram of the IoT-based Environmental Monitoring System showing the data flow from the DHT11 sensor to the ThingSpeak Cloud.

## System setup snapshot
<img width="903" height="652" alt="image" src="https://github.com/user-attachments/assets/85b6180e-d930-4ec4-8522-fc749bc6532c" />

Figure b: Hardware interfacing of DHT11 sensor with ESP8266 NodeMCU.

## Expected Output
Serial Monitor:
<img width="903" height="515" alt="image" src="https://github.com/user-attachments/assets/497b1d79-544f-4c31-b7c0-6b779306cff2" />

Figure c: Real-time visualization of Temperature and Humidity on ThingSpeak Dashboard and Arduino IDE serial monitor.

