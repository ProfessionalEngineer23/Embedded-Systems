# Embedded-Systems  

A collection of university projects involving **Arduino**, **ATmega328P**, **ESP32**, and general embedded systems development.  

---

## 📂 Repository Structure  
- **Arduino328P** → Smart Autonomous Microbot  
- **Greenhouse_Atmega328p_code** → IoT Greenhouse Monitoring Hub  

---

## Project 1: Arduino328P – Smart Autonomous Microbot  
<img width="200" height="400" alt="image" src="https://github.com/user-attachments/assets/40c4d715-1625-486f-947e-1f9595b5f16e" />

### 🔧 Overview 
An embedded systems project demonstrating robotics, Bluetooth control, and autonomous navigation. The microbot integrates sensors, led indicators for interactive functionality implemented through raw embedded c programming and hardware setup.  

### ⚙️ Features  
- 🚗 **Remote Control Mode** via Bluetooth (UART communication)  
- 🔄 **Autonomous Mode** using **HC-SR04 Ultrasonic Sensor** for obstacle detection & avoidance  
- 🔊 **Buzzer alerts** when reversing or triggered from mobile app  
- 💡 **Lighting System**  
  - Front headlights  
  - Rear lights  
  - Left/Right indicator LEDs  
- 🌡️ **LM35 Temperature Sensor** for live data monitoring  
- 📡 **Bidirectional communication** (sending & receiving data via UART)  
- 🎶 **Dance Function** for demonstration & fun interaction
- Check out the demonstration video: https://youtube.com/shorts/MYuRv3px1k4?feature=share
---

## Project 2: Greenhouse_Atmega328p_code – IoT Greenhouse Monitoring Hub  
<img width="600" height="400" alt="image" src="https://github.com/user-attachments/assets/3c330ea2-2400-46ad-9113-1efabf20078a" />

### 🔧 Overview  
An IoT project built with **ATmega328P**, **ESP8266 Wi-Fi**, and multiple sensors. It provides real-time environmental monitoring, cloud connectivity, and AI-powered predictions for smart greenhouse management.  

### ⚙️ Features  
- 🌡️ **Sensors**  
  - **DHT20** → Air Temperature & Humidity  
  - **DS18B20** → Soil Temperature  
  - **LDR** → Light Intensity  
- 💨 **Relay-controlled Fan** → Automatically turns on/off based on set temperature threshold  
- 🔊 **Passive Buzzer** → Plays startup melodies and alerts when fan state changes  
- 🖥️ **LCD Display** → Shows real-time sensor values and fan state locally  
- 🌐 **Cloud Integration**  
  - **ESP8266 Wi-Fi** uploads sensor data to ThingSpeak via REST API 
  - **Dashboard** hosted on Render for visualization, code can be viewed here: https://github.com/ProfessionalEngineer23/greenhouse-dashboard
  - Demonstration video: https://youtube.com/shorts/Hdc7Yb3v1_c?feature=share
  - Development vlog: https://www.youtube.com/playlist?list=PLw1CliiFCSWNNFSFAg9YIj1HqUXdAepGj

- **AI/ Algorithm Predictions**  
  - Implemented using Python + XGBoost on Google Colab
  - Predicts future greenhouse sensor values and exports them as graph images and .csv files. (temperature, humidity, soil temp, light)
   <img width="800" height="500" alt="image" src="https://github.com/user-attachments/assets/eac9c367-9580-43f1-9b43-a904b2b918b3" />
   <img width="800" height="500" alt="image" src="https://github.com/user-attachments/assets/7cdf633d-e083-4a95-b674-317e6a89b85d" />
   <img width="800" height="500" alt="image" src="https://github.com/user-attachments/assets/b4445bcc-7ed1-47d7-9764-f9642d7ba40d" />
   <img width="800" height="500" alt="image" src="https://github.com/user-attachments/assets/6e81284a-2f32-4a46-9eea-322c75c1d332" />





---

### Prerequisites for Greenhouse.ino code 
- Arduino IDE or PlatformIO  
- Libraries:  
  - `OneWire`  
  - `DallasTemperature`  
  - `LiquidCrystal`  
  - `rgb_lcd`  
  - `Arduino_SensorKit`  

