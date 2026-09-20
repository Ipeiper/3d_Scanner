const int pin = 0;
const  int READSPEED = 20;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Time,Voltage");
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor1 = analogRead(pin);
  int sensor2 = analogRead(pin);
  int sensor3 = analogRead(pin);
  int min1=min(sensor1,sensor2);
  int sensorReal=min(min1,sensor3);

  Serial.print(millis());
  Serial.print(",");
  Serial.print(sensorReal);
  Serial.write(13);
  Serial.write(10);
  
  delay(READSPEED);
}
