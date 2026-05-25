#ifndef __BATTERY_H__
#define __BATTERY_H__

#include <Arduino.h>

#define BATTERY_PIN A3

#ifndef BATTERY_ADC_REF_V
#define BATTERY_ADC_REF_V 5.0f
#endif

#ifndef BATTERY_DIVIDER_RATIO
#define BATTERY_DIVIDER_RATIO 2.0f
#endif

// If a fully charged pack still reports too low, increase this slightly.
#ifndef BATTERY_VOLTAGE_CALIBRATION
#define BATTERY_VOLTAGE_CALIBRATION 0.90f
#endif

#ifndef BATTERY_EMPTY_VOLTAGE
#define BATTERY_EMPTY_VOLTAGE 6.0f
#endif

#ifndef BATTERY_FULL_VOLTAGE
#define BATTERY_FULL_VOLTAGE 8.4f
#endif

// SunFounder dashboard derives percentage from BV using 6.6V..8.4V.
// Keep enabled when using packs that should read 100% below 8.4V.
#ifndef BATTERY_DASHBOARD_COMPAT_MODE
#define BATTERY_DASHBOARD_COMPAT_MODE 1
#endif

#ifndef BATTERY_DASHBOARD_EMPTY_VOLTAGE
#define BATTERY_DASHBOARD_EMPTY_VOLTAGE 6.6f
#endif

#ifndef BATTERY_DASHBOARD_FULL_VOLTAGE
#define BATTERY_DASHBOARD_FULL_VOLTAGE 8.4f
#endif

/**
 * @brief init battery module
 * 
 */
void batteryBegin() {
  pinMode(BATTERY_PIN, INPUT);
}

/**
 * @brief Returns the voltage of the battery
 * 
 * @return float 
 */
float batteryGetVoltage() {
  const uint8_t sampleCount = 8;
  uint16_t adcSum = 0;

  for (uint8_t i = 0; i < sampleCount; i++) {
    adcSum += analogRead(BATTERY_PIN);
  }

  float adcValue = adcSum / float(sampleCount);
  float adcVoltage = adcValue * (BATTERY_ADC_REF_V / 1023.0f);
  float batteryVoltage = adcVoltage * BATTERY_DIVIDER_RATIO * BATTERY_VOLTAGE_CALIBRATION;
  batteryVoltage = int(batteryVoltage * 100.0f + 0.5f) / 100.0f; // round two decimal places
  return batteryVoltage;
}

/**
 * @brief Returns the percentage of the battery
 * 
 * @return uint8_t
 */
uint8_t batteryGetPercentage() {
  float voltage = batteryGetVoltage();
  float percentage = (voltage - BATTERY_EMPTY_VOLTAGE) * 100.0f /
                     (BATTERY_FULL_VOLTAGE - BATTERY_EMPTY_VOLTAGE);
  percentage = constrain(percentage, 0.0f, 100.0f);
  uint8_t roundedPercentage = uint8_t(percentage + 0.5f);
  return roundedPercentage;
}

/**
 * @brief Voltage value formatted for app dashboard (BV field).
 *
 * In compatibility mode, this maps calculated percentage to app's expected
 * voltage range so the app percentage matches the configured battery curve.
 */
float batteryGetDashboardVoltage() {
#if BATTERY_DASHBOARD_COMPAT_MODE
  float percentage = batteryGetPercentage() / 100.0f;
  float dashboardVoltage = BATTERY_DASHBOARD_EMPTY_VOLTAGE +
                           percentage * (BATTERY_DASHBOARD_FULL_VOLTAGE - BATTERY_DASHBOARD_EMPTY_VOLTAGE);
  dashboardVoltage = int(dashboardVoltage * 100.0f + 0.5f) / 100.0f;
  return dashboardVoltage;
#else
  return batteryGetVoltage();
#endif
}

#endif // __BATTERY_H__