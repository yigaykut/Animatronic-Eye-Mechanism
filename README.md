# Animatronic-Eye-Mechanism
This project controls a 6-axis animatronic eye mechanism using an Arduino and a local Qwen Vision-Language Model (VLM). A snake/endoscope camera captures the live feed, passes it to the Qwen model to track a target, and maps the coordinates to drive 6 servo motors via serial communication.

Repository Structure
As shown in the workspace layout, the project consists of the following core files:

servo.ino: The Arduino sketch managing the 6 servos with smooth micro-stepping logic to prevent jerky movements.

main.py: The Python bridge script. It captures camera frames, encodes them to Base64, sends them to the local Qwen API, parses the coordinates, and streams them to the hardware.

qwen.json: The central configuration file for serial ports, baud rates, camera index, and safety servo limits.

