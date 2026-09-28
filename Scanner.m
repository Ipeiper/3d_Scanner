%52.7016exp(-0.7880x)+(-0.2026)

clear s
freeports = serialportlist("available") % Shows available serial ports
%
%Choose which port to use for Arduino (probably best to hardcoded)
%
ports = "/dev/ttyACM0";%freeports(2)
baudrate = 9600;
s = serialport("COM4",baudrate);

writeline(s,"Start")

%initialize a timeout in case MATLAB cannot connect to the arduino
timeout = 0;
i = 0;
a=zeros(1,2460); % Sets the varibles up to be stored with appending each list for faster speed
b=zeros(1,2460);
c=zeros(1,2460);
d=zeros(1,2460);
% main loop to read data from the Arduino, then display it%
while timeout < 5 % % check if data was received %
while s.NumBytesAvailable > 0
%
% reset timeout
%
timeout = 0;
%
% data was received, convert it into array of integers
%
values = eval(strcat('[',readline(s),']'));
%
% if you want to store the integers in four variables
%
a(i) = values(1);
b(i) = values(2);
c(i) = values(3);
d(i) = values(4);
%
% print the results
%
%disp(sprintf('a,b,c,d = %d,%d,%d,%d\n',[a,b,c,d]));
i = i+1;
end
pause(0.5);
timeout = timeout + 1;
end


nCols = 60;   % samples per line (pan sweep)
nRows = [];   % number of lines (tilt steps)

B = reshape(b, nCols, nRows)';   % transpose so rows = lines, cols = samples along line
C = reshape(c, nCols, nRows)';
D = reshape(d, nCols, nRows)';

% Un-zigzag: flip every other row left-right
B(2:2:end, :) = fliplr(B(2:2:end, :));
C(2:2:end, :) = fliplr(C(2:2:end, :));
D(2:2:end, :) = fliplr(D(2:2:end, :));

imagesc(C(1,:), D(:,1), B)   % pan angles as x, tilt angles as y, data as color
colorbar    
axis xy   
colormap abyss

Pigeon = gca; % Uploads heat map data png
Pigeonpng = 'CA.png'
exportgraphics(Pigeon,Pigeonpng)


time = a; % set up to find 3d map of pings
p = 52.7016.*exp(-0.7880.*B)+(-0.2026); % coverts to distance
theta = deg2rad(C);%Pan angle
phi = deg2rad(D);  %Tilt angle
rho = p; % varible legibity

% The radial distance ρ
% 
% The azimuthal angle θ
% 
% The polar angle ϕ

% x=ρsinϕcosθ,

% y=ρsinϕsinθ,

% z=ρcosϕ.
N = length(time);
x_P = zeros(1, N); % Same as before opmtiztion set up
y_P = zeros(1, N);
z_P = zeros(1, N);

for i=1:N; % converts polor cordanites to catiesatian

x_P(i) = rho(i)*sin(phi(i))*cos(theta(i));
y_P(i) = rho(i)*sin(phi(i))*sin(theta(i));
z_P(i) = rho(i)*cos(phi(i));


end


plot3(x_P,y_P,z_P,'ko','MarkerSize',5)
