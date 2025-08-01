# Air-Quality

**Air quality monitoring using ESP8266 and PMS5003 sensor**

This project uses an ESP8266 WiFi board and a PMS5003 particulate matter sensor to measure air pollution levels (PM1.0, PM2.5, PM10).  
Data can be sent to a remote server or displayed locally on a screen.

---

## 📦 Hardware components

- **Board:** ESP8266 (e.g., NodeMCU or Wemos D1 Mini)  
- **Particulate Matter Sensor:** PMS5003   
- **Power:** 5V via USB or external power supply  

---

## 💻 Software

The code is written in C++ for the Arduino IDE.  
To use it:

1. Open the Arduino IDE and select the correct board (e.g., "NodeMCU 1.0 (ESP-12E Module)").  
2. Install the `SoftwareSerial` library if not already installed.  
3. Upload the code to your ESP8266 board.  

**Note:** Connect the RST pin to D0 (GPIO16) only after uploading the code to avoid the board entering deep sleep mode.
<!-- connettere il pin rst al d0 (per la sleep mode) solo dopo aver caricato il codice. -->
---

## 📡 Communication

The PMS5003 sensor communicates via UART serial interface.  
You can read the sensor data directly from the ESP8266 serial port or send it to a remote server using HTTP or MQTT.







