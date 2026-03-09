# 🏎️ Nissan X-Trail T30 "Hybrid" Throttle & Idle Control System
### Project Aim: Solving the Electronic Throttle Body (ETB) Failure
The Nissan X-Trail T30 (QR20DE) is notorious for Throttle Body motor failures which lead to expensive repairs or dangerous "Limp Mode" events. This project converts the system into a **Manual Cable-Driven Throttle** while using an **Arduino-controlled Servo** to manage the critical idle air compensation (AC, Power Steering, and Cold Starts).

---

## 🛠️ 1. Mechanical Modification: The "Hybrid" Body
To bypass the electronic motor, the throttle body must be physically modified to accept a manual cable and an idle-assist shaft.

### **The Transformation Steps:**
1. **Shaft Extension:** Remove the plastic gear cover. Weld a steel extension or a threaded bolt to the butterfly valve shaft.
2. **The Pulley:** Attach a circular pulley to the new shaft extension for the accelerator cable.
3. **The Helper Servo:** A high-torque servo is mounted via a 3D-printed bracket. Its arm is positioned to "push" the throttle open slightly (0–15%) to maintain idle.
4. **Safety Return Spring:** **CRITICAL.** Install a heavy-duty external spring to ensure the throttle snaps shut if the cable or servo fails.



---

## 🔌 2. Wiring & Electronics
The Arduino Nano acts as the "Idle Control Unit," monitoring engine loads and adjusting the servo position in real-time.

### **Complete Wiring Table**
| Function | Pin | Component | Note |
| :--- | :--- | :--- | :--- |
| **RPM Input** | D2 | PC817 Optocoupler | Tapped from Ignition Coil (High Voltage Protection) |
| **PSP Switch** | D3 | OEM Pressure Switch | Detects Power Steering load |
| **AC Signal** | D4 | AC Clutch Wire | Detects AC Compressor load |
| **Temp Sensor** | D6 | DS18B20 | Reads engine coolant temperature |
| **Servo Output** | D9 | MG996R / SG90 | Controls physical idle opening |
| **Display** | A4/A5 | SSD1306 OLED | I2C Data/Clock |
| **Buzzer** | D11 | Active 5V Buzzer | Stall Alarm (RPM < 550) |
| **Voltage** | A0 | Resistor Divider | Optional Battery Monitor (30k/7.5k) |



---

## 🖥️ 3. The Software Logic
The code uses a simplified PID loop to maintain target RPM:
* **Cold Start:** 1100 RPM (until > 50°C)
* **Base Idle:** 750 RPM
* **AC Compensation:** +150 RPM
* **Steering Compensation:** +100 RPM

> **Note:** The code includes an EEPROM save feature. Long-press the **MENU** button to save your custom idle settings.

---

## 📐 4. 3D Printable Designs
This project requires two specific 3D prints to handle the environment:

### **A. Engine Bay Servo Bracket**
* **Material:** MUST be **ASA or ABS** (PLA will melt).
* **Function:** Holds the MG996R servo rigid against the engine vibration.
* **Infill:** 40% Gyroid for maximum structural strength.

### **B. Dashboard Display Casing**
* **Material:** PETG or ABS.
* **Features:** Mounts for the 0.96" OLED, 3 tactile buttons (Menu/Up/Down), and the Arduino Nano.
* **Port:** Includes a side-access hole for the Mini-USB programming port.



---

## 🚀 5. Installation & Calibration
1. **Flash:** Upload the `XTrail_T30_IdleControl.ino` to your Arduino Nano.
2. **Mounting:** Bolt the Servo Bracket near the throttle body. Connect the linkage.
3. **Power:** Use a **12V to 5V (3A) Buck Converter**. The car's 12V is too "dirty" and powerful for the Arduino's internal regulator.
4. **Test:** With the engine OFF, turn the key. Use the UP/DOWN buttons to test if the servo moves the throttle butterfly smoothly.

---

## ⚠️ Safety Warning
This is a custom mechanical modification. 
* Always ensure your **Mechanical Return Spring** is stronger than the servo motor.
* Use a **1A Fuse** on the 12V power supply to the Arduino.
* **Testing:** Perform your first start in Neutral with the handbrake engaged.

---

## 🤝 Contributing
Built by **Jay Overlander**. If you have improved the PID tuning or designed a better bracket, feel free to submit a Pull Request!

---
