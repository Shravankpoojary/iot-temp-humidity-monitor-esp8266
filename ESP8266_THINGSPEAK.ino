#include <ESP8266WiFi.h>
#include <DHT.h>
#include "ThingSpeak.h"

// ─────────────────────────────────────────────────────────────
//  Wi-Fi Credentials
//  (Wokwi provides a built-in Wi-Fi; use these exact values)
// ─────────────────────────────────────────────────────────────
const char* WIFI_SSID     = "YOUR_WIFI_SSID";       // ← Replace with your WiFi name
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";   // ← Replace with your WiFi password

// ─────────────────────────────────────────────────────────────
//  ThingSpeak Configuration  ← EDIT THESE
// ─────────────────────────────────────────────────────────────
unsigned long CHANNEL_ID  = 0;                       // ← Replace with your ThingSpeak Channel ID
const char*   WRITE_API_KEY = "YOUR_WRITE_API_KEY"; // ← Replace with your Write API Key

// ─────────────────────────────────────────────────────────────
//  DHT11 Sensor Configuration
// ─────────────────────────────────────────────────────────────
#define DHTPIN  13          // GPIO2  =  D4 on WeMos D1 / NodeMCU
#define DHTTYPE DHT11

DHT   dht(DHTPIN, DHTTYPE);
WiFiClient wifiClient;

// ─────────────────────────────────────────────────────────────
//  Timing
// ─────────────────────────────────────────────────────────────
const unsigned long UPLOAD_INTERVAL_MS = 15000UL; // 15 s  (ThingSpeak free tier min: 15 s)
unsigned long lastUploadTime           = 0;

// ─────────────────────────────────────────────────────────────
//  Helpers ─ Serial status indicator
// ─────────────────────────────────────────────────────────────
void printSeparator() {
  Serial.println(F("─────────────────────────────────────"));
}

// ─────────────────────────────────────────────────────────────
//  Connect / reconnect to Wi-Fi
// ─────────────────────────────────────────────────────────────
void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.print(F("\n[WiFi] Connecting to "));
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print('.');
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("\n[WiFi] Connected!"));
    Serial.print(F("[WiFi] IP Address: "));
    Serial.println(WiFi.localIP());
  } else {
    Serial.println(F("\n[WiFi] Connection FAILED. Will retry."));
  }
}

// ─────────────────────────────────────────────────────────────
//  SETUP
// ─────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(200);

  printSeparator();
  Serial.println(F("  ESP8266 + DHT11 → ThingSpeak"));
  //Serial.println(F("  Wokwi Simulatio"));
  printSeparator();

  // Initialize DHT sensor
  dht.begin();
  Serial.println(F("[DHT11] Sensor initialized on GPIO2 (D4)"));

  // Initialize ThingSpeak
  ThingSpeak.begin(wifiClient);
  Serial.println(F("[ThingSpeak] Client initialized"));

  // Connect Wi-Fi
  WiFi.mode(WIFI_STA);
  connectWiFi();

  Serial.println(F("[System] Setup complete. Starting data loop...\n"));
}

// ─────────────────────────────────────────────────────────────
//  LOOP
// ─────────────────────────────────────────────────────────────
void loop() {
  unsigned long currentTime = millis();

  // Check if it's time to sample & upload
  if (currentTime - lastUploadTime >= UPLOAD_INTERVAL_MS) {
    lastUploadTime = currentTime;

    // ── 1. Read sensor ────────────────────────────────────────
    float humidity    = dht.readHumidity();
    float temperature = dht.readTemperature(); // Celsius

    printSeparator();
    Serial.print(F("[Sensor] Reading at "));
    Serial.print(currentTime / 1000);
    Serial.println(F("s"));

    // Validate readings
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println(F("[ERROR] DHT11 read failed! Skipping upload."));
      return;
    }

    Serial.print(F("  Temperature : "));
    Serial.print(temperature, 1);
    Serial.println(F(" °C"));

    Serial.print(F("  Humidity    : "));
    Serial.print(humidity, 1);
    Serial.println(F(" %"));

    // ── 2. Ensure Wi-Fi is alive ──────────────────────────────
    connectWiFi();
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println(F("[ERROR] No Wi-Fi. Skipping upload."));
      return;
    }

    // ── 3. Push data to ThingSpeak ────────────────────────────
    ThingSpeak.setField(1, temperature); // Field 1 → Temperature
    ThingSpeak.setField(2, humidity);    // Field 2 → Humidity

    // Optional: add a status message
    ThingSpeak.setStatus("Data is recieved");

    int httpCode = ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);

    // ── 4. Report result ──────────────────────────────────────
    if (httpCode == 200) {
      Serial.println(F("[ThingSpeak] ✓ Data uploaded successfully!"));
    } else {
      Serial.print(F("[ThingSpeak] ✗ Upload failed. HTTP code: "));
      Serial.println(httpCode);
    }
  }

  // Wi-Fi watchdog (runs every loop iteration, lightweight)
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  delay(100); // Small delay prevents tight loop
}
