# BNO055_Tutorial


## A. Calibration

When using multiple BNO055 sensors, there are a few key points to consider regarding calibration:

1. **Individual Calibration**: Each BNO055 sensor must be calibrated individually. Calibration is specific to each sensor due to variations in sensor characteristics and mounting orientations. The calibration process involves rotating the sensor in various orientations to calibrate the accelerometer, magnetometer, and gyroscope.

2. **Storing Calibration Offsets**: The calibration offsets or data can indeed be saved for each individual BNO055 sensor. However, these offsets are not stored on the sensor itself. When you power down the sensor, it loses its calibration state. Therefore, you need to store the calibration data externally (e.g., in an Arduino's EEPROM, in a file on an SD card, or in flash memory, as we discussed earlier) and reload it to the sensor upon each power-up.

3. **Unique Identification for Each Sensor**: If you're using multiple sensors with a single Arduino or controller, you need a way to uniquely identify each sensor so you can apply the correct calibration offsets to each one. This could be as simple as storing each set of calibration data in a separate file or EEPROM address, labeled or named according to the sensor.

4. **Handling Multiple Sensors**: BNO055 sensors communicate over I2C, and each one has a default I2C address. To use multiple BNO055 sensors with a single microcontroller, you will need to change the I2C address of each sensor or use an I2C multiplexer. The BNO055 allows for a change in the I2C address via a pin (ADR/PS0), but you can only have two different addresses in this manner. For more than two sensors, an I2C multiplexer becomes necessary.

In summary, for eight BNO055 sensors, you will need to:

- Calibrate each sensor individually.
- Store the calibration data for each sensor externally.
- Upon each startup, load the correct calibration data to each respective sensor.
- Manage I2C addressing to communicate with each sensor individually, likely using an I2C multiplexer.

![acccalibration](https://github.com/dongheonh/BNO055_Setup/assets/142549534/58ba8824-9026-41ec-aae7-184a166b25c3) For more information on sensor calibration with Arduino, see the [MathWorks guide on calibrating sensors](https://www.mathworks.com/help/supportpkg/arduinoio/ug/calibrate-sensors.html).


