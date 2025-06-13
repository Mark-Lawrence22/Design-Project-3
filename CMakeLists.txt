#include <WiFi.h>
#include <WiFiProv.h>
#include "RMaker.h"
#include <Adafruit_BME280.h>
#include <DHT.h>

// Device name
const char *deviceName = "ESP32-EnvMonitor";

// Pins
#define SDA_PIN 21
#define SCL_PIN 22
#define OUTPUT_PIN 17  // Changed from 25 to 17
#define LED_PIN 16     // Changed from 26 to 16
#define DHTPIN 4
#define DHTTYPE DHT22

// Sensor objects
Adafruit_BME280 bme;
DHT dht(DHTPIN, DHTTYPE);

// RainMaker nodes/devices
Node node;
TemperatureSensor *dht_temp_sensor;
Device *bme280_device;
Param *humidity_param;
Param *pressure_param;
Switch *output_switch;

// Provisioning event handler
void sysProvEvent(arduino_event_t *sys_event) {
  switch (sys_event->event_id) {
    case ARDUINO_EVENT_PROV_START:
      Serial.println("Provisioning started");
      printQR();
      break;
    case ARDUINO_EVENT_PROV_CRED_SUCCESS:
      Serial.println("Provisioning successful");
      break;
    case ARDUINO_EVENT_PROV_END:
      Serial.println("Provisioning ended");
      break;
    default:
      break;
  }
}

// Callback for RainMaker switch
void write_callback(Device *device, Param *param, esp_rmaker_param_val_t val, void *priv_data, esp_rmaker_write_ctx_t *ctx) {
  if (strcmp(device->getDeviceName(), "Output Control") == 0) {
    bool state = val.val.b;
    digitalWrite(OUTPUT_PIN, state ? HIGH : LOW);
    Serial.printf("Output switched %s\n", state ? "ON" : "OFF");
    param->updateAndReport(val);
  }
}

void setup() {
  Serial.begin(115200);

  // I2C for BME280
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!bme.begin(0x76)) {
    Serial.println("Could not find BME280! Check wiring.");
    while (1);
  }

  // Init DHT22
  dht.begin();

  // Output pins
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Initialize RainMaker
  node = RMaker.initNode(deviceName);

  // DHT22 Temperature Sensor
  dht_temp_sensor = new TemperatureSensor("DHT22 Sensor");
  node.addDevice(*dht_temp_sensor);

  // BME280 Humidity + Pressure Sensor
  bme280_device = new Device("BME280 Sensor", "custom.bme280", NULL);
  humidity_param = new Param("Humidity", "esp.param.humidity", value((float)0.0), PROP_FLAG_READ | PROP_FLAG_PERSIST);
  pressure_param = new Param("Pressure", "esp.param.pressure", value((float)0.0), PROP_FLAG_READ | PROP_FLAG_PERSIST);
  bme280_device->addParam(*humidity_param);
  bme280_device->addParam(*pressure_param);
  node.addDevice(*bme280_device);

  // Output switch
  output_switch = new Switch("Output Control", NULL, false);
  output_switch->addCb(write_callback);
  node.addDevice(*output_switch);

  // Start services
  RMaker.enableOTA(OTA_USING_PARAMS);
  RMaker.enableTZService();
  RMaker.start();

  // Start provisioning
  WiFi.onEvent(sysProvEvent);
  WiFiProv.beginProvision(NETWORK_PROV_SCHEME_BLE);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // DHT22 temperature
    float dhtTemp = dht.readTemperature();
    if (!isnan(dhtTemp)) {
      dht_temp_sensor->updateAndReportParam("Temperature", dhtTemp);
      Serial.printf("DHT22 Temp: %.2f °C\n", dhtTemp);
      digitalWrite(LED_PIN, (dhtTemp >= 31.0) ? HIGH : LOW);
    } else {
      Serial.println("Failed to read from DHT22");
    }

    // BME280 humidity and pressure
    float hum = bme.readHumidity();
    float pres = bme.readPressure() / 100.0F;
    if (!isnan(hum)) humidity_param->updateAndReport(value(hum));
    if (!isnan(pres)) pressure_param->updateAndReport(value(pres));
    Serial.printf("Humidity: %.2f%%, Pressure: %.2f hPa\n", hum, pres);
  } else {
    Serial.println("WiFi not connected.");
  }

  delay(5000);
}

// Print QR for BLE provisioning
void printQR() {
  String payload = "{\"ver\":\"v1\",\"name\":\"" + String(deviceName) +
                   "\",\"pop\":\"abcd1234\",\"transport\":\"ble\"}";
  String QR = "https://espressif.github.io/esp-jumpstart/qrcode.html?data=" + payload;
  Serial.println(QR);
}
