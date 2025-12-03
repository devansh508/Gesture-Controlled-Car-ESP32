#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

// ESP-NOW data structure
typedef struct struct_message {
  char command;  // single character F/B/L/R/S
} struct_message;

struct_message myData;

// Receiver MAC address , replace with your own
uint8_t receiverMAC[] = {0x84, 0x1F, 0xE8, 0x15, 0xB1, 0xFC};

// ESP-NOW send callback
void OnSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Message Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Initialize I2C on ESP32 pins SDA=21, SCL=22
  Wire.begin(21, 22);

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found! Check wiring.");
    while (1) delay(10);
  }
  Serial.println("MPU6050 Ready!");

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    ESP.restart();
  }

  esp_now_register_send_cb(OnSent);

  // Add receiver peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("Transmitter Ready!");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Map tilt to F/B/L/R/S
  float threshold = 5.0; // m/s^2
  if (a.acceleration.x > threshold)        myData.command = 'F';
  else if (a.acceleration.x < -threshold) myData.command = 'B';
  else if (a.acceleration.y > threshold)  myData.command = 'L';
  else if (a.acceleration.y < -threshold) myData.command = 'R';
  else                                    myData.command = 'S';

  // Send command via ESP-NOW
  esp_now_send(receiverMAC, (uint8_t *)&myData, sizeof(myData));

  Serial.print("Command Sent: ");
  Serial.println(myData.command);

  delay(200);
}
