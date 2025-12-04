# Enhanced-Edition-Of-E-Vehicle-Energy-Supply-System
1. Introduction

Electric Vehicles (EVs) are becoming an essential part of modern transportation, but they still face challenges such as limited driving range, slow charging, and lack of charging infrastructure, especially in rural areas.This project presents a smart energy supply system that uses a dual-battery switching mechanism, solar-based automatic charging, and IoT monitoring to improve reliability and range of EVs. The system ensures continuous operation by switching between two batteries and uses renewable solar energy to reduce dependency on grid charging.

2. Objective

To design and implement an enhanced EV energy system using:
   Smart dual-battery automatic switching
   Solar charging with MPPT
   IoT monitoring for voltage, SoC, and alerts
The goal is to provide continuous power, extended range, and a sustainable charging solution for electric vehicles.

3. Components Used

   ESP32 / Arduino UNO – Handles sensor inputs, battery switching logic, and IoT communication.
   Primary EV Battery – Main power source for running the EV motor.
   Secondary EV Battery – Backup battery used when the primary battery is low.
   Solar Panel (PV Module) – Generates renewable power for charging the secondary battery.
   Voltage Sensor (INA219 / Voltage Divider) – Measures real-time battery voltage for SoC calculation.
   Relay Module  – Enables fast and safe switching between Battery-1 and Battery-2.
   Motor  – DC motor to run the wheel
   Wires, Connectors, Terminals – Used for electrical connections and power routing.

4. How it works:
   Sensors continuously monitor voltage and SoC of both batteries. When the primary battery drops below threshold, the system automatically switches to the secondary battery. Solar panel charges the idle battery through the MPPT controller. IoT system sends real-time data to dashboard. This ensures zero downtime, improved range, and higher energy efficiency.

5. Solar Charging & MPPT Key Features:
   MPPT extracts maximum power even under varying sunlight Protects battery from overcharge Ensures fast and efficient solar charging
Working:
   Solar panel produces DC voltage. MPPT optimizes the voltage-current combination. Energy is stored in the secondary battery. When fully charged, the system stops charging to protect battery life.

6. IoT Monitoring System The system uses
   ESP32/Wi-Fi/GSM for real-time monitoring of: Battery voltage State of Charge (SoC) , Current flow ,Sensor status ,Fault alerts.
7. Circuit Description Connections :-
    Batteries → Relay/MOSFET switching module → Motor controller Solar Panel → MPPT → Secondary Battery Voltage sensors → ESP32 analog/digital pins IoT module → Wi-Fi/GSM network ESP32 → Relay driver module (for switching)
   Working Steps:-
    ESP32 reads SoC from sensors. Based on logic, it selects either Battery 1 or Battery 2. MPPT charges secondary battery using solar energy. IoT module updates the dashboard continuously.

8. Algorithm Initialize all modules
   (sensors, switching, IoT).
   Read voltage and SoC of both batteries.
   If Primary Battery < threshold → switch to Secondary Battery.
   Charge the idle battery using solar+MPPT.
   Update IoT dashboard with real-time data.
   Repeat the cycle continuously.

9. Applications
    Electric scooters and bikes
    Auto-rickshaws e-rickshaws
    Rural EVs with no charging stations
    Delivery vehicles needing long operation time
    EVs used in agriculture and remote locations

10. Advantages
    ✅ Continuous power supply using dual batteries
    ✅ Renewable charging using solar energy
    ✅ Less dependency on grid charging
    ✅ Extended driving range
    ✅ Real-time IoT monitoring
    ✅ Low-cost and scalable system

11. Limitations
    ⚙️ Higher initial setup cost compared to single-battery EVs
    ⚙️ Solar charging speed depends on weather conditions
    ⚙️ Requires proper protection circuits for safety
    ⚙️ Dual-battery management increases complexity
    
12. Conclusion
    This project successfully demonstrates an advanced EV energy supply system that uses dual-battery switching, solar charging, and IoT monitoring. The system ensures uninterrupted operation, improved range, and promotes green mobility. It is highly suitable for rural and semi-urban EV usage where charging stations are limited.

13. Images :-
    <img width="1224" height="1254" alt="image" src="https://github.com/user-attachments/assets/7de7186c-dc64-460a-b852-6c5651e40d6c" />
    <img width="1207" height="1280" alt="image" src="https://github.com/user-attachments/assets/3de1187f-5020-4852-a908-d32f84fd5e12" />
    <img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/56747902-7278-42e3-b8e1-10b6e2f74b25" />
    <img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/d010bf11-8e89-480b-9da9-93f977cca892" />


    
    


    
