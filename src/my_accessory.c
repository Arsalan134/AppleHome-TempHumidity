/*
 * my_accessory.c
 * Define the accessory in C language using the Macro in characteristics.h
 *
 *  Created on: 2020-05-15
 *      Author: Mixiaoxiao (Wang Bin)
 */

#include <homekit/characteristics.h>
#include <homekit/homekit.h>

void my_accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");
  digitalWrite(2, 1);
}

// Switch (HAP section 8.38)
// required: ON
// optional: NAME

// format: bool; HAP section 9.70; write the .setter function to get the
// switch-event sent from iOS Home APP.

void temperature_sensor_identify(homekit_value_t _value) {
  printf("Temperature sensor identify\n");
}

homekit_characteristic_t temperature =
    HOMEKIT_CHARACTERISTIC_(CURRENT_TEMPERATURE, 0);
homekit_characteristic_t humidity =
    HOMEKIT_CHARACTERISTIC_(CURRENT_RELATIVE_HUMIDITY, 0);

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(
            .id = 1, .category = homekit_accessory_category_thermostat,
            .services =
                (homekit_service_t *[]){
                    HOMEKIT_SERVICE(
                        ACCESSORY_INFORMATION,
                        .characteristics =
                            (homekit_characteristic_t *[]){
                                HOMEKIT_CHARACTERISTIC(NAME,
                                                       "Temperature Sensor"),
                                HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Arsalan"),
                                HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "123456"),
                                HOMEKIT_CHARACTERISTIC(MODEL,
                                                       "MyTemperatureSensor"),
                                HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION,
                                                       "1.0"),
                                HOMEKIT_CHARACTERISTIC(
                                    IDENTIFY, temperature_sensor_identify),
                                NULL}),
                    HOMEKIT_SERVICE(TEMPERATURE_SENSOR, .primary = true,
                                    .characteristics =
                                        (homekit_characteristic_t *[]){
                                            HOMEKIT_CHARACTERISTIC(
                                                NAME, "Temperature Sensor"),
                                            &temperature, NULL}),
                    HOMEKIT_SERVICE(
                        HUMIDITY_SENSOR,
                        .characteristics =
                            (homekit_characteristic_t *[]){
                                HOMEKIT_CHARACTERISTIC(NAME, "Humidity Sensor"),
                                &humidity, NULL}),
                    NULL}),
    NULL};

homekit_server_config_t config = {.accessories = accessories,
                                  .password = "111-11-111"};
