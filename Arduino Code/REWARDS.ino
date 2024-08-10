void REDEEM_REWARDS()
{
  if (Reward == true)
  {
    nexLoop(nex_listen_list);

    if (Page10_Display == false && Reward == true)
    {
      Serial.print("page 10");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Serial.print("page 10");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(100);
      Serial.print("IDCard.txt=");
      Serial.print("\"");
      Serial.print(Display_User_Card);
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Serial.print("IDCard.txt=");
      Serial.print("\"");
      Serial.print(Display_User_Card);
      Serial.print("\"");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Serial.print("IDBal.val=");
      Serial.print(User_Points);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Serial.print("IDBal.val=");
      Serial.print(User_Points);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Page10_Display = true;
    }
    if (Back_Page10 == true)
    {
      Page10_Display = false;
      Page2_Display = false;
      Start_Display = false;
      Reward = false;
      Back_Page10 = false;
    }

    if (Page4_Display == false && Select_Reward == true)
    {
      Serial.print("page 4");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Serial.print("page 4");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Page4_Display = true;
    }

    if (Back_Page4 == true)
    {
      Page4_Display = false;
      Page10_Display = false;
      Select_Reward = false;
      Back_Page4 = false;
    }

    //---------------------------------------- SHORT-BOND-PAPER ----------------------------------------//
    if (Short == true)
    {
      // Serial.println("Short!");
      nexLoop(nex_listen_list);

      if (Page5_Display == false && Page4_Display == true)
      {
        Available_Short = readUnsignedIntFromEEPROM(1);
        Serial.print("page 5");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("PShort.val=");
        Serial.print(Short_Paper_Points);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("PShort.val=");
        Serial.print(Short_Paper_Points);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("AShort.val=");
        Serial.print(Available_Short);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("AShort.val=");
        Serial.print(Available_Short);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Page5_Display = true;
      }

      if (Quantity_Short > 0)
      {
        Total_Points_Required = Quantity_Short * Short_Paper_Points;
      }
      else
      {
        Total_Points_Required = 0;
      }

      if (Back_Page5 == true)
      {
        Page4_Display = false;
        Page5_Display = false;
        Short = false;
        Back_Page5 = false;
      }
    }


    //---------------------------------------- LONG-BOND-PAPER ----------------------------------------//
    if (Long == true)
    {
      // Serial.println("Short!");
      nexLoop(nex_listen_list);

      if (Page6_Display == false && Page4_Display == true)
      {
        Available_Long = readUnsignedIntFromEEPROM(5);
        Serial.print("page 6");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("PLong.val=");
        Serial.print(Long_Paper_Points);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("PLong.val=");
        Serial.print(Long_Paper_Points);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("ALong.val=");
        Serial.print(Available_Long);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("ALong.val=");
        Serial.print(Available_Long);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Page6_Display = true;
      }

      if (Quantity_Long > 0)
      {
        Total_Points_Required = Quantity_Long * Long_Paper_Points;
      }
      else
      {
        Total_Points_Required = 0;
      }

      if (Back_Page6 == true)
      {
        Page4_Display = false;
        Page6_Display = false;
        Long = false;
        Back_Page6 = false;
      }
    }

    //---------------------------------------- BALLPEN ----------------------------------------//
    if (Ballpen == true)
    {
      // Serial.println("Short!");
      nexLoop(nex_listen_list);

      if (Page7_Display == false && Page4_Display == true)
      {
        Available_Ballpen = readUnsignedIntFromEEPROM(10);
        Serial.print("page 7");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("PPen.val=");
        Serial.print(Ballpen_Points);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("PPen.val=");
        Serial.print(Ballpen_Points);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("APen.val=");
        Serial.print(Available_Ballpen);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("APen.val=");
        Serial.print(Available_Ballpen);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Page7_Display = true;
      }

      if (Quantity_Ballpen > 0)
      {
        Total_Points_Required = Quantity_Ballpen * Ballpen_Points;
      }
      else
      {
        Total_Points_Required = 0;
      }

      if (Back_Page7 == true)
      {
        Page4_Display = false;
        Page7_Display = false;
        Ballpen = false;
        Back_Page7 = false;
      }
    }
    //---------------------------------------- INDEX CARD ----------------------------------------//
    if (Index == true)
    {
      // Serial.println("Short!");
      nexLoop(nex_listen_list);

      if (Page8_Display == false && Page4_Display == true)
      {
        Available_Index = readUnsignedIntFromEEPROM(15);
        Serial.print("page 8");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("PIndex.val=");
        Serial.print(Index_Points);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("PIndex.val=");
        Serial.print(Index_Points);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("AIndex.val=");
        Serial.print(Available_Index);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Serial.print("AIndex.val=");
        Serial.print(Available_Index);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        delay(20);
        Page8_Display = true;
      }

      if (Quantity_Index > 0)
      {
        Total_Points_Required = Quantity_Index * Index_Points;
      }
      else
      {
        Total_Points_Required = 0;
      }

      if (Back_Page8 == true)
      {
        Page4_Display = false;
        Page8_Display = false;
        Index = false;
        Back_Page8 = false;
      }
    }
  }
}
