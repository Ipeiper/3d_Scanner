#include <Servo.h>
//Servo pin
const int sense_pin = A0;
const int serv_pan_pin = 5;
const int serv_tilt_pin = 3;
//Read speed is in miliseconds between measurements
const  int READSPEED = 1000;
//servo object
Servo pan;
Servo tilt;
//scan Parameters in degrees
int pan_center = 90
int pan_left = pan_center - 30;
int pan_right = pan_center + 30;
int pan_step = 1;
int tilt_center = 90;
int tilt_down = tilt_center - 30;
int tilt_up = tilt_center + 30;
int tilt_step = 5;
// servo position 
int pan_pos=pan_left;
int tilt_pos=tilt_down;
// Movement direction
// 0 is moving up
// 1 is moving right
// 2 is movine left
int move_dir = 1;




//start time
unsigned long start_time = millis();
unsigned long last_time = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Time,Voltage,Pan,Tilt");
  //bind servo objects to their pins
  pan.attach(serv_pan_pin);
  tilt.attach(serv_tilt_pin);

  // set up to start neutral
  pan.write(pan_pos);
  tilt.write(tilt_pos);
}

void loop() {
  // put your main code here, to run repeatedly:
  //starts the timer
  start_time=millis();
  //Here is the servo looping code
  //if move_dir = 1


  int sensor1 = analogRead(sense_pin);
  int sensor2 = analogRead(sense_pin);
  int sensor3 = analogRead(sense_pin);
  int min1=min(sensor1,sensor2);
  int sensorReal=min(min1,sensor3);
  
  // This prints the values from the sensors and motor in a comma seperated format with order time, ir voltage, pan, tilt
  Serial.print(millis());
  Serial.print(",");
  Serial.print(sensorReal);
  Serial.print(",");
  // this is the pan value with positive being to the right and negative being to the left
  Serial.print(pan_pos);
  Serial.print(",");
  // this is the tilt value with positive being up and negative being down
  Serial.print(tilt_pos);
  Serial.write(13);
  Serial.write(10);
  // change to dynamically account for runtime using start time and last time
  last_time=start_time;
  delay_time=max(0,READSPEED-(millis()-start_time));
  delay(delay_time);
}
