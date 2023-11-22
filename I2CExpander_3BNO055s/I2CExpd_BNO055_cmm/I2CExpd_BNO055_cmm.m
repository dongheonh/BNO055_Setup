clear

tic;
% check the serial port name in the terminal: ls /dev/tty.*
s = serialport("/dev/tty.usbmodem14401",9600); 

orientIMU1 = [];                % ith column is ith angular orientation 
orientIMU2 = [];                % ith column is ith angular orientation
orientIMU3 = [];                % ith column is ith angular orientation

maxIteration = 2*10^2;          % approximately 20 seconds of data collecting
iteration = 0;
whileFlag = 1;

while whileFlag
    iteration = iteration + 1;
    % Read data from serial port
    data1 = readline(s);
    data2 = readline(s);
    data3 = readline(s);

    parsedData1 = sscanf(data1, "Orientation: %f, %f, %f");
    parsedData2 = sscanf(data2, "Orientation: %f, %f, %f");
    parsedData3 = sscanf(data3, "Orientation: %f, %f, %f");

    % Process or display the data
    fprintf('IMU1: \n')
    disp(parsedData1);
    fprintf('IMU2: \n')
    disp(parsedData2);
    fprintf('IMU3: \n')
    disp(parsedData3);

    orient_iter_ea_IMU1 = parsedData1;
    orientIMU1 = [orientIMU1 orient_iter_ea_IMU1];       % expand the matrix size

    orient_iter_ea_IMU2 = parsedData2;
    orientIMU2 = [orientIMU2 orient_iter_ea_IMU2];       % expand the matrix size

    orient_iter_ea_IMU3 = parsedData3;
    orientIMU3 = [orientIMU3 orient_iter_ea_IMU3];       % expand the matrix size


    % if iteration reach maxIteration terminate
    if iteration == maxIteration
        fprintf('done with collecting orientation')
        whileFlag = 0;
        disp(orient)
    end
end

toc;