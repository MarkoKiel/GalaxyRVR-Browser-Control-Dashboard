## GPS Module Installation

The GalaxyRVR dashboard uses a **GPS6MV2 GPS module** connected to the Arduino/ESP32 platform.

### Wiring

| GPS6MV2 Pin | Arduino / ESP32 |
| ----------- | --------------- |
| VCC         | 3.3V / 5V       |
| GND         | GND             |
| TX          | PIN A1          |
| RX          | Optional        |


GPS6MV2 TX → PIN A1

The GPS module is used for:

* Live GPS speed display
* Position tracking
* Future navigation functions

---

## WiFi Configuration

Before uploading the firmware, update your WiFi credentials in:

galaxy-rvr-gps.ino

Change the following values:

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

Then upload the firmware to the Arduino.

---

## Required Libraries

Depending on your setup, install:

* TinyGPS++
* WiFi library for ESP32

Example:

#include <TinyGPS++.h>
#include <WiFi.h>

NEO-6M GPS Module
Arduino
Espressif Systems
