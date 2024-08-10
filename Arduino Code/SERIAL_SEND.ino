void SERIAL_SEND_NODEMCU_EXPRESS()
{
  int Points = 0;
  int Status = 1;
  delay(20);
  Arduino_Serial.print(toString8(User_Card) + toString8(String(Points)) + toString8(String(Status)) + " \n");
  delay(1000);
}

void SERIAL_SEND_DISPENSE()
{
  int Status = 2;
  Arduino_Serial.print(toString8(User_Card) + toString8(String(User_Points)) + toString8(String(Status)) + " \n");
  delay(1000);
}

void SERIAL_DONE_INSERT()
{
  int Status = 3;
  Arduino_Serial.print(toString8(User_Card) + toString8(String(pulses_bottles)) + toString8(String(Status)) + " \n");
  delay(1500);

  if (Dispense_Display == false)
  {
    Serial.print("page 9");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("page 9");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    delay(1000);
    pulses_bottles = 0;
    Dispense_Display = true;
    setServoAngle(Servo_Entrance, 0);
    delay(20);
  }
  RESET_VARIABLES();
}

void RESET_VARIABLES()
{
  Validation = 0;
  User_Points = 0;
  pulses_bottles = 0;
  Insert = false;
  Reward = false;
  Select_Reward = false;
  Short = false;
  Long = false;
  Ballpen = false;
  Index = false;
  Dispense_Short = false;
  Dispense_Long = false;
  Dispense_Ballpen = false;
  Dispense_Index = false;
  Start_Display = false;
  Page2_Display = false;
  Page3_Display = false;
  Page4_Display = false;
  Page5_Display = false;
  Page6_Display = false;
  Page7_Display = false;
  Page8_Display = false;
  Page10_Display = false;
  Start_Detect = false;
  Back_Page2 = false;
  Back_Page3 = false;
  Back_Page4 = false;
  Back_Page5 = false;
  Back_Page6 = false;
  Back_Page7 = false;
  Back_Page8 = false;
  Back_Page10 = false;
  Dispense_Display = false;
  BIN_NOTIF = false;
  SHORT_NOTIF = false;
  LONG_NOTIF = false;
  BALLPEN_NOTIF = false;
  INDEX_NOTIF = false;
  User_Card = "";
  Prev_User = "";
  Display_User_Card = "";

  Serial.print("page 0");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  delay(20);
  Serial.print("page 0");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  delay(20);
  Serial.println("Reset!");
}

String toString8(String num) {
  String out;
  String raw = num;

  if (raw.length() == 1) {
    out = "0000000" + raw;
  }
  else if (raw.length() == 2) {
    out = "000000" + raw;
  }
  else if (raw.length() == 3) {
    out = "00000" + raw;
  }
  else if (raw.length() == 4) {
    out = "0000" + raw;
  }
  else if (raw.length() == 5) {
    out = "000" + raw;
  }
  else if (raw.length() == 6) {
    out = "00" + raw;
  }
  else if (raw.length() == 7) {
    out = "0" + raw;
  }
  else {
    out = raw;
  }
  return out;
}
