# Intelligent Greenhouse Climate Controller (IoT & Fuzzy Logic)

An advanced Internet of Things (IoT) system designed for automated greenhouse climate control, powered by an ESP32 microcontroller. The system utilizes a Takagi-Sugeno Fuzzy Logic inference engine to make smart, smooth control decisions (such as variable fan speed control via PWM) based on real-time environmental data. All telemetry data is securely transmitted to a cloud platform.

---

## 🚀 Key Features
* **Fuzzy Logic Control (Sugeno):** Smooth and precise regulation of actuators based on sensor inputs using trapezoidal membership functions (`MfTrap`).
* **IoT Architecture:** Real-time environmental monitoring with telemetry data securely stored in a high-performance **InfluxDB** time-series database.
* **Modular Hardware Design:** Hand-assembled on a perfboard (THT) using Kynar wire-wrapping wire and female goldpin headers, ensuring high mechanical durability and easy component replacement.
* **Cloud Integration:** Data processing, storage, and visualization hosted on a cloud platform deployed via the *Azure for Students* program.

---

## 🛠️ System Architecture & Data Flows

### Node-RED Logic & Backend Flows
<img width="878" height="778" alt="image" src="https://github.com/user-attachments/assets/95c0cfa0-ec55-44ff-b14e-398090d63cc6" />


### 📊 User Interface & Cloud Dashboard
<img width="1900" height="920" alt="dashboard_overview" src="https://github.com/user-attachments/assets/6b1de5d6-cc5b-4263-a014-4a21335ca133" />
<img width="1900" height="920" alt="dashboard_historicaltrends" src="https://github.com/user-attachments/assets/1cf66317-bee5-4d0c-a520-cae189b35060" />
<img width="1900" height="920" alt="dashboard_ctrlpanel" src="https://github.com/user-attachments/assets/d3e00b81-ca09-4249-8f0a-04de8ff7fe53" />

---

## 💾 Hardware Implementation
Before assembly, the circuit schematic and component layout were carefully planned and designed using **KiCad**. Following the design phase, the prototype was fully implemented on a universal perfboard, providing a rigid, compact and impact-resistant build.

**Component Breakdown:**
* **ESP32** Microcontroller (Wi-Fi/MQTT)
* **I2C Sensor Array** (Ambient Temperature, Relative Humidity, and Light Intensity)
* **OLED Display** (On-site, real-time parameter debugging)
* **Actuators** (PWM-controlled exhaust fan, heating element, and irrigation valves)

### 📷 Hardware Showcase
<img width="4000" height="3000" alt="soldered_board" src="https://github.com/user-attachments/assets/dd88656b-62e9-4e5a-927a-c24af5577e66" />


---

## 🧠 How the Control Algorithm Works
The controller processes climate adjustments in three distinct steps:
1. **Fuzzification:** Converts "crisp" sensor readings (e.g., 24°C) into degrees of membership representing linguistic states (e.g., "Optimal" or "Hot").
2. **Inference (Rule Evaluation):** Evaluates the fuzzified inputs against the predefined rule base (e.g., *IF Temperature is Hot, THEN set Fan Speed to Maximum*).
3. **Defuzzification:** Computes the exact, final control signal (0-255 PWM duty cycle) using a weighted average calculation based on the constant numerical singletons assigned to each rule's output.

---

## 💻 Tech Stack & Tools
* **Language/Framework:** C++ (PlatformIO) / Arduino Framework
* **Communication Protocol:** MQTT
* **Cloud Infrastructure:** Microsoft Azure (*Azure for Students* tier)
* **Data Integration & Orchestration:** Node-RED
