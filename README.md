# Smart Mirror with Raspberry Pi and Arduino

This project implements a **Smart Mirror** system that integrates a Raspberry Pi, an Arduino, and various sensors to measure and display temperature, height, and weight on a connected display.

---

## Features

- **Temperature Measurement**: Uses an MLX90614 infrared temperature sensor to capture and display body temperature.
- **Height Measurement**: Employs a VL53L1X time-of-flight sensor to calculate height.
- **Weight Measurement**: Utilizes an HX711 module and a load cell to measure weight.
- **Real-Time Display**: Displays sensor data on a full-screen graphical interface powered by Pygame.
- **Interactive Interface**: Allows users to reset the system for new measurements via a keyboard.

---

## Hardware Requirements

- **Raspberry Pi** (tested on Raspberry Pi 4)
- **Arduino Uno** (for sensor control and data collection)
- **MLX90614** Infrared Temperature Sensor
- **VL53L1X** Time-of-Flight Distance Sensor
- **HX711** Load Cell Amplifier + Load Cell
- **HDMI Display** (connected to Raspberry Pi for visual output)
- **USB Cable** (to connect Arduino to Raspberry Pi)
- **Miscellaneous**: Jumper wires, breadboard, etc.

---

## Software Requirements

Ensure you have the following installed on the Raspberry Pi:

- Python 3.x
- Pygame
- PySerial

Install missing libraries using:
```bash
sudo apt update
pip install pygame pyserial
```

---

## Project Workflow

1. **Arduino Setup**:
   - Reads data from the MLX90614, VL53L1X, and HX711 sensors.
   - Processes the raw data and sends it via Serial to the Raspberry Pi.

2. **Raspberry Pi Setup**:
   - Receives the data from the Arduino through the Serial USB connection.
   - Displays the data in real-time using Pygame.

3. **User Interaction**:
   - Users can view their temperature, height, and weight measurements.
   - The interface resets when prompted to start a new measurement cycle.

---

## How to Run

1. **Set Up Hardware**:
   - Connect the MLX90614, VL53L1X, and HX711 sensors to the Arduino Uno.
   - Connect the Arduino to the Raspberry Pi via USB.
   - Attach the HDMI display to the Raspberry Pi.

2. **Upload Arduino Code**:
   - Upload the provided Arduino sketch (`arduino_code.ino`) to the Arduino Uno using the Arduino IDE.

3. **Run Python Code**:
   - Copy the Python script (`mirror_display.py`) to your Raspberry Pi.
   - Execute the script:
     ```bash
     python3 mirror_display.py
     ```

4. **View Measurements**:
   - Follow the on-screen instructions to take measurements and view results.

---

## File Structure

```
SmartMirror/
│
├── arduino_code.ino       # Arduino code for sensor integration
├── mirror_display.py      # Python code for Raspberry Pi display
├── README.md              # Project documentation
└── images/                # Add screenshots or wiring diagrams here
```

---

## Outputs

- **Temperature**: Measured in Fahrenheit.
- **Height**: Displayed in feet and inches.
- **Weight**: Displayed in pounds.

---

## Acknowledgments

Special thanks to the creators of the libraries for MLX90614, VL53L1X, and HX711 sensors for making hardware integration seamless.

