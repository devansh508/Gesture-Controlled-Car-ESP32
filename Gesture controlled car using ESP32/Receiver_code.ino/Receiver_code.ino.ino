#include <WiFi.h>
#include <esp_now.h>

// Motor A pins
#define ENA 25
#define IN1 26
#define IN2 27

// Motor B pins
#define ENB 14
#define IN3 12
#define IN4 13

String command = "";

// OLD CALLBACK FORMAT (WORKS FOR ESP32 CORE 2.0.17)
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  command = "";
  for (int i = 0; i < len; i++) {
    command += (char)incomingData[i];
  }

  Serial.println("Command Received: " + command);
  moveCar(command);
}

void moveCar(String cmd) {

  if (cmd == "F") {  // Forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(0, 200);
    ledcWrite(1, 200);
  }

  else if (cmd == "B") {  // Backward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    ledcWrite(0, 200);
    ledcWrite(1, 200);
  }

  else if (cmd == "L") {  // Left
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(0, 200);
    ledcWrite(1, 200);
  }

  else if (cmd == "R") {  // Right
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    ledcWrite(0, 200);
    ledcWrite(1, 200);
  }

  else if (cmd == "S") {  // Stop
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    ledcWrite(0, 0);
    ledcWrite(1, 0);
  }
}

void setup() {
  Serial.begin(115200);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // PWM
  ledcAttachPin(ENA, 0);
  ledcSetup(0, 1000, 8);

  ledcAttachPin(ENB, 1);
  ledcSetup(1, 1000, 8);

  // ESP-NOW
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Receiver Ready!");
}

void loop() {
}
