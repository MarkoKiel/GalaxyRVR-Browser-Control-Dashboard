# GalaxyRVR Dashboard – Project Summary

## Overview

GalaxyRVR is a modern web-based control and monitoring dashboard for an ESP32-powered rover platform with live telemetry, sensor visualization, and video streaming capabilities. The project combines embedded hardware, real-time communication, and a responsive Bootstrap 5 frontend into a unified remote-control interface.

The dashboard is designed for both desktop and mobile operation and focuses on low-latency monitoring, clean UI design, and modular hardware integration.

<p align="center">
  <img 
    src="https://github.com/MarkoKiel/GalaxyRVR-Browser-Control-Dashboard/blob/main/ScreenshotGalaxyRVR-Dashboard.png"
  >
</p>

## Features

### Live Telemetry

* GPS speed display
* Motor power visualization
* Real-time sensor values
* Front obstacle sensor monitoring
* Status indicators for rover systems

### Video Streaming

* MJPEG live stream integration
* Browser-based camera viewing
* Local network optimized streaming
* Embedded stream support using `<object>` rendering
* Lightweight streaming without external plugins

### Responsive Dashboard

* Bootstrap 5 based UI
* Mobile-friendly layout
* Modern card and widget system
* Dynamic value updates via JavaScript
* Clean dark dashboard styling

### ESP32 Integration

* ESP32-S3 based rover controller
* WiFi communication
* GPIO-based sensor integration
* Real-time browser updates
* Planned USB mass-storage support

### Hardware Support

* TFT display integration
* Touch support
* RFID support
* RTC integration
* Smart card reader support
* Camera streaming module support
* External motor driver telemetry

---

## Current Technical Stack

### Frontend

* HTML5
* CSS3
* Bootstrap 5
* JavaScript
* Font Awesome

### Backend / Communication

* ESP32 WebSocket communication
* MJPEG HTTP video stream
* Local network communication

### Embedded Hardware

* ESP32-S3-WROOM-1-N16R8
* TFT display (ILI9341)
* XPT2046 touch controller
* RFID module
* USB-C power integration
* RTC module
* Sensor array support

---

## Dashboard Components

### Main Rover View

* Central rover visualization
* Live speed indicator
* Sensor overlays
* Motor telemetry panels

### Telemetry Widgets

* GPS speed
* Motor K value
* Motor Q value
* Front distance sensor
* System state information

### Video Module

* Embedded MJPEG stream
* Optimized local streaming
* Non-blocking stream rendering
* Browser compatible implementation

---

## Goals

* Create a professional rover control interface
* Support autonomous and manual operation
* Enable modular sensor expansion
* Provide reliable local-network remote control
* Build a scalable ESP32 robotics platform

---

## Project Status

Active development.
Frontend modernization, hardware integration, and streaming optimization are currently in progress.
