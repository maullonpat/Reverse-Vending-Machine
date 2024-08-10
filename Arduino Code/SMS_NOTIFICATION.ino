void SMS_NOTIFICATION_BOTTLES()
{
  Serial3.print("AT+IPR=9600\r");
  delay(500);
  Serial3.print("ATE0\r"); // Select SIM900 Message Format (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("AT+CMGF=1\r"); // Select SIM900 Message Format (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("AT+CMGS=\"+639935153199\"\r"); // Number to which you want to send the SIM900  (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("Warning! The Bin is Full.. Please Remove All the Plastic Bottles! Thank You"); // The text of the message to be sent to the receiver or the owner. (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print((char)26);// ASCII code of CTRL+Z for saying the end of SIM900 to  the module
  delay(1000);
}

void SMS_NOTIFICATION_SHORT()
{
  Serial3.print("AT+IPR=9600\r");
  delay(500);
  Serial3.print("ATE0\r"); // Select SIM900 Message Format (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("AT+CMGF=1\r"); // Select SIM900 Message Format (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("AT+CMGS=\"+639935153199\"\r"); // Number to which you want to send the SIM900  (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("Warning! Short Bond Paper Storage is Empty.. Please Refill Immediately! Thank You"); // The text of the message to be sent to the receiver or the owner. (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print((char)26);// ASCII code of CTRL+Z for saying the end of SIM900 to  the module
  delay(1000);
}

void SMS_NOTIFICATION_LONG()
{
  Serial3.print("AT+IPR=9600\r");
  delay(500);
  Serial3.print("ATE0\r"); // Select SIM900 Message Format (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("AT+CMGF=1\r"); // Select SIM900 Message Format (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("AT+CMGS=\"+639935153199\"\r"); // Number to which you want to send the SIM900  (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("Warning! Long Bond Paper Storage is Empty.. Please Refill Immediately! Thank You"); // The text of the message to be sent to the receiver or the owner. (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print((char)26);// ASCII code of CTRL+Z for saying the end of SIM900 to  the module
  delay(1000);
}

void SMS_NOTIFICATION_BALLPEN()
{
  Serial3.print("AT+IPR=9600\r");
  delay(500);
  Serial3.print("ATE0\r"); // Select SIM900 Message Format (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("AT+CMGF=1\r"); // Select SIM900 Message Format (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("AT+CMGS=\"+639935153199\"\r"); // Number to which you want to send the SIM900  (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("Warning! Ballpen Storage is Empty.. Please Refill Immediately! Thank You"); // The text of the message to be sent to the receiver or the owner. (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print((char)26);// ASCII code of CTRL+Z for saying the end of SIM900 to  the module
  delay(1000);
}

void SMS_NOTIFICATION_INDEX()
{
  Serial3.print("AT+IPR=9600\r");
  delay(500);
  Serial3.print("ATE0\r"); // Select SIM900 Message Format (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("AT+CMGF=1\r"); // Select SIM900 Message Format (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("AT+CMGS=\"+639935153199\"\r"); // Number to which you want to send the SIM900  (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print("Warning! Index Card Storage is Empty.. Please Refill Immediately! Thank You"); // The text of the message to be sent to the receiver or the owner. (see SIM900 AT Commands Reference)
  delay(500);
  Serial3.print((char)26);// ASCII code of CTRL+Z for saying the end of SIM900 to  the module
  delay(1000);
}
