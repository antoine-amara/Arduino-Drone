#include <Wire.h>

int cal_int;
unsigned long UL_timer;
double gyro_roll, gyro_pitch, gyro_yaw;
double gyro_roll_cal, gyro_pitch_cal, gyro_yaw_cal;
byte lowByte, highByte;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  Wire.beginTransmission(107);
  Wire.write(0x20);
  Wire.write(0x0F);
  Wire.endTransmission();
  
  Wire.beginTransmission(107);
  Wire.write(0x23);
  Wire.write(0x80);
  Wire.endTransmission();
  
  delay(250);
  
  Serial.print("Starting Calibration ...");
  for(cal_int = 0; cal_int < 2000; cal_int++) {
    gyro_signalen();
    gyro_roll_cal += gyro_roll;
    gyro_pitch_cal += gyro_pitch;
    gyro_yaw_cal += gyro_yaw;
    if(cal_int % 100 == 0) Serial.print(".");
    delay(4);
  }
  Serial.println("done");
  gyro_roll_cal /= 2000;
  gyro_pitch_cal /= 2000;
  gyro_yaw_cal /= 2000;
}

void loop() {
  delay(250);
  gyro_signalen();
  print_output();
}

void gyro_signalen() {
  Wire.beginTransmission(107);
  Wire.write(168);
  Wire.endTransmission();
  Wire.requestFrom(107, 6);
  while(Wire.available() < 6);
  lowByte = Wire.read();
  highByte = Wire.read();
  gyro_roll = ((highByte << 8)|lowByte);
  if(cal_int == 2000) gyro_roll -= gyro_roll_cal;
  lowByte = Wire.read();
  highByte = Wire.read();
  gyro_pitch = ((highByte << 8)|lowByte);
  gyro_pitch *= -1;
  if(cal_int == 2000) gyro_pitch -= gyro_pitch_cal;
  lowByte = Wire.read();
  highByte = Wire.read();
  gyro_yaw = ((highByte << 8)|lowByte);
  gyro_yaw *= -1;
  if(cal_int == 2000) gyro_yaw -= gyro_yaw_cal;
}

void print_output() {
  Serial.println("Pitch: ");
  if(gyro_pitch >= 0) Serial.print("+");
  Serial.print(gyro_pitch/57.14286, 0);
  if(gyro_pitch/57.14286 - 2 > 0) Serial.print("NoU");
  else if(gyro_pitch/57.14286 + 2 > 0) Serial.print("NoD");
  else Serial.print("---");
  Serial.println("Roll:");
  if(gyro_roll >= 0) Serial.print("+");
  Serial.print(gyro_roll/57.14286, 0);
  if(gyro_roll/57.14286 - 2 > 0) Serial.print("RwU");
  else if(gyro_roll/57.14286 + 2 > 0) Serial.print("RwD");
  else Serial.print("---");
  Serial.println("Yaw:");
  if(gyro_yaw >= 0) Serial.print("+");
  Serial.print(gyro_yaw/57.14286, 0);
  if(gyro_yaw/57.14286 - 2 > 0) Serial.print("NoR");
  else if(gyro_yaw/57.14286 + 2 > 0) Serial.print("NoL");
  else Serial.print("---");
}
