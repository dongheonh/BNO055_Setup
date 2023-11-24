import serial
import time

# Setup serial connection (adjust COM port as needed)
ser = serial.Serial('/dev/tty.usbmodem14401', 9600, timeout=1)
time.sleep(2)  # Wait for connection to establish

# Open a file to save the calibration data
with open("calibration_data.txt", "w") as file:
    while True:
        if ser.in_waiting:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            file.write(line + "\n")
