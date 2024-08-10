void INSERT_BOTTLE()
{
  if (Insert == true)
  {
    nexLoop(nex_listen_list);

    if (Page3_Display == false && Insert == true)
    {
      setServoAngle(Servo_Entrance, 60);
      Serial.print("page 3");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Serial.print("page 3");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Page3_Display = true;
    }
    if (Back_Page3 == true)
    {
      setServoAngle(Servo_Entrance, 0);
      Page3_Display = false;
      Page2_Display = false;
      Start_Display = false;
      Insert = false;
      Back_Page3 = false;
      
    }
    STORAGE_MONITORING();
  }
}

void ULTRASONIC_ITEM_DETECTION()
{
  int VAL_INDUCTIVE = digitalRead(INDUCTIVE_SENSOR);

  digitalWrite(TRIG_BOTTLE, HIGH); // eto yung para sa entrance
  delayMicroseconds(1000);
  digitalWrite(TRIG_BOTTLE, LOW); // eto yung para sa entrance
  Detect_Duration = pulseIn(ECHO_BOTTLE, HIGH);
  Detect_Bottle = (Detect_Duration / 2) / 29.1;
  Serial.print("ULTRASONIC_DETECTION:");
  Serial.println(Detect_Bottle);
  Serial.print("VAL_INDUCTIVE:");
  Serial.println(VAL_INDUCTIVE);

  if (Detect_Bottle < 6 && VAL_INDUCTIVE == 1 && Insert == true)
  {
    setServoAngle(Servo_Entrance, 0);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Scanning Item....");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Scanning Item....");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(1000);
    LOADCELL_VERIFICATION();
  }
  else if (Detect_Bottle < 6 && VAL_INDUCTIVE == 0 && Insert == true)
  {
    setServoAngle(Servo_Entrance, 0);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Metal Item Detected!");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Metal Item Detected!");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    setServoAngle(Servo_Accepted, 150);
    delay(2000);
    setServoAngle(Servo_Loadcell, 110);
    delay(1500);
    setServoAngle(Servo_Loadcell, 200);
    delay(1500);
    setServoAngle(Servo_Accepted, 80);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Invalid Item!");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Invalid Item!");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);

    delay(1000);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    setServoAngle(Servo_Entrance, 60);
  }
  else
  {
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}
void ULTRASONIC_BOTTLE_DETECTION()
{
  digitalWrite(TRIG_BOTTLE, HIGH); // eto yung para sa entrance
  delayMicroseconds(1000);
  digitalWrite(TRIG_BOTTLE, LOW); // eto yung para sa entrance
  Detect_Duration = pulseIn(ECHO_BOTTLE, HIGH);
  Detect_Bottle = (Detect_Duration / 2) / 29.1;
  Serial.print("ULTRASONIC_DETECTION:");
  Serial.println(Detect_Bottle);
}

void VERIFICATION_PROCESS()
{
  int VAL_INDUCTIVE = digitalRead(INDUCTIVE_SENSOR);
  Serial.println(VAL_INDUCTIVE);
  ULTRASONIC_BOTTLE_DETECTION();

  if ((VAL_INDUCTIVE == 1) && (Detect_Bottle <= 6))
  {
    digitalWrite(SIGNAL_ARDUINO, LOW);
    delay(1500);
    digitalWrite(SIGNAL_ARDUINO, HIGH);
    Start_Detect = true;

    while (Start_Detect == true)
    {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis_02 >= interval_02)
      {
        undetected++;
        previousMillis_02 = currentMillis;
      }

      if (undetected == 15)
      {
        setServoAngle(Servo_Entrance, 60);
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("Detection Error!");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("Detection Error!");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        delay(1500);
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("Insert Item Properly!");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("Insert Item Properly!");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        delay(4000);

        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        Start_Detect = false;
        undetected = 0;
        setServoAngle(Servo_Entrance, 60);
      }
      if (digitalRead(SIGNAL_ACCEPTED) == HIGH)
      {
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("Plastic Bottle!");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("Plastic Bottle!");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        weight = 0;
        pulses_bottles += 1;

        setServoAngle(Servo_Accepted, 80);
        delay(1000);
        setServoAngle(Servo_Loadcell, 110);
        delay(1500);
        setServoAngle(Servo_Loadcell, 200);
        delay(1000);
        setServoAngle(Servo_Entrance, 60);

        Serial.print("CountB.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print(pulses_bottles);  // This is the value you want to send to that object and atribute mentioned before.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("CountB.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print(pulses_bottles);  // This is the value you want to send to that object and atribute mentioned before.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        undetected = 0;
        Start_Detect = false;
        break;
      }
      else if (digitalRead(SIGNAL_REJECTED) == HIGH)
      {
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("Invalid Item!");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("Invalid Item!");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        setServoAngle(Servo_Accepted, 150);
        delay(2000);
        setServoAngle(Servo_Loadcell, 110);
        delay(1500);
        setServoAngle(Servo_Loadcell, 200);
        delay(1500);
        setServoAngle(Servo_Accepted, 80);
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.print("");  // This is the text you want to send to that object and atribute mentioned before.
        Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
        Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        Serial.write(0xff);
        Serial.write(0xff);
        setServoAngle(Servo_Entrance, 60);
        Start_Detect = false;
        undetected = 0;
      }
    }
  }
}

void STORAGE_MONITORING()
{
  // ----------------------------- BOTTLE BIN ULTRASONIC ---------------------------------//
  digitalWrite(TRIG_BIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIG_BIN, LOW);
  Bin_Duration  = pulseIn(ECHO_BIN, HIGH);
  Bin_Bottle = (Bin_Duration / 2) / 29.1;
  Serial.print("ULTRASONIC_BOTTLE_BIN:");
  Serial.println(Bin_Bottle);
  delay(20);

  if (Bin_Bottle <= 10 )
  {
    if (BIN_NOTIF == false)
    {
      SMS_NOTIFICATION_BOTTLES();
      BIN_NOTIF = true;
    }
    Serial.print("page 12");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("page 12");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    delay(2000);
    Serial.print("page 2");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("page 2");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Page3_Display = false;
    Page2_Display = false;
    Start_Display = false;
    Insert = false;
  }
  else
  {
    BIN_NOTIF = false;
    Serial.print("CountB.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(pulses_bottles);  // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("CountB.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(pulses_bottles);  // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    ULTRASONIC_ITEM_DETECTION();
  }
}
