#ifndef __GPS_H__
#define __GPS_H__

#include <Arduino.h>

#ifndef GPS_ENABLE
#define GPS_ENABLE 1
#endif

#if GPS_ENABLE

#include <TinyGPS++.h>

#if defined(__has_include)
  #if __has_include(<NeoSWSerial.h>)
    #include <NeoSWSerial.h>
    #define GPS_USE_NEOSWSERIAL 1
  #else
    #include <SoftwareSerial.h>
    #define GPS_USE_NEOSWSERIAL 0
  #endif
#else
  #include <SoftwareSerial.h>
  #define GPS_USE_NEOSWSERIAL 0
#endif

/** GPS (GY-NEO6MV2) wiring for Arduino UNO
 * GPS TX -> Arduino A1 (RX)
 * GPS RX -> Arduino A0 (TX, optional)
 */
#define GPS_SERIAL_RX_PIN A1
#define GPS_SERIAL_TX_PIN -1
#define GPS_BAUDRATE 9600

// Consider fix stale if no valid update arrives within this window.
#define GPS_FIX_TIMEOUT_MS 5000
#if GPS_USE_NEOSWSERIAL
  #define GPS_UPDATE_INTERVAL_MS 60
  // Keep GPS parsing bounded so other tasks (ESP32 comms) are not starved.
  #define GPS_MAX_BYTES_PER_UPDATE 16
  #define GPS_MAX_READ_TIME_US 1800
#else
  // SoftwareSerial is more CPU intensive on AVR UNO, so parse more conservatively.
  #define GPS_UPDATE_INTERVAL_MS 100
  #define GPS_MAX_BYTES_PER_UPDATE 8
  #define GPS_MAX_READ_TIME_US 1000
#endif

#if GPS_USE_NEOSWSERIAL
typedef NeoSWSerial GpsSerialType;
#else
typedef SoftwareSerial GpsSerialType;
#endif

static GpsSerialType gpsSerial(GPS_SERIAL_RX_PIN, GPS_SERIAL_TX_PIN);
static TinyGPSPlus gps;

static bool gpsFix = false;
static double gpsLatitude = 0.0;
static double gpsLongitude = 0.0;
static double gpsSpeedKmph = 0.0;
static uint32_t gpsSatellites = 0;
static uint32_t gpsLastFixTime = 0;
static uint32_t gpsLastUpdateTick = 0;
static bool gpsTelemetryDirty = true;

void gpsBegin() {
  gpsSerial.begin(GPS_BAUDRATE);
}

void gpsUpdate() {
  uint32_t now = millis();
  if (now - gpsLastUpdateTick < GPS_UPDATE_INTERVAL_MS) {
    return;
  }
  gpsLastUpdateTick = now;

  uint16_t bytesRead = 0;
  uint32_t readStart = micros();

  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());

    bytesRead++;
    if (bytesRead >= GPS_MAX_BYTES_PER_UPDATE) {
      break;
    }

    if (micros() - readStart >= GPS_MAX_READ_TIME_US) {
      break;
    }
  }

  if (gps.location.isUpdated()) {
    gpsTelemetryDirty = true;
    gpsFix = gps.location.isValid();
    if (gpsFix) {
      gpsLatitude = gps.location.lat();
      gpsLongitude = gps.location.lng();
      gpsLastFixTime = millis();
    }
  }

  if (gps.speed.isUpdated() && gps.speed.isValid()) {
    gpsSpeedKmph = gps.speed.kmph();
    gpsTelemetryDirty = true;
  }

  if (gps.satellites.isUpdated() && gps.satellites.isValid()) {
    gpsSatellites = gps.satellites.value();
    gpsTelemetryDirty = true;
  }

  if (gpsFix && millis() - gpsLastFixTime > GPS_FIX_TIMEOUT_MS) {
    gpsFix = false;
    gpsTelemetryDirty = true;
  }
}

bool gpsHasTelemetryUpdate() {
  return gpsTelemetryDirty;
}

void gpsMarkTelemetrySent() {
  gpsTelemetryDirty = false;
}

bool gpsHasFix() {
  return gpsFix;
}

double gpsGetLatitude() {
  return gpsLatitude;
}

double gpsGetLongitude() {
  return gpsLongitude;
}

double gpsGetSpeedKmph() {
  return gpsSpeedKmph;
}

uint32_t gpsGetSatellites() {
  return gpsSatellites;
}

#else

void gpsBegin() {}
void gpsUpdate() {}

bool gpsHasTelemetryUpdate() {
  return false;
}

void gpsMarkTelemetrySent() {}

bool gpsHasFix() {
  return false;
}

double gpsGetLatitude() {
  return 0.0;
}

double gpsGetLongitude() {
  return 0.0;
}

double gpsGetSpeedKmph() {
  return 0.0;
}

uint32_t gpsGetSatellites() {
  return 0;
}

#endif

#endif // __GPS_H__
