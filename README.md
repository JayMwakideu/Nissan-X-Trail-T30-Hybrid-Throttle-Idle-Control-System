# 🏎️ Nissan X-Trail T30 "Hybrid" Throttle & Idle Control System

### **Project Aim: Permanently Solving Electronic Throttle Body (ETB) Failure**

The Nissan X-Trail T30 (QR20DE/QR25DE) suffers from a notorious flaw: Electronic Throttle Body motor failure. This leads to erratic idling, Limp Mode, and expensive repairs.

This project bypasses the electronic failure points entirely by converting the system to a **Manual Cable-Driven Throttle**. An **Arduino-controlled Servo** is then used as a "helper" to manage critical idle air compensation (AC load, Power Steering load, and Cold Starts), creating a reliable, bulletproof solution.

---

## 🛠️ 1. Mechanical Modification: The "Hybrid" Body

To bypass the unreliable electronics, the throttle body must be physically modified to accept a manual accelerator cable and an idle-assist servo shaft.

### **Transformation Steps:**
1.  **Shaft Extension:** Weld a steel extension or a threaded bolt to the end of the main butterfly valve shaft.
2.  **The Pulley:** Attach a circular pulley to the new shaft extension for the manual accelerator cable.
3.  **The Helper Servo:** Mount a high-torque servo using a 3D-printed bracket. The servo arm "pushes" the throttle linkage to "crack" the butterfly open slightly (0–15%) to maintain idle.
4.  **Failsafe Return Spring:** **CRITICAL SAFETY STEP.** Install a heavy-duty external spring to ensure the throttle snaps shut if the cable or servo fails.

### **Modification Reference Photos**
*(Upload your photos to the repository to activate these links)*

| Modified Throttle Body | Engine Bay Installation | Gas Pedal Linkage |
| :---: | :---: | :---: |
| ![Throttle](throttle1.jpg) | ![Engine](engine-bay.jpg) | ![Pedal](gas-pedal.jpg) |

---

## 🔌 2. Wiring & Electronics

The Arduino (Uno/Nano) acts as the new "Idle Control Unit," monitoring engine loads and adjusting the servo position in real-time.

### **Complete Wiring Table**

| Function | Pin | Component | Note |
| :--- | :--- | :--- | :--- |
| **RPM Input** | D2 | PC817 Optocoupler | Tapped from Ignition Coil (Must use Opto!) |
| **PSP Switch** | D3 | OEM Pressure Switch | Detects Power Steering load |
| **AC Signal** | D4 | AC Clutch Wire | Detects AC Compressor load |
| **Temp Sensor** | D6 | DS18B20 | Reads engine coolant temperature |
| **Servo Output** | D9 | MG996R / SG90 | Controls physical idle opening |
| **Display** | A4/A5 | SSD1306 OLED | I2C Data/Clock |
| **Buzzer** | D11 | Active 5V Buzzer | Stall Alarm (RPM < 550) |
| **Voltage** | A0 | Resistor Divider | Optional Battery Monitor (30k/7.5k) |

---

## 🖥️ 3. Software Logic & UI

The code uses a simplified PID loop to maintain target RPM based on input loads.

### **Dashboard Interface Gallery**
Here is a sequence showing the bootloader, main telemetry dash, and the EEPROM settings menu.

<table border="0">
  <tr>
    <td align="center"><img src="/images/Display1.png" width="200"><br><em>Boot Logo</em></td>
    <td align="center"><img src="/images/Display2.png" width="200"><br><em>Main Telemetry</em></td>
    <td align="center"><img src="/images/Display3.png" width="200"><br><em>Menu System</em></td>
  </tr>
  <tr>
    <td align="center"><img src="/images/Display4.png" width="200"><br><em>Settings Adjust</em></td>
    <td align="center"><img src="/images/Display5.png" width="200"><br><em>Save Prompt</em></td>
    <td align="center"><img src="/images/Display6.png" width="200"><br><em>Data Log View</em></td>
  </tr>
</table>

> **Note:** Long-press the **MENU** button to save your custom idle settings to EEPROM.

---

## 📐 4. 3D Printable Designs

The project relies on two distinct 3D printed assemblies.

### **A. Arduino Uno Control Casing**
This robust casing houses the main microcontroller, buttons, and the buzzer.

<table border="0">
  <tr>
    <td align="center"><img src="/images/Base.png" width="200"><br><em>Main Base</em></td>
    <td align="center"><img src="/images/Arduino_Fit.jpg" width="200"><br><em>Uno Fitment</em></td>
    <td align="center"><img src="/images/Button_Button.png" width="100"><br><em>Button Caps</em></td>
  </tr>
  <tr>
    <td align="center"><img src="/images/Lid_Plain.png" width="200"><br><em>Lid (Plain)</em></td>
    <td align="center"><img src="/images/Lid_Marked.png" width="200"><br><em>Lid (Marked)</em></td>
    <td align="center"><img src="/images/Full_Assembly.jpg" width="200"><br><em>Final Assembly</em></td>
  </tr>
</table>

#### **Download Uno Case STLs:**
* 📦 [Base.stl](/3D-files/Uno-case/Base.stl)
* 📦 [Lid_Plain.stl](/3D-files/Uno-case/Lid_Plain.stl)
* 📦 [Button_Button.stl](/3D-files/Uno-case/Button_Button.stl)
* 📦 [E-Lock.stl](/3D-files/Uno-case/E-Lock.stl)
* 📦 [Whole_Assembly.stl](/3D-files/Uno-case/Whole_Assembly.stl)

***

### **B. OLED Display & Dashboard Mount**
A dedicated enclosure for the 0.96" SSD1306 OLED, designed for easy dashboard integration.

<table border="0">
  <tr>
    <td align="center"><img src="/images/Whole_Assembly.png" width="250"><br><em>OLED Mount Concept</em></td>
    <td align="center"><img src="/images/Assembled.jpg" width="250"><br><em>Physical Build</em></td>
  </tr>
</table>

#### **Download Display STLs:**
* 📦 [OLED_Case_Front.stl](/3D-files/Display/OLED-SSD1306-case-front.stl)
* 📦 [OLED_Case_Back.stl](/3D-files/Display/OLED-SSD1306-case-back.stl)
* 📂 [OLED_Case_Source.123dx](/3D-files/Display/OLED-SSD1306-case.123dx)

---

## 🚀 5. Installation & Operation Demos

### **Prototype Working Model (Table Test)**
Before installing on the vehicle, the system was validated on a bench setup.

![Working Model](working-model-table.jpg)

### **Operation Video**
*(Video link coming soon)*

<a href="https://www.youtube.com/watch?v=YOUR_VIDEO_ID_HERE" target="_blank"><img src="https://img.youtube.com/vi/YOUR_VIDEO_ID_HERE/0.jpg" alt="Watch the T30 Hybrid Throttle in Action" width="560" height="315" border="10" /></a>

---

## ⚠️ Safety Warning & Disclaimer

This is a custom mechanical modification to a critical vehicle system. **Use at your own risk.**

* **Failsafe:** Always ensure your **Mechanical Return Spring** is significantly stronger than the servo motor's output force. The spring must be able to snap the throttle closed even if the servo is active.
* **Fusing:** Use a **1A Fuse** on the 12V power supply to the Arduino.
* **Testing:** Perform your first engine start in Neutral with the handbrake firmly engaged.

---

## 🤝 Contributing

Built by **Jay Overlander**. If you have improved the PID tuning values for the QR20DE engine or designed a better bracket, feel free to submit a Pull Request!

For support or questions, email me at: **jmwakideu@jaylansolutions.co.ke**

---
