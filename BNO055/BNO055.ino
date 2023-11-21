#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055();

void setup(void) {
    Serial.begin(9600); // communicate between the Arduino and a computer's serial monitor, or with other devices that use serial communication
    while (!Serial) {   // wait for serial to be ready - It inverts the value of the expression that follows it. So, !Serial means "not Serial"
    delay(1);           // Wait for Serial Monitor to open
    }

    Serial.println("Orientation Test");
   
    if (!bno.begin()) {                                               // Initialize the BNO055 sensor using its begin() method
    Serial.print("No BNO055 detected, check wiring or I2C address!"); // begin() method configures the sensor with default settings & establishes communication
    while (1);                                                        // loop after the error message to halt the program if the sensor is not detected      
    }
    bno.setExtCrystalUse(true);                                       // configure the BNO055 to use an external crystal for its timekeeping and operation (optional)
}

void loop(void) {
  sensors_event_t event;                                              // data structure (or a 'struct' in C/C++) defined by the Adafruit Unified Sensor Driver                                         
  bno.getEvent(&event);                                               // sensors_event_t: struct that holds sensor reading data in a uniform way
  
  Serial.print("Orientation: ");
  Serial.print(event.orientation.x, 3);                               // field/structure that specifically represents the x-axis value of the orientation
  Serial.print(", ");
  Serial.print(event.orientation.y, 3);
  Serial.print(", ");
  Serial.print(event.orientation.z, 3);
  Serial.println();

  delay(100);
}