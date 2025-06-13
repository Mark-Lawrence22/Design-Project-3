// utils.c
#include <stdio.h>
#include <string.h>

// A simple function to print the provisioning QR code
void printQR(const char *deviceName) {
    char payload[200];
    snprintf(payload, sizeof(payload),
             "{\"ver\":\"v1\",\"name\":\"%s\",\"pop\":\"abcd1234\",\"transport\":\"ble\"}",
             deviceName);

    char qr_url[300];
    snprintf(qr_url, sizeof(qr_url),
             "https://espressif.github.io/esp-jumpstart/qrcode.html?data=%s",
             payload);

    printf("%s\n", qr_url);  // For Serial.print in Arduino, we’ll handle it differently in the .ino file