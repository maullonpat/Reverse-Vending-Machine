#include <Wire.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

char c;
String dataIn;

SoftwareSerial Nodemcu_Serial(D1, D2);

const char* ssid = "iMan"; //--> Your wifi name or SSID.
const char* password = "sheeshables"; //--> Your wifi password.

// #define SIGNAL_MEGA D0 //--> Defines an LED Pin. D8 = GPIO15
// #define SIGNAL_BIN D3 //--> Defines an LED Pin. D8 = GPIO15

// unsigned long previousMillis = 0;        // will store last time LED was updated
// const long interval = 1000;           // interval at which to blink (milliseconds)
// int timer_count = 0;

// String prev, current;
// String val = "";

String myInts[25];
int incomingByte = 0;
String test2 = "";
int until = 8;
int arrayIndex = 0;

String ID;
int Points;
int Status;
String User_Points;
bool send_stopper = false;


//----------------------------------------Web Server address / IPv4
// If using IPv4, press Windows key + R then type cmd, then type ipconfig (If using Windows OS).
const char *urlRegister = "http://172.20.10.2/rvm_ecotech/Register.php?"; 
const char *urlValidate = "http://172.20.10.2/rvm_ecotech/ValidateCard.php?";
const char *urlPoints = "http://172.20.10.2/rvm_ecotech/GetPoints.php?";
const char *urlSavePoints = "http://172.20.10.2/rvm_ecotech/SavePoints.php?";
const char *urlSaveBottles = "http://172.20.10.2/rvm_ecotech/SaveBottles.php?";
//----------------------------------------

boolean connectedFlag = false;
String GetAddress, LinkGet, getData;
int httpCodeGet;
String payloadGet;

//WiFiClientSecure client;
WiFiClient client;

void ICACHE_RAM_ATTR loop();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Nodemcu_Serial.begin(9600);
  ESP.wdtDisable();
  ESP.wdtEnable(WDTO_8S);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
  delay(1000);

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    //  digitalWrite(ON_Board_LED, LOW);
    delay(250);
    //  digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  connectedFlag = true;
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------
}
void loop() {
  // put your main code here, to run repeatedly:

  while ( Nodemcu_Serial.available() > 0)
  {
    c =  Nodemcu_Serial.read();
    if (c == '\n')
    {
      break;
    }
    else
    {
      dataIn += c;
    }
  }
  if (c == '\n')
  {
    Serial.print("DataIn:");
    Serial.println(dataIn);
    for (int i = 0; i < dataIn.length(); i++) {
      if (i == 0 || i % 8 == 0) {
        test2 = dataIn.substring(i, until);
        myInts[arrayIndex] = test2;
        until = until + 8;
        arrayIndex++;
      }
    }

    ID = myInts[0];
    Points = myInts[1].toInt();
    Status = myInts[2].toInt();
    Serial.print("ID:");
    Serial.println(ID);
    Serial.print("Points:");
    Serial.println(Points);
    delay(20);

    Validate_Card(ID);
    c = 0;
    dataIn = "";
    arrayIndex = 0;
    test2 = "";
    until = 8;
  }
}

void Register_Card(String RFID, int Points)
{
  if (connectedFlag)
  {
    HTTPClient httpClient;
    String data = "RFID=" + RFID + "&Points=" + Points;

    httpClient.begin(urlRegister);
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = httpClient.POST(data);
    payloadGet = httpClient.getString();

    if (payloadGet == "\"Successful\"")
    {
      Serial.println("Successful Register!");
      Nodemcu_Serial.print(toString4(String(2)) + toString4(String(0)) + " \n");
    }

    httpClient.end();
    Serial.println(httpCode);
    Serial.println(payloadGet);
  }
}

void Validate_Card(String RFID)
{
  if (connectedFlag)
  {
    HTTPClient httpClient;
    String data = "RFID=" + RFID;

    httpClient.begin(urlValidate);
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = httpClient.POST(data);
    payloadGet = httpClient.getString();

    if (payloadGet == "\"Available\"")
    {
      Register_Card(ID, 0);
    }
    else if (payloadGet == "\"Used\"")
    {
      if (Status == 1)
      {
        Get_Points(ID);
      }
      else if (Status == 2)
      {
        Save_Points(ID, Points);
      }
      else if (Status == 3)
      {
        Save_Bottles(ID, Points);
      }
    }

    httpClient.end();
    Serial.println(httpCode);
    Serial.println(payloadGet);
  }
}

void Get_Points(String RFID)
{
  if (connectedFlag)
  {
    send_stopper = false;
    Serial.println("Get Points");
    HTTPClient httpClient;
    String data = "RFID=" + RFID;

    httpClient.begin(urlPoints);
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = httpClient.POST(data);
    payloadGet = httpClient.getString();
    User_Points = removeDoubleQuotes(payloadGet);
    delay(500);
    Nodemcu_Serial.print(toString4(String(1)) + toString4(User_Points) + " \n");
    Serial.println(toString4(String(1)) + toString4(User_Points));
    delay(500);
    httpClient.end();
    Serial.println(httpCode);
    Serial.println(payloadGet);
  }
}

void Save_Points(String RFID, int Points)
{
  if (connectedFlag)
  {

    Serial.println("Save Points");
    HTTPClient httpClient;
    String data = "RFID=" + RFID + "&Points=" + Points;

    httpClient.begin(urlSavePoints);
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = httpClient.POST(data);
    payloadGet = httpClient.getString();
    httpClient.end();
    Serial.println(httpCode);
    Serial.println(payloadGet);

  }
}

void Save_Bottles(String RFID, int Points)
{
  if (connectedFlag)
  {

    Serial.println("Save Points");
    HTTPClient httpClient;
    String data = "RFID=" + RFID + "&Points=" + Points;

    httpClient.begin(urlSaveBottles);
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = httpClient.POST(data);
    payloadGet = httpClient.getString();
    httpClient.end();
    Serial.println(httpCode);
    Serial.println(payloadGet);

  }
}

String removeDoubleQuotes(String inputString) {
  String result = "";
  for (int i = 0; i < inputString.length(); i++) {
    if (inputString[i] != '"') { // Exclude double quotes
      result += inputString[i];
    }
  }
  return result;
}

String toString4(String num) {
  String out;
  String raw = num;

  if (raw.length() == 1) {
    out = "000" + raw;
  }
  else if (raw.length() == 2) {
    out = "00" + raw;
  }
  else if (raw.length() == 3) {
    out = "0" + raw;
  }
  else {
    out = raw;
  }
  return out;
}
