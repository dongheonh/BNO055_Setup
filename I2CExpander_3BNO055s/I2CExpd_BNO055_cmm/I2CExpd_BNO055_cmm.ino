#include <Wire.h> // Include the Wire library for I2C communication
#include <Adafruit_Sensor.h> // Include Adafruit Sensor library for sensor interface
#include <Adafruit_BNO055.h> // Include Adafruit BNO055 library for the BNO055 sensor

// Define the I2C address for the TCA9548A multiplexer
#define TCAADDR 0x70

// Create instances of Adafruit_BNO055 for each BNO055 sensor
// Each instance is initialized with the same address, as the TCA9548A will be used to select the active sensor
Adafruit_BNO055 bno1 = Adafruit_BNO055(55, 0x28);
Adafruit_BNO055 bno2 = Adafruit_BNO055(55, 0x28);
Adafruit_BNO055 bno3 = Adafruit_BNO055(55, 0x28);

void setup() {
  Serial.begin(9600); // Start the Serial communication at 9600 baud rate
  Wire.begin(); // Initialize the I2C communication

  // Initialize and test connection with each BNO055 sensor
  tcaselect(0); // Select channel 0 on TCA9548A for BNO055 #1
  if (!bno1.begin()) {
    Serial.println("Failed to initialize BNO055 #1"); // Print error if initialization fails
    while (1); // Infinite loop to halt further execution
  }

  tcaselect(1); // Select channel 1 on TCA9548A for BNO055 #2
  if (!bno2.begin()) {
    Serial.println("Failed to initialize BNO055 #2"); // Print error if initialization fails
    while (1); // Infinite loop to halt further execution
  }

  tcaselect(2); // Select channel 2 on TCA9548A for BNO055 #3
  if (!bno3.begin()) {
    Serial.println("Failed to initialize BNO055 #3"); // Print error if initialization fails
    while (1); // Infinite loop to halt further execution
  }
}

void loop() {
  // Create a variable to hold sensor event data
  sensors_event_t event;

  // Read and print the orientation data from each BNO055 sensor
  tcaselect(0); // Select the first BNO055 sensor
  bno1.getEvent(&event); // Get the orientation data
  Serial.print("Orientation: "); // Print the sensor ID
  printOrientation(event.orientation); // Print the orientation data

  tcaselect(1); // Repeat for the second BNO055 sensor
  bno2.getEvent(&event);
  Serial.print("Orientation: ");
  printOrientation(event.orientation);

  tcaselect(2); // Repeat for the third BNO055 sensor
  bno3.getEvent(&event);
  Serial.print("Orientation: ");
  printOrientation(event.orientation);

  delay(500); // Delay for 3 seconds before the next reading
}

void tcaselect(uint8_t i) {
  // Function to select the channel on the TCA9548A
  if (i > 7) return; // Do nothing if the channel number is out of range

  Wire.beginTransmission(TCAADDR); // Start I2C transmission to the TCA9548A
  Wire.write(1 << i); // Send byte to select the appropriate channel
  Wire.endTransmission(); // End transmission
}

void printOrientation(sensors_vec_t orientation) {
  // Function to print orientation data
  Serial.print(orientation.x, 3);
  Serial.print(", ");
  Serial.print(orientation.y, 3);
  Serial.print(", ");
  Serial.print(orientation.z, 3);
  Serial.println();
}