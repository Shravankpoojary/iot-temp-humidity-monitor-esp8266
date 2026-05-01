# iot-temp-humidity-monitor-esp8266
### Minor Project | GlowLogics Solutions Pvt. Ltd. Internship 2025-26
This project is a wireless environmental monitoring system designed to provide timely tracking of ambient temperature and relative humidity. It utilizes an ESP8266 NodeMCU to process digital signals from a DHT11 sensor and transmits the data to a cloud-based analytics platform for remote visualization.

## Overview
A wireless environmental monitoring system that continuously 
reads real-time temperature and humidity data using a DHT11 
sensor and uploads it to the ThingSpeak cloud platform for 
live visualization and trend analysis.

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
2. Install DHT and ThingSpeak libraries
3. Open ESP8266_THINGSPEAK.ino
4. Replace the following with your own credentials:
   - YOUR_WIFI_SSID → your WiFi network name
   - YOUR_WIFI_PASSWORD → your WiFi password
   - YOUR_CHANNEL_ID → your ThingSpeak channel ID
   - YOUR_WRITE_API_KEY → your ThingSpeak Write API Key
5. Select board: NodeMCU 1.0 (ESP-12E Module)
6. Upload the code
7. Open Serial Monitor at 115200 baud to view readings

## Expected Output
Serial Monitor:
