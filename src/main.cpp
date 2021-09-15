/*
 *  Created on: 2020-05-15
 *      Author: Mixiaoxiao (Wang Bin)
 *
 * HAP section 8.38 Switch
 * An accessory contains a switch.
 *
 * This example shows how to:
 * 1. define a switch accessory and its characteristics (in my_accessory.c).
 * 2. get the switch-event sent from iOS Home APP.
 * 3. report the switch value to HomeKit.
 *
 * You should:
 * 1. read and use the Example01_TemperatureSensor with detailed comments
 *    to know the basic concept and usage of this library before other
 * examples。
 * 2. erase the full flash or call homekit_storage_reset() in setup()
 *    to remove the previous HomeKit pairing storage and
 *    enable the pairing with the new accessory of this new HomeKit example.
 */

#include "wifi_info.h"
#include <Arduino.h>

#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <Wire.h>
#include <arduino_homekit_server.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN D5 // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE DHT11 // DHT 11
// #define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
// https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);

//==============================
// HomeKit setup and loop
//==============================

// access your HomeKit characteristics defined in my_accessory.c
extern "C" homekit_characteristic_t temperature;
extern "C" homekit_characteristic_t humidity;

extern "C" homekit_server_config_t config;

static uint32_t next_report_millis = 0;

Adafruit_BMP280 bmp;
bool flag = false;

// Called when the switch value is changed by iOS Home APP
void my_homekit_report() {
  // Get temperature event and print its value.
  sensors_event_t event;

  dht.temperature().getEvent(&event);

  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    temperature.value.float_value = event.temperature;
  }

  if (flag) {
    Serial.println("bmp value");
    temperature.value.float_value = bmp.readTemperature();
  }

  flag = !flag;

  Serial.print(F("Temperature: "));
  Serial.print(temperature.value.float_value);
  Serial.println(F("°C"));

  homekit_characteristic_notify(&temperature, temperature.value);

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));

    humidity.value.float_value = event.relative_humidity;

    homekit_characteristic_notify(&humidity, humidity.value);
  }
}

void my_homekit_setup() { arduino_homekit_setup(&config); }

void sensorSetup() {
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print(F("Sensor Type: "));
  Serial.println(sensor.name);
  Serial.print(F("Driver Ver:  "));
  Serial.println(sensor.version);
  Serial.print(F("Unique ID:   "));
  Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value:   "));
  Serial.print(sensor.max_value);
  Serial.println(F("°C"));
  Serial.print(F("Min Value:   "));
  Serial.print(sensor.min_value);
  Serial.println(F("°C"));
  Serial.print(F("Resolution:  "));
  Serial.print(sensor.resolution);
  Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print(F("Sensor Type: "));
  Serial.println(sensor.name);
  Serial.print(F("Driver Ver:  "));
  Serial.println(sensor.version);
  Serial.print(F("Unique ID:   "));
  Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value:   "));
  Serial.print(sensor.max_value);
  Serial.println(F("%"));
  Serial.print(F("Min Value:   "));
  Serial.print(sensor.min_value);
  Serial.println(F("%"));
  Serial.print(F("Resolution:  "));
  Serial.print(sensor.resolution);
  Serial.println(F("%"));
  Serial.println(F("------------------------------------"));

  // if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    while (1)
      delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  // Set delay between sensor readings based on sensor details.
  delay(1000);
}

void setup() {
  Serial.begin(115200);
  sensorSetup();
  wifi_connect();
  my_homekit_setup();
}

void loop() {
  arduino_homekit_loop();

  const uint32_t t = millis();

  if (t > next_report_millis) {
    next_report_millis = t + 1 * 1000 * 30;
    my_homekit_report();
  }
}