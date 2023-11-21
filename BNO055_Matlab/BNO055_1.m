% Author: Dong Heon Han @ FREE LAB
% 11/21/2023
clear 

% Device variables
ardn = arduino();                              % constructor method that initializes a new Arduino object "ardn"
bno = bno055(ardn, 'OperatingMode', 'ndof');   % constructor function used to create an instance of the BNO055 sensor object  
accCalib = 0; gyrCalib = 0; magCalib = 0;      % Accelerometer, Gyroscope, Magnetometer calibration flag

% Start the calibration
fprintf('Calibrating the BNO055 sensor . . . \n');

iter = 0;                                           % iteration initinalization 
while(prod([accCalib, gyrCalib, magCalib]) ~= 1)    % when all variable = 1, break
   iter = iter + 1;
   fprintf('\niteration %d\n', iter)                % show the iteration 
   
   % Sensor Readings
   acc = bno.readCalibrationStatus.Accelerometer;
   gyr = bno.readCalibrationStatus.Gyroscope;  
   magn = bno.readCalibrationStatus.Magnetometer; 
   
   % Display the acc gyr magn status
   fprintf('Accelerometer: ');  disp(acc); 
   fprintf('Gyroscope: '); disp(gyr); 
   fprintf('Magnetometer: '); disp(magn);    
   
   % Accelerometer Calibration
   if strcmpi(acc, "full") && isequal(accCalib, 0)
      accCalib = 1;
      fprintf('Accelerometer is calibrated! . . .\n');
   end
    
   % Gyroscope Calibration
   if strcmpi(gyr, "full") && isequal(gyrCalib, 0)
       gyrCalib = 1;
       fprintf('Gyroscope is calibrated! . . .\n');
   end
    
   % Magnetometer Calibration
   if strcmpi(magn, "full") && isequal(magCalib, 0)
       magCalib = 1;
       fprintf('Magnetometer is calibrated! . . .\n');
   end
end

fprintf('BNO055 sensor is fully calibrated!\n');

% Read orientation - 100 times
fprintf('READ ORIENTATION\n');
for i = 1:100
   readOrientation(bno)
end

clear ardn
