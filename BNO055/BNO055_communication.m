clear
tic;
% check the serial port name in the terminal: ls /dev/tty.*
s = serialport("/dev/tty.usbmodem14401",9600); 

orient = [];                % ith column is ith angular orientation 
maxIteration = 2*10^2;      % approximately 20 seconds of data collecting
iteration = 0;
whileFlag = 1;

while whileFlag
    iteration = iteration + 1;
    % Read data from serial port
    data = readline(s);
    parsedData = sscanf(data, "Orientation: %f, %f, %f");
    % Process or display the data
    disp(parsedData);
    orient_iter_ea = parsedData;
    orient = [orient orient_iter_ea];       % expand the matrix size

    % if iteration reach maxIteration terminate
    if iteration == maxIteration
        fprintf('done with collecting orientation')
        whileFlag = 0;
        disp(orient)
    end
end

toc;