%52.7016exp(-0.7880x)+(-0.2026)

clear s
freeports = serialportlist("available") % Shows available serial ports
%
%Choose which port to use for Arduino (proabably best to hardcode)
%
ports = "/dev/ttyACM0";%freeports(2)
baudrate = 9600;
s = serialport("COM4",baudrate);

writeline(s,"Start")

%initialize a timeout in case MATLAB cannot connect to the arduino
timeout = 0;

a=[];
b=[];
c=[];
d=[];
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
a(end+1) = values(1);
b(end+1) = values(2);
c(end+1) = values(3);
d(end+1) = values(4);
%
% print the results
%
%disp(sprintf('a,b,c,d = %d,%d,%d,%d\n',[a,b,c,d]));
end
pause(0.5);
timeout = timeout + 1;
end



time = a;
p = 52.7016.*exp(-0.7880.*b)+(-0.2026); %
theta = deg2rad(c);%Pan angle
phi = deg2rad(d);  %Tilt angle
rho = p;
% The radial distance ρ
% 
% The azimuthal angle θ
% 
% The polar angle ϕ

% x=ρsinϕcosθ,

% y=ρsinϕsinθ,

% z=ρcosϕ.
N = length(time);
x_P = zeros(1, N);
y_P = zeros(1, N);
z_P = zeros(1, N);

for i=1:N;

x_P(i) = rho(i)*sin(phi(i))*cos(theta(i));
y_P(i) = rho(i)*sin(phi(i))*sin(theta(i));
z_P(i) = rho(i)*cos(phi(i));

end


plot3(x_P,y_P,z_P,'ko','MarkerSize',10,'MarkerFaceColor','k')
imagesc(y_P,z_P,x_P)
imagesc(c,d,b)