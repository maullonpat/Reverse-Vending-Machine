void RFID_READER_CARD()
{
  if (Start_Display == false)
  {
    if ( ! mfrc522_01.PICC_IsNewCardPresent())
    {
      return;
    }
    if ( ! mfrc522_01.PICC_ReadCardSerial())
    {
      return;
    }

    String content1 = "";
    String content2 = "";
    delay(20);
    for (byte i = 0; i < mfrc522_01.uid.size; i++)
    {
      content1.concat(String(mfrc522_01.uid.uidByte[i] < 0x10 ? "0" : ""));
      content1.concat(String(mfrc522_01.uid.uidByte[i], HEX));
      content2.concat(String(mfrc522_01.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content2.concat(String(mfrc522_01.uid.uidByte[i], HEX));
    }

    content1.toUpperCase();
    content2.toUpperCase();
    User_Card = content1;
    Display_User_Card = content2.substring(1);
    Serial.println(User_Card);
    Serial.println(Display_User_Card);
    delay(20);

    if (Prev_User != User_Card)
    {
      SERIAL_SEND_NODEMCU_EXPRESS();
      Prev_User = User_Card;
    }
  }
}

void RFID_USER_VERIFICATION()
{
  if (Validation == 1)
  {
    nexLoop(nex_listen_list);
    if (Page2_Display == false && Start_Display == false)
    {
      Start_Display = true;
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
      Page2_Display = true;
    }

    if (Back_Page2 == true)
    {
      Start_Display = false;
      User_Card = "";
      Prev_User = "";
      Display_User_Card = "";
      User_Points = 0;
      Validation = 0;
      Serial.print("page 1");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Serial.print("page 1");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Validation = 0;
      Back_Page2 = false;
    }
  }
  else if (Validation == 2)
  {
    Serial.print("page 11");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("page 11");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    delay(2000);
    RESET_VARIABLES();
  }
}
