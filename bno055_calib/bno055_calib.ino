// Include necessary libraries for I2C communication and sensor interfacing
#include <Wire.h> // Wire library for I2C communication
#include <Adafruit_Sensor.h> // Adafruit Unified Sensor Driver
#include <Adafruit_BNO055.h> // Adafruit BNO055 library

// Define the I2C address for the TCA9548A multiplexer
#define TCAADDR 0x70

// Create instances of the BNO055 sensor, all with the same I2C address
Adafruit_BNO055 bno1 = Adafruit_BNO055(55, 0x28); // Sensor instance 1
Adafruit_BNO055 bno2 = Adafruit_BNO055(55, 0x28); // Sensor instance 2
Adafruit_BNO055 bno3 = Adafruit_BNO055(55, 0x28); // Sensor instance 3

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  Wire.begin(); // Initialize the I2C communication

  // Initialize each BNO055 sensor through the multiplexer
  initializeSensor(bno1, 0); // Initialize the first sensor
  initializeSensor(bno2, 1); // Initialize the second sensor
  initializeSensor(bno3, 2); // Initialize the third sensor
}

void loop() {
  // Continuously check and print calibration status for each sensor
  checkAndPrintCalibration(bno1, 0); // Check first sensor
  checkAndPrintCalibration(bno2, 1); // Check second sensor
  checkAndPrintCalibration(bno3, 2); // Check third sensor

  delay(1000); // Wait for 5 seconds before checking again
}

void tcaselect(uint8_t i) {
  if (i > 7) return; // If channel number is out of range, do nothing
  Wire.beginTransmission(TCAADDR); // Begin I2C transmission to the TCA9548A
  Wire.write(1 << i); // Select the appropriate channel (0 to 7)
  Wire.endTransmission(); // End the I2C transmission
}

void initializeSensor(Adafruit_BNO055& bno, uint8_t channel) {
  tcaselect(channel); // Select the appropriate channel on the multiplexer
  if (!bno.begin()) { // Begin communication with the BNO055 sensor
    Serial.println("Failed to initialize BNO055 on channel " + String(channel)); // Print error message if initialization fails
    while (1); // Infinite loop to halt further execution
  }
  delay(1000); // Wait for a short time after initialization
  bno.setExtCrystalUse(true); // Use the external crystal for more accuracy
}

void checkAndPrintCalibration(Adafruit_BNO055& bno, uint8_t channel) {
  tcaselect(channel); // Select the appropriate channel on the multiplexer
  uint8_t system, gyro, accel, mag; // Variables to store calibration status
  bno.getCalibration(&system, &gyro, &accel, &mag); // Get calibration status

  if (system == 0x03) { // Check if system calibration status is fully calibrated
    Serial.print("Fully Calibrated - Channel "); // Print the channel number
    Serial.print(channel);
    Serial.print(": ");

    adafruit_bno055_offsets_t calibrationData; // Structure to hold calibration data
    bno.getSensorOffsets(calibrationData); // Get sensor offsets

    // Print accelerometer offsets
    Serial.print("Accel: ");
    Serial.print(calibrationData.accel_offset_x); Serial.print(" ");
    Serial.print(calibrationData.accel_offset_y); Serial.print(" ");
    Serial.print(calibrationData.accel_offset_z); Serial.print(", ");

    // You can repeat the above lines to print gyro and magnetometer offsets
    // ...

    Serial.println(); // Print a newline
  } else {
    Serial.print("Not Calibrated - Calibrating sensor on channel "); // Print calibration message
    Serial.println(channel);
  }
}
