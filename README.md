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

## 🚦 6. First Start & Calibration Guide
Before turning the key, follow this diagnostic checklist to prevent high-rev surges or mechanical binding.

### **Step 1: Mechanical "Dry Run" (Engine OFF)**
1. Power the Arduino via USB or the 5V Buck converter (Key in 'ON' position, Engine 'OFF').
2. Use the **UP/DOWN** buttons on your control box to manually move the servo.
3. **Check for Binding:** Ensure the linkage moves freely from 0% to 20% throttle.
4. **The Snap Test:** Open the throttle manually by hand and let go. The external return spring **must** be strong enough to pull the servo back to the closed position.



### **Step 2: Sensor Verification**
Check the OLED display for the following readings before cranking:
* **TMP:** Should match ambient temperature (e.g., 25-30°C).
* **BAT:** Should read ~12.4V to 12.6V.
* **RPM:** Should read `0`.
* **AC/STR:** Toggle the AC switch and turn the steering wheel; the screen should update to `ON` for each.

### **Step 3: The "First Crank"**
1. Have an assistant ready to turn the key while you watch the throttle body.
2. If the engine revs above 2000 RPM instantly, **KILL THE IGNITION**. This means your `baseIdle` servo position is physically too open.
3. Once idling, let the engine reach 80°C. The `TMP` sensor will trigger the transition from `ColdIdle` (1100) to `BaseIdle` (750).

---

## ⚖️ 7. PID Tuning & Troubleshooting
If the idle "hunts" (RPM bounces up and down) or "lags" (drops too low when AC turns on), adjust the variables in the `XTrail_T30_IdleControl.ino` file:

| Variable | Default | If RPM Bounces... | If RPM is Slow to React... |
| :--- | :--- | :--- | :--- |
| **Kp** (Proportional) | `0.35` | Decrease value | Increase value |
| **Ki** (Integral) | `0.02` | Decrease value | Increase value |
| **Kd** (Derivative) | `0.08` | Increase value | Decrease value |



### **Troubleshooting "Ghost" Signals**
* **Erratic RPM:** Usually caused by electrical noise from the ignition coils. Ensure your **PC817 Optocoupler** is wired correctly and the wires are away from the spark plug leads.
* **Servo Jitter:** Ensure you have a **470µF Capacitor** across the Servo’s +5V and GND lines to smooth out voltage spikes.

---

## 🛠️ 8. Maintenance Schedule
* **Every 5,000km:** Inspect the welded shaft and pulley for hairline cracks.
* **Every 10,000km:** Lubricate the throttle cable and servo linkage with dry PTFE spray.
* **Summer/Winter:** You may want to use the **MENU** to adjust the `ColdIdle` target if you live in a climate with extreme temperature swings.

---

---

## 🤝 Contributing
If you have improved the PID tuning or designed a better bracket, feel free to submit a Pull Request! or email me on jmwakideu@jaylansolutions.co.ke

---
