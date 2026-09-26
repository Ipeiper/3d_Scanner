#include <Servo.h>
//Servo pin
const int sense_pin = A0;
const int serv_pan_pin = 5;
const int serv_tilt_pin = 3;
//Read speed is in miliseconds between measurements
const  int READSPEED = 1000;
//wait time on start, currently 10 seconds
const int START_WAIT = 10*1000;
//define delay time
int delay_time = 0;

//servo object
Servo pan;
Servo tilt;
//scan Parameters in degrees
int pan_center = 90;
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
// 1 is moving right
// 2 is movine left
int move_dir = 1;
// End Tracking
bool end = false;



//start time
unsigned long start_time = 0;
unsigned long last_time = 0;

void setup() {
  // LED for use in signaling the user about Pauses and Program end
  pinMode(LED_BUILTIN, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Time,Voltage,Pan,Tilt");
  //bind servo objects to their pins
  pan.attach(serv_pan_pin);
  tilt.attach(serv_tilt_pin);

  // set up to start neutral
  pan.write(pan_pos);
  tilt.write(tilt_pos);
  //turns on the led and then waits START_WAIT time, then turns it off and runs the main loop
  digitalWrite(LED_BUILTIN,HIGH);
  delay(START_WAIT);
  digitalWrite(LED_BUILTIN,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  //starts the timer
  start_time=millis();
  //Here is the servo looping code
  if (end == true){
    // Turns on led to signal the code is done
    digitalWrite(LED_BUILTIN,HIGH);
    while(true){
      //does nothing forever to end the code
      delay(1000);
    }
  }
  if (move_dir == 1) {
    if (pan_pos+pan_step>=pan_right) {
      pan_pos=pan_right;
      pan.write(pan_pos);
      Move_up();
      move_dir=2;
    }
    else{
      pan_pos += pan_step;
      pan.write(pan_pos);
    }
  }
  else if (move_dir == 2) {
    if (pan_pos-pan_step<=pan_left) {
      pan_pos=pan_left;
      pan.write(pan_pos);
      Move_up();
      move_dir=1;
    }
    else {
      pan_pos -= pan_step;
      pan.write(pan_pos);
    }

  }

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

void Move_up(){
  if (tilt_pos == tilt_up){
    //end the code
    end=true;
  }
  else if (tilt_pos+tilt_step>= tilt_up){
    tilt_pos=tilt_up;
  }
  else {
    tilt_pos+=tilt_step;
  }
  tilt.write(tilt_pos);
}
