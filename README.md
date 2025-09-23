# Embedded-Systems  

A collection of university projects involving **Arduino**, **ATmega328P**, **ESP32**, and general embedded systems development.  

---

## 📂 Repository Structure  
- **Arduino328P**  
  Smart autonomous microbot written in Embedded C.  
  - Implements obstacle avoidance and motor control.  
  - Main codebase located in `CA5`.  

- **Greenhouse_Atmega328p_code**  
  Arduino C++ code for a greenhouse environmental monitoring system.  
  - Features:  
    - Temperature, humidity, and light monitoring  
    - Fan and buzzer control with LCD feedback  
    - Wi-Fi connectivity (ESP8266)  
    - Data logging to ThingSpeak + AI-based predictions  
  - 🌐 Dashboard + AI predictions: [greenhouse-dashboard](https://github.com/ProfessionalEngineer23/greenhouse-dashboard)  

---

## 🚀 Features  
- ✅ Real-time sensor monitoring (Temp, Humidity, Light, Soil Temp)  
- ✅ Wi-Fi enabled data logging  
- ✅ Custom LCD animations & system alerts  
- ✅ Modular project structure (secrets managed via `arduino_secrets.h`)  
- ✅ Integration with ThingSpeak + AI prediction pipeline  

---

## 🛠️ Getting Started  

### Prerequisites for Greenhouse hub code 
- Arduino IDE or PlatformIO  
- Required libraries:  
  - `OneWire`, `DallasTemperature`, `LiquidCrystal`, `rgb_lcd`, `Arduino_SensorKit`  

### Setup  
1. Clone the repository  
   ```bash
   git clone https://github.com/ProfessionalEngineer23/Embedded-Systems-.git
