# 🏠🌡️ Apple HomeKit Temperature & Humidity Station

<div align="center">

![HomeKit](https://img.shields.io/badge/Apple-HomeKit-000000?style=for-the-badge&logo=apple&logoColor=white)
![ESP8266](https://img.shields.io/badge/ESP8266-000000?style=for-the-badge&logo=espressif&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

*Transform your home into a smart environment with native Apple HomeKit integration! 🍎*

[🚀 Features](#-features) • [📱 HomeKit Setup](#-homekit-setup) • [🔧 Installation](#-installation) • [📊 Sensors](#-sensors) • [🤝 Contributing](#-contributing)

</div>

---

## 🌟 What is This?

Turn your ESP8266 into a professional **Apple HomeKit Weather Station**! This project creates a native HomeKit accessory that appears directly in your iPhone's Home app - no additional apps required!

### 🎯 **The Magic**
- **Native HomeKit Integration** 🏠 - Appears directly in Apple Home app
- **Dual Sensor Support** 📊 - DHT11 + BMP280 for redundancy
- **Real-time Monitoring** ⏱️ - Live temperature and humidity updates
- **Zero Configuration** ✨ - Automatic HomeKit discovery and pairing

---

## 🚀 Features

### 🏠 **Apple HomeKit Native**
- **No Bridge Required**: Direct HomeKit accessory (not Homebridge!)
- **Home App Integration**: Shows up automatically in iOS/macOS Home app
- **Siri Compatible**: "Hey Siri, what's the temperature in the living room?"
- **Automation Ready**: Trigger scenes based on temperature/humidity thresholds

### 🌡️ **Professional Sensors**
- **DHT11 Sensor**: Temperature (-40°C to +80°C) & Humidity (5%-95%)
- **BMP280 Sensor**: High-precision temperature backup & atmospheric pressure
- **Sensor Redundancy**: Automatically switches between sensors for reliability
- **Calibrated Readings**: Factory-calibrated sensors for accuracy

### ⚡ **Smart Features**
- **Auto-Discovery**: Appears in HomeKit setup automatically
- **Low Power**: Efficient ESP8266 implementation
- **OTA Updates**: Over-the-air firmware updates (future feature)
- **Status LED**: Visual feedback for connection status

### 📱 **HomeKit Benefits**
- **Multi-Device Access**: iPhone, iPad, Mac, Apple Watch, Apple TV
- **Secure Connection**: End-to-end encryption via HomeKit protocol
- **Remote Access**: Control from anywhere via Apple TV/HomePod hub
- **Automation Engine**: Create complex scenes and automations

---

## 📱 HomeKit Setup

### 🔍 **Adding to Home App**

1. **Open Home App** on your iPhone/iPad
2. **Tap "+" → Add Accessory**
3. **Scan QR Code** or enter setup code manually
4. **Follow Setup Wizard** - Name your station and assign to a room

### 📊 **What You'll See**

```
🏠 Home App Display:
┌─────────────────────────┐
│    Meteo Station        │
│  🌡️ 23.4°C   💧 65%     /
│     Living Room         │
└─────────────────────────┘
```

### 🎙️ **Siri Commands**
- *"Hey Siri, what's the temperature?"*
- *"Hey Siri, what's the humidity in the living room?"*
- *"Hey Siri, is it humid inside?"*

### 🏠 **Automation Ideas**
- **Turn on humidifier** when humidity < 40%
- **Send notifications** when temperature exceeds 26°C
- **Control smart thermostat** based on room temperature
- **Turn on fans** when humidity > 70%

---

## 🔧 Installation

### 📦 **Hardware Requirements**

| Component | Model | Purpose | Price |
|-----------|-------|---------|-------|
| **Microcontroller** | ESP8266 (NodeMCU/Wemos D1) | Main controller | ~$3 |
| **Temperature/Humidity** | DHT11 | Primary sensor | ~$2 |
| **Pressure/Temp Backup** | BMP280 | Secondary sensor | ~$3 |
| **Breadboard** | Half-size | Prototyping | ~$2 |
| **Jumper Wires** | Male-to-Male | Connections | ~$2 |
| **Power Supply** | USB 5V 1A | Power source | ~$3 |

**💰 Total Project Cost: ~$15**

### 🔌 **Wiring Diagram**

```
ESP8266 NodeMCU  →  DHT11 Sensor
─────────────────    ────────────
3.3V             →  VCC
GND              →  GND  
D5 (GPIO14)      →  DATA

ESP8266 NodeMCU  →  BMP280 Sensor
─────────────────    ─────────────
3.3V             →  VCC
GND              →  GND
D1 (GPIO5)       →  SCL
D2 (GPIO4)       →  SDA
```

### 💻 **Software Setup**

#### 1. **Prerequisites**
```bash
# Install PlatformIO
pip install platformio

# Or use VS Code with PlatformIO extension
```

#### 2. **Clone & Configure**
```bash
git clone https://github.com/Arsalan134/AppleHome-TempHumidity.git
cd AppleHome-TempHumidity
```

#### 3. **WiFi Configuration**
Create `src/wifi_info.h`:
```cpp
#ifndef WIFI_INFO_H_
#define WIFI_INFO_H_

const char* wifi_ssid = "YourWiFiName";
const char* wifi_password = "YourWiFiPassword";

#endif
```

#### 4. **Build & Upload**
```bash
# Build the project
pio run

# Upload to ESP8266
pio run --target upload

# Monitor serial output
pio device monitor --baud 115200
```

---

## 📊 Sensors

### 🌡️ **DHT11 Temperature & Humidity**
- **Temperature Range**: -40°C to +80°C (±2°C accuracy)
- **Humidity Range**: 5% to 95% RH (±5% accuracy)
- **Response Time**: 6-15 seconds
- **Power**: 3-5V, 2.5mA max current

### 🌐 **BMP280 Pressure & Temperature**
- **Temperature Range**: -40°C to +85°C (±1°C accuracy)
- **Pressure Range**: 300-1100 hPa (±1 hPa accuracy)
- **Interface**: I2C/SPI (using I2C)
- **Power**: 1.71-3.6V, 2.7μA current

### 🔄 **Sensor Redundancy Logic**
```cpp
// Smart sensor switching for reliability
if (dht_reading_valid) {
    use_dht11_temperature();
} else {
    fallback_to_bmp280_temperature();
}
```

---

## 🛠️ Configuration

### ⚙️ **HomeKit Settings**

Located in `my_accessory.c`:
```c
// Customize your device info
HOMEKIT_CHARACTERISTIC(NAME, "Meteo Station"),
HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Arsalan"),
HOMEKIT_CHARACTERISTIC(MODEL, "MyTemperatureSensor"),
HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
```

### 📡 **Update Intervals**
```cpp
// Adjust reporting frequency (in main.cpp)
static uint32_t next_report_millis = 0;
const uint32_t REPORT_INTERVAL = 10000; // 10 seconds
```

### 🔧 **Pin Configuration**
```cpp
// Change sensor pins if needed
#define DHTPIN D5        // DHT11 data pin
// BMP280 uses I2C: D1(SCL), D2(SDA)
```

---

## 🔍 Troubleshooting

### ❗ **Common Issues**

| Problem | Solution |
|---------|----------|
| **Device not found in Home app** | Check WiFi connection, reset HomeKit pairing |
| **"No Response" in Home app** | Verify ESP8266 is powered and connected to WiFi |
| **Inaccurate readings** | Check sensor wiring, ensure proper power supply |
| **Constant sensor errors** | Verify DHT11 connections, try different pins |

### 🔄 **Reset HomeKit Pairing**
```cpp
// Add this to setup() function
homekit_storage_reset(); // Clears existing HomeKit pairings
```

### 📊 **Serial Debug Output**
```
Temperature: 23.4°C
Humidity: 65.2%
HomeKit client connected
Characteristic updated: Temperature
```

---

## 🎯 Advanced Features

### 🔮 **Future Enhancements**
- [ ] **OTA Updates**: Wireless firmware updates
- [ ] **Web Interface**: Browser-based configuration
- [ ] **Data Logging**: Store historical data to SD card
- [ ] **Multiple Sensors**: Support for additional sensor types
- [ ] **Battery Power**: Low-power mode for battery operation

### 🏗️ **Hardware Expansions**
- **Display Module**: OLED/LCD for local readings
- **External Antenna**: Better WiFi range
- **Weatherproof Case**: Outdoor installation
- **Solar Panel**: Self-powered operation

---

## 🤝 Contributing

We welcome contributions! Here's how you can help:

### 🛠️ **Development Areas**
- 🔧 Add support for more sensor types (DHT22, SHT30, etc.)
- 📱 Improve HomeKit integration features
- ⚡ Optimize power consumption
- 🌐 Add web-based configuration interface
- 📊 Implement data logging capabilities

### 📝 **How to Contribute**
1. Fork the repository
2. Create feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open Pull Request

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

### 🍎 **HomeKit Compatibility**
This project uses the open-source HomeKit implementation and is compatible with Apple's HomeKit ecosystem without requiring MFi certification.

---

## 🙋‍♂️ Author

**Arsalan Iravani**
- 🔗 LinkedIn: [@airavani](https://www.linkedin.com/in/airavani/)
- 📧 Email: [Contact](mailto:airavani2018@gmail.com)

---

## 🚀 About Me

I'm an **iOS Developer** and **Smart Home Enthusiast** passionate about bridging Apple's ecosystem with custom hardware. This project showcases the power of native HomeKit integration without expensive commercial solutions.

**Other Projects**: 📱 iOS Apps • 🏠 HomeKit Accessories • 🚗 Automotive Electronics • 🛩️ Drone Technology

---

## 🔗 Related Projects

- **[BMW-OBD2](https://github.com/Arsalan134/BMW-OBD2)** - OBD2 RPM visualizer for BMW
- **[Mazda-OBD2](https://github.com/Arsalan134/Mazda-OBD2)** - OBD2 RPM visualizer for Mazda
- **[Ground-Lora](https://github.com/Arsalan134/Ground-Lora)** - LoRa ground control station

---

<div align="center">

### 🌟 **Star this repo if you found it helpful!** 🌟

**Made with ❤️ and lots of ☕ for the Apple HomeKit community**

*"The best smart home is the one that works seamlessly with your existing devices"*

</div>
