About The Project:

Status: Currently Migrating to ESP-IDF v5.3 and FreeRTOS

Biometric monitoring system implemented on ESP32 to measure heart rate and blood oxygen. This project utilizes a photometer and OLED screen to display visual feeback (current status of the system, user instructions, beats per minute, etc). 

Built With:
- ESP-WROOM-32 Microcontroller
- 0.96 in. I2C OLED Display
- MAX30102 Heart Rate Sensor/Photometer

Technical Stack:
- Framework: ESP-IDF v5.3 (originally PlatformIO/Arduino)
- Operating System: FreeRTOS
- Environment: Docker-based container
- Protocols: I2C, UART

Photo (as of 3/25):
<img width="914" height="571" alt="image" src="https://github.com/user-attachments/assets/a7ced517-831a-4474-b1de-b8353d8e119a" />


Possible Future Implementation:
- Second display w/ PPG Waveform Visualization (likely using matplotlib)
- Alarm system when Tachycardia, Badycardia, or Arrythmia are detected
