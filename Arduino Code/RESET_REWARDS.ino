void RESET_REWARD()
{
  int VAL_SHORT = digitalRead(BTN_SHORT);
  int VAL_LONG = digitalRead(BTN_LONG);
  int VAL_BALLPEN = digitalRead(BTN_BALLPEN);
  int VAL_INDEX = digitalRead(BTN_INDEX);

  // Serial.print("VAL_SHORT:");
  // Serial.println(VAL_SHORT);
  // Serial.print("VAL_LONG:");
  // Serial.println(VAL_LONG);
  // Serial.print("VAL_BALLPEN:");
  // Serial.println(VAL_BALLPEN);
  // Serial.print("VAL_INDEX:");
  // Serial.println(VAL_INDEX);
  
  if (VAL_SHORT == 0)
  {
    Available_Short = 10;
    writeUnsignedIntIntoEEPROM(1,  Available_Short);
    delay(20);
    Available_Short = readUnsignedIntFromEEPROM(1);
  }

  else if (VAL_LONG == 0)
  {
    Available_Long = 11;
    writeUnsignedIntIntoEEPROM(5,  Available_Long);
    delay(20);
    Available_Long = readUnsignedIntFromEEPROM(5);
  }

  else if (VAL_BALLPEN == 0)
  {
    Available_Ballpen = 12;
    writeUnsignedIntIntoEEPROM(10,  Available_Ballpen);
    delay(20);
    Available_Ballpen = readUnsignedIntFromEEPROM(10);
  }

  else if (VAL_INDEX == 0)
  {
    Available_Index = 11;
    writeUnsignedIntIntoEEPROM(15,  Available_Index);
    delay(20);
    Available_Index = readUnsignedIntFromEEPROM(15);
  }
}