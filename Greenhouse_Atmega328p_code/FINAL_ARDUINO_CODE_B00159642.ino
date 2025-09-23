#include <OneWire.h> 
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include "rgb_lcd.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Arduino_SensorKit.h>
#include <avr/wdt.h>

// Hardware Configuration
#define ONE_WIRE_BUS        7
#define FAN_PIN             8
#define TEMP_THRESHOLD_PIN  A0
#define LDR_PIN             A1
#define ESP_RX              10
#define ESP_TX              11
#define BUZZER_PIN          5

// ThingSpeak Settings
const String API_KEY = "R1ZTW11SA2559MEB";
const String HOST = "api.thingspeak.com";
const String PORT = "80";

// WiFi Credentials
const String WIFI_SSID = "yep";
const String WIFI_PASSWORD = "12345678";

// Global Objects
rgb_lcd lcd;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SoftwareSerial esp8266(ESP_RX, ESP_TX);

// Custom LCD Characters
byte DegreesC[] = {
  B11000, B11011, B00100, B00100, B00100, B00100, B00011, B00000
};
byte Lumens[] = {
  B10101, B10010, B10010, B10010, B10010, B10010, B10010, B11101
};
byte Heart[] = {
  B00000, B01010, B11111, B11111, B11111, B01110, B00100, B00000
};

// Fan Animation Frames
byte FanFrame1[] = { B00100, B00100, B11111, B00100, B00100, B00000, B00100, B00000 };
byte FanFrame2[] = { B10001, B01010, B00100, B01010, B10001, B00000, B00000, B00000 };
byte FanFrame3[] = { B00000, B00100, B10101, B11111, B10101, B00100, B00000, B00000 };
byte FanFrame4[] = { B00000, B10001, B01010, B00100, B01010, B10001, B00000, B00000 };
byte FanFrame5[] = { B00100, B00100, B11111, B00100, B00100, B00000, B00100, B00000 };
byte FanFrame6[] = { B10001, B01010, B00100, B01010, B10001, B00000, B00000, B00000 };

// Animation control
int fanFrame = 0;
unsigned long lastFanFrameTime = 0;
const unsigned long fanAnimInterval = 150;

// State Variables
float SoilTemp = 0;
bool FanState = false;
float previousPotValue = -1;
unsigned long lastPotChangeTime = 0;
bool showingThreshold = false;

// ===== Function Declarations =====
void initializeSensors();
void initializeWiFi();
bool checkFanState(float airTemp, float threshold);
void sendCommand(String command, int maxTime, char readReply[]);
void sendToThingSpeak(float soilTemp, float airTemp, float humidity, float lux, bool fanStatus);
float calculateLux();
void updateLCD(float soilTemp, float airTemp, float humidity, float lux, bool fan);
void setLCDColor(float airTemp);
void playStartupMelody();
void buzzFanOn();
void buzzFanOff();
void loadCustomChars();
void displaySystemReady();

void setup() {
  lcd.begin(16, 2);
  loadCustomChars();
  initializeSensors();
  initializeWiFi();
  delay(2000); // Let peripherals stabilize

  // Enable Watchdog Timer for 2 seconds
  wdt_enable(WDTO_2S);

  lcd.clear();
  playStartupMelody();
  displaySystemReady();
}


void loop() {
  sensors.requestTemperatures();
  SoilTemp = sensors.getTempCByIndex(0);
  float airTemp = Environment_I2C.readTemperature();
  float humidity = Environment_I2C.readHumidity();
  float lux = calculateLux();

  int rawPotValue = analogRead(TEMP_THRESHOLD_PIN);
  float tempThreshold = map(rawPotValue, 0, 1023, 0, 40);

  if (abs(rawPotValue - previousPotValue) > 5) {
    previousPotValue = rawPotValue;
    lastPotChangeTime = millis();
    showingThreshold = true;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Threshold:");
    lcd.setCursor(0, 1);
    lcd.print(tempThreshold, 1);
    lcd.write((byte)0);

    tone(BUZZER_PIN, 1046, 40);
    delay(50);
    tone(BUZZER_PIN, 1318, 30);
    delay(35);
    noTone(BUZZER_PIN);
  }

  bool fanShouldBeOn = checkFanState(airTemp, tempThreshold);
  digitalWrite(FAN_PIN, fanShouldBeOn ? HIGH : LOW);
  FanState = fanShouldBeOn;

  static bool previousFanState = false;
  if (FanState != previousFanState) {
    if (FanState) buzzFanOn();
    else buzzFanOff();
    previousFanState = FanState;
  }

  setLCDColor(airTemp);

  if (showingThreshold && (millis() - lastPotChangeTime > 2000)) {
    showingThreshold = false;
  }

  if (!showingThreshold) {
    updateLCD(SoilTemp, airTemp, humidity, lux, FanState);
  }

  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 60000) {
    sendToThingSpeak(SoilTemp, airTemp, humidity, lux, FanState);
    lastUpdate = millis();
  }

  static unsigned long lastBlink = 0;
  if (millis() - lastBlink > 500) {
    digitalWrite(13, !digitalRead(13));
    lastBlink = millis();
  }

  if (FanState && millis() - lastFanFrameTime >= fanAnimInterval) {
    fanFrame = (fanFrame + 1) % 6;
    switch (fanFrame) {
      case 0: lcd.createChar(3, FanFrame1); break;
      case 1: lcd.createChar(3, FanFrame2); break;
      case 2: lcd.createChar(3, FanFrame3); break;
      case 3: lcd.createChar(3, FanFrame4); break;
      case 4: lcd.createChar(3, FanFrame5); break;
      case 5: lcd.createChar(3, FanFrame6); break;
    }
    lastFanFrameTime = millis();
  }

  wdt_reset();
}


void initializeSensors() {
  Wire.begin();
  Environment_I2C.begin();
  sensors.begin();

  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  pinMode(13, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(115200);
  esp8266.begin(115200);

  float bootTemp = Environment_I2C.readTemperature();
  setLCDColor(bootTemp);
}

void initializeWiFi() {
  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\"" + WIFI_SSID + "\",\"" + WIFI_PASSWORD + "\"", 20, "OK");
}

bool checkFanState(float airTemp, float threshold) {
  bool shouldBeOn = (airTemp > threshold);
  if (FanState && !shouldBeOn && airTemp > (threshold - 1.0)) {
    shouldBeOn = true;
  }
  return shouldBeOn;
}

// LCD color changes instantly (no hysteresis)
void setLCDColor(float airTemp) {
  if (airTemp > 30) {
    lcd.setRGB(255, 0, 0); // Hot
  } else if (airTemp < 20) {
    lcd.setRGB(0, 0, 255); // Cold
  } else {
    lcd.setRGB(0, 255, 0); // Normal
  }
}

float calculateLux() {
  int ldrValue = analogRead(LDR_PIN);
  float voltage = ldrValue * (5.03 / 1023.0);
  if (voltage < 0.01) return 0;
  float resistance = (5.03 - voltage) / voltage * 10160.0;
  return 2355175.0 * pow(resistance, -1.2109);
}

void updateLCD(float soilTemp, float airTemp, float humidity, float lux, bool fan) {
  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(soilTemp, 1);
  lcd.write((byte)0);
  lcd.print(" A:");
  lcd.print(airTemp, 1);
  lcd.write((byte)0);

  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity, 1);
  lcd.print("% L:");

  char luxFanBuffer[7];
  int luxInt = (int)lux;

  if (fan) {
    snprintf(luxFanBuffer, sizeof(luxFanBuffer), "%-4d%c%c", luxInt, 1, 3);
  } else {
    snprintf(luxFanBuffer, sizeof(luxFanBuffer), "%-4d%c ", luxInt, 1);
  }

  lcd.print(luxFanBuffer);
}

void sendCommand(String command, int maxTime, char readReply[]) {
  Serial.print("[ESP] Sending: ");
  Serial.println(command);
  bool found = false;
  int countTimeCommand = 0;

  while (countTimeCommand < maxTime) {
    esp8266.println(command);
    if (esp8266.find(readReply)) {
      found = true;
      break;
    }
    countTimeCommand++;
    delay(1000);
  }
  Serial.println(found ? "Success" : "Failed");
}

void sendToThingSpeak(float soilTemp, float airTemp, float humidity, float lux, bool fanStatus) {
  String data = "GET /update?api_key=" + API_KEY +
                "&field1=" + String(soilTemp) +
                "&field2=" + String(airTemp) +
                "&field3=" + String(humidity) +
                "&field4=" + String(lux) +
                "&field5=" + String(fanStatus ? 1 : 0) + 
                "\r\n\r\n";

  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
  sendCommand("AT+CIPSEND=0," + String(data.length()), 4, ">");
  esp8266.print(data);
  delay(1000);
  sendCommand("AT+CIPCLOSE=0", 5, "OK");
}

void loadCustomChars() {
  lcd.createChar(0, DegreesC);
  lcd.createChar(1, Lumens);
  lcd.createChar(2, Heart);
  lcd.createChar(3, FanFrame1); // Initial fan frame
}

void displaySystemReady() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write((byte)2);
  lcd.print(" System Ready ");
  lcd.write((byte)2);
  delay(2000);
  lcd.clear();
}

void playStartupMelody() {
  tone(BUZZER_PIN, 523, 200);
  delay(250);
  tone(BUZZER_PIN, 659, 200);
  delay(250);
  tone(BUZZER_PIN, 784, 200);
  delay(250);
  noTone(BUZZER_PIN);
}

void buzzFanOn() {
  tone(BUZZER_PIN, 880, 150);
  delay(200);
  noTone(BUZZER_PIN);
}

void buzzFanOff() {
  tone(BUZZER_PIN, 440, 150);
  delay(200);
  noTone(BUZZER_PIN);
}
