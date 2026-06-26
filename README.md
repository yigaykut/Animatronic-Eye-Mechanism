# Animatronic-Eye-Mechanism
This project controls a 6-axis animatronic eye mechanism using an Arduino and a local Qwen Vision-Language Model (VLM). A snake/endoscope camera captures the live feed, passes it to the Qwen model to track a target, and maps the coordinates to drive 6 servo motors via serial communication.


# Repository Structure
As shown in the workspace layout, the project consists of the following core files:

servo.ino: The Arduino sketch managing the 6 servos with smooth micro-stepping logic to prevent jerky movements.

main.py: The Python bridge script. It captures camera frames, encodes them to Base64, sends them to the local Qwen API, parses the coordinates, and streams them to the hardware.

qwen.json: The central configuration file for serial ports, baud rates, camera index, and safety servo limits.

# Hardware Setup
Hardware Components
Arduino Uno / Nano

PCA9685 16-Channel 12-bit PWM I2C Servo Driver (Crucial for handling PWM signals and dedicated power routing for 6 servos)

6x SG90 (or similar) Servo Motors

1x USB Snake / Endoscope Camera

External 5V Power Supply (Connect directly to the PCA9685 power terminal block. Do NOT power the servos through the Arduino).

# Wiring & Channel Mapping
Arduino to PCA9685 (I2C Connection)
VCC -> Arduino 5V (for logic)

GND -> Arduino GND

SDA -> Arduino A4 (on Uno/Nano)

SCL -> Arduino A5 (on Uno/Nano)

# PCA9685 Servo Channels
The servos plug directly into the PCA9685 pin headers sequentially:

Channel 0: Eye 1 (X-Axis)

Channel 1: Eye 1 (Y-Axis)

Channel 2: Eye 2 (X-Axis)

Channel 3: Eye 2 (Y-Axis)

Channel 4: Eyelid Upper

Channel 5: Eyelid Lower

Make sure to share a common ground (GND) between the external 5V power supply, the PCA9685, and the Arduino.


# Arduino Pin Mapping
The servo.ino sketch expects the following pin connections:

Eye 1 (X-Axis): Pin 3

Eye 1 (Y-Axis): Pin 5

Eye 2 (X-Axis): Pin 6

Eye 2 (Y-Axis): Pin 9

Eyelid Upper: Pin 10

Eyelid Lower: Pin 11

Make sure to share a common ground between the external 5V power supply and the Arduino.

# Software Configuration
Configure the Local VLM: Ensure you have your local inference engine running (e.g., Ollama or a local OpenAI-compatible server hosting a model like Qwen2.5-VL-7B-Instruct).

Update Settings: Open qwen.json and adjust the configuration to match your system setup:

Change "serial_port" to match your Arduino port 

Verify "camera_index" points to your snake camera (usually 0 if it's the only camera, or 1/2 if you have an integrated webcam).

Tweak the "servo_limits" if your mechanical setup binds at specific angles.

# How to Run
Upload servo.ino to your Arduino using the Arduino IDE.

Install the Python dependencies:

pip install opencv-python pyserial requests pillow
Run the tracking bridge:

python main.py
