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

### **Reference Photos**
| Throttle Modification | Engine Bay Layout | Gas Pedal Linkage |
| :---: | :---: | :---: |
| ![Throttle](throttle1.jpg) | ![Engine](engine-bay.jpg) | ![Pedal](gas-pedal.jpg) |

---

## 🔌 2. Wiring & Electronics
The Arduino acts as the "Idle Control Unit," monitoring engine loads and adjusting the servo position in real-time.

### **Complete Wiring Table**
| Function | Pin | Component | Note |
| :--- | :--- | :--- | :--- |
| **RPM Input** | D2 | PC817 Optocoupler | Tapped from Ignition Coil |
| **PSP Switch** | D3 | OEM Pressure Switch | Detects Power Steering load |
| **AC Signal** | D4 | AC Clutch Wire | Detects AC Compressor load |
| **Temp Sensor** | D6 | DS18B20 | Reads engine coolant temperature |
| **Servo Output** | D9 | MG996R / SG90 | Controls physical idle opening |
| **Display** | A4/A5 | SSD1306 OLED | I2C Data/Clock |
| **Buzzer** | D11 | Active 5V Buzzer | Stall Alarm (RPM < 550) |
| **Voltage** | A0 | Resistor Divider | Optional Battery Monitor (30k/7.5k) |

![Wiring Reference](/images/Arduino_Reference_Model.png)

---

## 🖥️ 3. The Software Logic
The code uses a simplified PID loop to maintain target RPM:
* **Cold Start:** 1100 RPM (until > 50°C)
* **Base Idle:** 750 RPM
* **AC Compensation:** +150 RPM
* **Steering Compensation:** +100 RPM

### **Dashboard Interface States**
| Boot Screen | Main Dash | Menu System | Settings |
| :---: | :---: | :---: | :---: |
| ![Dash1](/images/Display1.png) | ![Dash2](/images/Display2.png) | ![Dash3](/images/Display3.png) | ![Dash4](/images/Display4.png) |

---

## 📐 4. 3D Printable Designs
This project includes a custom enclosure for the Arduino Uno/Nano and the OLED display.

### **Control Unit Assembly**
| Base | Lid | Final Assembly |
| :---: | :---: | :---: |
| ![Base](/images/Base.png) | ![Lid](/images/Lid_Plain.png) | ![Full](/images/Assembled.jpg) |

### **Download STL Files**
* 📦 **Main Case:** [Base.stl](/3D-files/Uno-case/Base.stl) | [Lid.stl](/3D-files/Uno-case/Lid_Plain.stl) | [Lock.stl](/3D-files/Uno-case/E-Lock.stl)
* 📦 **Buttons:** [Button_Button.stl](/3D-files/Uno-case/Button_Button.stl)
* 📦 **OLED Mount:** [OLED_Case_Front.stl](/3D-files/Display/OLED-SSD1306-case-front.stl) | [OLED_Case_Back.stl](/3D-files/Display/OLED-SSD1306-case-back.stl)

---

## 🚀 5. Installation & Calibration
1. **Flash:** Upload the `XTrail_T30_IdleControl.ino` to your Arduino.
2. **Mounting:** Bolt the Servo Bracket near the throttle body.
3. **Power:** Use a **12V to 5V (3A) Buck Converter**.

### **Working Prototype**
![Working Model](working-model-table.jpg)
*(Video of operations coming soon)*

---

## 🚦 6. First Start & Calibration Guide
### **Step 1: Mechanical "Dry Run"**
* Use the **UP/DOWN** buttons to move the servo.
* ![Calibration](/images/Lid_Marked.png)
* **The Snap Test:** Ensure the external return spring pulls the throttle shut even if the servo is active.

### **Step 2: Sensor Verification**
Check OLED for:
* **TMP:** Ambient temp.
* **BAT:** ~12.6V.
* **RPM:** `0` (Engine off).

---

## ⚖️ 7. PID Tuning & Troubleshooting
| Variable | Default | If RPM Bounces... | If RPM is Slow... |
| :--- | :--- | :--- | :--- |
| **Kp** | `0.35` | Decrease value | Increase value |
| **Ki** | `0.02` | Decrease value | Increase value |
| **Kd** | `0.08` | Increase value | Decrease value |

![Diagnostic](/images/Screen_Shot_2015-04-07_at_5.00.05_PM.png)

---

## ⚠️ Safety Warning
* Always ensure your **Mechanical Return Spring** is stronger than the servo motor.
* Use a **1A Fuse** on the 12V power supply.
* **Testing:** Perform your first start in Neutral with the handbrake engaged.

---

## 🤝 Contributing
Built by **Jay Overlander**. If you have improved the PID tuning or designed a better bracket, feel free to submit a Pull Request or email me at: **jmwakideu@jaylansolutions.co.ke**

---
