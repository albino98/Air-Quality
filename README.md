# 🌫️ Air-Quality

**Air quality monitoring using ESP8266 and PMS5003 sensor**

This project measures particulate matter (PM1.0, PM2.5, PM10) using a PMS5003 sensor connected to an ESP8266.  
Data is averaged and sent to [ThingSpeak](https://thingspeak.com/) for logging and visualization.

---

## 📦 Hardware Components

- **Board:** ESP8266 (NodeMCU or Wemos D1 Mini)
- **Sensor:** PMS5003 (Particulate Matter Sensor)
- **Power supply:** 5V (USB or external)
- **WiFi:** Required for sending data to ThingSpeak

---

<!--
## 🔌 Wiring

| PMS5003 Pin | ESP8266 Pin   | Description                             |
|-------------|----------------|-----------------------------------------|
| TX          | GPIO3 (RX)     | Sensor → ESP (Serial data)              |
| RX          | GPIO1 (TX)     | ESP → Sensor (optional)                 |
| VCC         | 5V             | Power supply                            |
| GND         | GND            | Ground                                  |

> ⚠️ Disconnect the sensor during code upload to avoid conflicts with the USB serial interface.  
> 📌 Use **5V** to power the PMS5003 (it does not work reliably at 3.3V).

---
-->
## 💻 Software Overview

The code is written for the Arduino IDE and uses the following libraries:

- `ESP8266WiFi.h` – for Wi-Fi connectivity
- `ThingSpeak.h` – to send data to ThingSpeak
- `PMS.h` – for reading data from PMS5003 sensor

### Setup steps:

1. Open the project in the Arduino IDE
2. Select your ESP8266 board (e.g., NodeMCU 1.0)
3. Install dependencies via **Library Manager**
4. Enter your Wi-Fi SSID, password, and ThingSpeak API keys in the code
5. Upload the sketch (**disconnect PMS5003 during upload**)
6. Open Serial Monitor to debug and view readings

⚠️ Connect the rst pin to d0 (for sleep mode) only after uploading the code.

---

## 📡 Data Flow

1. The sensor wakes up and stabilizes for 3 minutes
2. 10 readings are collected for PM1.0, PM2.5, and PM10
3. Averages are calculated
4. Data is sent to ThingSpeak using `writeRaw()`
5. The ESP8266 goes to deep sleep for ~24 minutes

---

## 🌐 ThingSpeak Integration

Make sure you:

- Create a ThingSpeak channel with **three fields** (PM1.0, PM2.5, PM10)
- Copy your **channel number** and **write API key** into the sketch

Example of data string sent:

api_key=XXXX&field1=12.5&field2=18.3&field3=21.7

## 💤 Power Saving

The ESP8266 uses `ESP.deepSleep()` for low-power operation.  
This makes the system suitable for battery-powered deployments.

---

## Support

If you find it useful, give it a ⭐ !

Feel free to fork it or open issues for feedback and suggestions.



<!-- connettere il pin rst al d0 (per la sleep mode) solo dopo aver caricato il codice. -->




