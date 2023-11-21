#include "I2CScanner.h"
I2CScanner scanner;

void setup()              // This function is called once when the Arduino first starts up. It's used for initial setup tasks.
{
Serial.begin(9600);
while (!Serial) {};
scanner.Init();          // The Init function is presumably part of the I2CScanner library and is likely used to initialize settings or configurations necessary for the I2C scan
}

void loop()
{
scanner.Scan();
delay(5000);
}