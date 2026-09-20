const int pin = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Time,Voltage");
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor1 = analogRead(pin);
  Serial.print(millis());
  Serial.print(",");
  Serial.print(sensor1);
  Serial.write(13);
  Serial.write(10);
  
  delay(1000);
}
