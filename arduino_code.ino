#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "SparkFun_VL53L1X.h"
#include "HX711.h"

// Initialize sensors
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
SFEVL53L1X distanceSensor;
HX711 scale;

// HX711 pins
#define LOADCELL_DOUT_PIN 3
#define LOADCELL_SCK_PIN 2
float calibration_factor = -7470.0;  // Calibration factor for scale

void setup() {
  Serial.begin(115200);

  // Initialize MLX90614
  mlx.begin();

  // Initialize VL53L1X
  Wire.begin();
  distanceSensor.begin();
  distanceSensor.startRanging();  // Begin continuous measurements

  // Initialize HX711
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);  // Set calibration factor
  scale.tare();  // Tare the scale at startup
}

void loop() {
  float temperature = 0;

  // Prompt to take temperature
  Serial.println("Please take temperature");
  do {
    temperature = mlx.readObjectTempF() + 6.3;
    delay(500);  // Check every half second to allow user readiness
  } while (temperature < 93.0 || temperature > 105.0);

  // Display valid temperature for 5 seconds
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println(" °F");
  delay(5000);  // Display temperature for 5 seconds

  // Prompt for height and weight measurement
  Serial.println("Please align your feet on the platform");
  delay(10000);  // 10-second delay to allow user to align feet

  // Measure and average distance
  unsigned long startTime = millis();
  long totalDistance = 0;
  int count = 0;
  while (millis() - startTime < 5000) {  // Collect data for 5 seconds
    if (distanceSensor.checkForDataReady()) {
      int distance = distanceSensor.getDistance();
      totalDistance += distance;
      count++;
      distanceSensor.clearInterrupt();
    }
  }
  float averageDistance = count > 0 ? totalDistance / float(count) : 0;
  float distanceInches = 79.0 - (averageDistance * 0.0393701);
  int distanceFeet = int(distanceInches) / 12;
  float inchesRemaining = distanceInches - (distanceFeet * 12);
  if (inchesRemaining >= 11.5) {
    inchesRemaining = 0.0;
    distanceFeet++;
  }

  // Measure and average weight
  startTime = millis();
  float totalWeight = 0;
  int weightCount = 0;
  while (millis() - startTime < 3000) {  // Collect weight data for 3 seconds
    float sensorValue = scale.get_units();
    totalWeight += sensorValue;
    weightCount++;
    delay(500);  // Short delay to manage sampling rate
  }
  float averageWeight = (weightCount > 0) ? totalWeight / weightCount : 0;

  // Output all readings
  for (int i = 0; i < 3; i++) {
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.println("°F");
    delay(1000);
    Serial.print("Height: ");
    Serial.print(distanceFeet);
    Serial.print("'");
    Serial.print(int(inchesRemaining));
    Serial.println('"');
    delay(1000);
    Serial.print("Weight: ");
    Serial.print(averageWeight, 1);
    Serial.println(" lbs");
    delay(1000);
  }

  delay(3000);  // Optional: Wait before the next loop iteration
}

