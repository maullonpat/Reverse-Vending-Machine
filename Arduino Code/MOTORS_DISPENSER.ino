void DISPENSE_SHORT(int val)
{
  if (val >= 1)
  {
    for (int i = 1 ; i <= val; i++)
    {
      SHORT_MOTOR_CW();
    }
  }
}

void DISPENSE_LONG(int val)
{
  if (val >= 1)
  {
    for (int i = 1 ; i <= val; i++)
    {
      LONG_MOTOR_CW();
    }
  }
}

void DISPENSE_BALLPEN(int val)
{
  if (val >= 1)
  {
    for (int i = 1 ; i <= val; i++)
    {
      BALLPEN_MOTOR_CW();
    }
  }
}
void DISPENSE_INDEX(int val)
{
  if (val >= 1)
  {
    for (int i = 1 ; i <= val; i++)
    {
      INDEX_MOTOR_CW();
    }
  }
}
void SHORT_MOTOR_CW()
{
  setServoAngle(Servo_Short_01, 180);
  setServoAngle(Servo_Short_02, 0);
  delay(1600);

  Quantity_Short--;
  SHORT_MOTOR_STOPS();

  Available_Short--;
  writeUnsignedIntIntoEEPROM(1,  Available_Short);
  delay(20);
  Available_Short = readUnsignedIntFromEEPROM(1);

  if (SHORT_NOTIF == false && Available_Short == 0)
  {
    SMS_NOTIFICATION_SHORT();
    SHORT_NOTIF = true;
  }

  if (Quantity_Short == 0)
  {
    RESET_VARIABLES();
  }
  delay(1500);
}

void LONG_MOTOR_CW()
{
  setServoAngle(Servo_Long_01, 180);
  setServoAngle(Servo_Long_02, 0);
  delay(1600);

  Quantity_Long--;
  LONG_MOTOR_STOPS();

  Available_Long--;
  writeUnsignedIntIntoEEPROM(5,  Available_Long);
  delay(20);
  Available_Long = readUnsignedIntFromEEPROM(5);

  if (LONG_NOTIF == false && Available_Long == 0)
  {
    SMS_NOTIFICATION_LONG();
    SHORT_NOTIF = true;
  }

  if (Quantity_Long == 0)
  {
    RESET_VARIABLES();
  }
  delay(1500);
}

void BALLPEN_MOTOR_CW()
{
  setServoAngle(Servo_Ballpen, 180);
  delay(1600);

  Quantity_Ballpen--;
  BALLPEN_MOTOR_STOPS();

  Available_Ballpen--;
  writeUnsignedIntIntoEEPROM(10,  Available_Ballpen);
  delay(20);
  Available_Ballpen = readUnsignedIntFromEEPROM(10);

  if (BALLPEN_NOTIF == false && Available_Ballpen == 0)
  {
    SMS_NOTIFICATION_BALLPEN();
    BALLPEN_NOTIF = true;
  }

  if (Quantity_Ballpen == 0)
  {
    RESET_VARIABLES();
  }
  delay(1500);
}

void INDEX_MOTOR_CW()
{
  setServoAngle(Servo_Index, 180);
  delay(1600);

  Quantity_Index--;
  INDEX_MOTOR_STOPS();

  Available_Index--;
  writeUnsignedIntIntoEEPROM(15,  Available_Index);
  delay(20);
  Available_Index = readUnsignedIntFromEEPROM(15);

  if (INDEX_NOTIF == false && Available_Index == 0)
  {
    SMS_NOTIFICATION_INDEX();
    INDEX_NOTIF = true;
  }

  if (Quantity_Index == 0)
  {
    RESET_VARIABLES();
  }
  delay(1500);
}
void SHORT_MOTOR_STOPS()
{
  setServoAngle(Servo_Short_01, 90);
  setServoAngle(Servo_Short_02, 90);
}

void LONG_MOTOR_STOPS()
{
  setServoAngle(Servo_Long_01, 90);
  setServoAngle(Servo_Long_02, 90);
}

void BALLPEN_MOTOR_STOPS()
{
  setServoAngle(Servo_Ballpen, 90);
}
void INDEX_MOTOR_STOPS()
{
  setServoAngle(Servo_Index, 90);
}
