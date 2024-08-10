#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>
#include <Nextion.h>
#include <EEPROM.h>
#include "HX711.h"
#define DOUT 10
#define SCK 11

HX711 scale(DOUT, SCK);

float weight;
float calibration_factor = 203640;  // for me this value works just perfect 419640

#define RST_PIN 49
#define SS_PIN 53
MFRC522 mfrc522_01(SS_PIN, RST_PIN);
MFRC522 mfrc522_02(SS_PIN, RST_PIN);
String User_Card, Prev_User, Display_User_Card;

#define SERVO_FREQ 60  // Analog servos run at ~60 Hz updates
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 150  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600  // This is the 'maximum' pulse length count (out of 4096)

uint8_t Servo_Loadcell = 0;
uint8_t Servo_Entrance = 1;
uint8_t Servo_Accepted = 2;

uint8_t Servo_Short_01 = 3;
uint8_t Servo_Short_02 = 4;
uint8_t Servo_Long_01 = 5;
uint8_t Servo_Long_02 = 6;
uint8_t Servo_Ballpen = 7;
uint8_t Servo_Index = 8;

SoftwareSerial Arduino_Serial(A8, A9);
bool BIN_NOTIF = false;
bool SHORT_NOTIF = false;
bool LONG_NOTIF = false;
bool BALLPEN_NOTIF = false;
bool INDEX_NOTIF = false;

//Dispensing 
// bool Done_Insert = false;
// bool Done_Short = false;
// bool Done_Long = false;
// bool Done_Ballpen = false;

//SoftwareSerial SMS(A11, A10);

char c;
String dataIn;

String myInts[9];
int incomingByte = 0;
String Data = "";
int until = 4;
int arrayIndex = 0;

int User_Points;
int Validation;

unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 10000;       // interval at which to blink (milliseconds)

unsigned long previousMillis_02 = 0;  // will store last time LED was updated
const long interval_02 = 1000;

#define INDUCTIVE_SENSOR 2
#define TRIG_BOTTLE 3
#define ECHO_BOTTLE 4
#define TRIG_BIN 5
#define ECHO_BIN 6
#define SIGNAL_ARDUINO 7
#define SIGNAL_ACCEPTED 8
#define SIGNAL_REJECTED 9

#define BTN_SHORT 44
#define BTN_LONG 45
#define BTN_BALLPEN 46
#define BTN_INDEX 47

bool Start_Detect = false;
int undetected = 0;
volatile int pulses_bottles;

int Detect_Bottle, Detect_Duration;
int Bin_Bottle, Bin_Duration;

bool Start_Display = false;
bool Page2_Display = false;
bool Page3_Display = false;
bool Page4_Display = false;
bool Page5_Display = false;
bool Page6_Display = false;
bool Page7_Display = false;
bool Page8_Display = false;
bool Page10_Display = false;
bool Dispense_Display = false;

int Short_Paper_Points = 15;
int Long_Paper_Points = 25;
int Ballpen_Points = 15;
int Index_Points = 15;

int Total_Points_Required;

bool Insert = false;
bool Reward = false;
bool Select_Reward = false;

bool Short = false;
bool Long = false;
bool Ballpen = false;
bool Index = false;

bool Dispense_Short = false;
bool Dispense_Long = false;
bool Dispense_Ballpen = false;
bool Dispense_Index = false;

int Quantity_Short = 0;
int Available_Short = 0;
int Quantity_Long = 0;
int Available_Long = 0;
int Quantity_Ballpen = 0;
int Available_Ballpen = 0;
int Quantity_Index = 0;
int Available_Index = 0;

bool Back_Page2 = false;
bool Back_Page3 = false;
bool Back_Page4 = false;
bool Back_Page5 = false;
bool Back_Page6 = false;
bool Back_Page7 = false;
bool Back_Page8 = false;
bool Back_Page10 = false;

NexButton bInsert = NexButton(2, 1, "bInsert");  // Button added
NexButton bReward = NexButton(2, 3, "bReward");  // Button added

NexButton bRedeem = NexButton(10, 1, "bRedeem");  // Button added

NexButton bShort = NexButton(4, 1, "bShort");      // Button added
NexButton bLong = NexButton(4, 2, "bLong");        // Button added
NexButton bBallpen = NexButton(4, 3, "bBallpen");  // Button added
NexButton bIndex = NexButton(4, 4, "bIndex");      // Button added

NexButton AddShort = NexButton(5, 6, "AddShort");    // Button added
NexButton SubShort = NexButton(5, 7, "SubShort");    // Button added
NexButton DoneShort = NexButton(5, 8, "DoneShort");  // Button added

NexButton AddLong = NexButton(6, 3, "AddLong");    // Button added
NexButton SubLong = NexButton(6, 4, "SubLong");    // Button added
NexButton DoneLong = NexButton(6, 5, "DoneLong");  // Button added

NexButton AddPen = NexButton(7, 3, "AddPen");    // Button added
NexButton SubPen = NexButton(7, 4, "SubPen");    // Button added
NexButton DonePen = NexButton(7, 5, "DonePen");  // Button added

NexButton AddIndex = NexButton(8, 3, "AddIndex");    // Button added
NexButton SubIndex = NexButton(8, 4, "SubIndex");    // Button added
NexButton DoneIndex = NexButton(8, 5, "DoneIndex");  // Button added

NexButton bPage2 = NexButton(2, 2, "bPage2");     // Button added
NexButton bPage3 = NexButton(3, 3, "bPage3");     // Button added
NexButton bPage4 = NexButton(4, 5, "bPage4");     // Button added
NexButton bPage5 = NexButton(5, 1, "bPage5");     // Button added
NexButton bPage6 = NexButton(6, 1, "bPage6");     // Button added
NexButton bPage7 = NexButton(7, 1, "bPage7");     // Button added
NexButton bPage8 = NexButton(8, 1, "bPage8");     // Button added
NexButton bPage10 = NexButton(10, 2, "bPage10");  // Button added

NexButton bDone = NexButton(3, 2, "bDone");  // Button added

NexTouch *nex_listen_list[] = {
  &bInsert, &bReward, &bRedeem, &bShort, &AddShort, &SubShort, &DoneShort,
  &bLong, &AddLong, &SubLong, &DoneLong, &bBallpen, &AddPen, &SubPen, &DonePen,
  &bIndex, &AddIndex, &SubIndex, &DoneIndex, &bPage2, &bPage3, &bPage4, &bPage5,
  &bPage6, &bPage7, &bPage8, &bPage10, &bDone,
  NULL
};

void Select_Insert(void *ptr)  // Release event for button b1
{
  if (Start_Display == true) {
    Insert = true;
  }
}

void Select_Rewards(void *ptr)  // Release event for button b1
{
  if (Start_Display == true) {
    Reward = true;
  }
}

void Button_Redeem(void *ptr)  // Release event for button b1
{
  if (Reward == true) {
    if (User_Points != 0) {
      Select_Reward = true;
    } else {
      Serial.print("txtErrorP10.txt=");     // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("Insufficient Points");  // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      delay(1500);
      Serial.print("txtErrorP10.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");                // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("");                  // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");                // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);                // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
    }
  }
}

void Short_Paper_Reward(void *ptr)  // Release event for button b1
{
  Short = true;
}

void Long_Paper_Reward(void *ptr)  // Release event for button b1
{
  Long = true;
}

void Ballpen_Reward(void *ptr)  // Release event for button b1
{
  Ballpen = true;
}

void Index_Card_Reward(void *ptr)  // Release event for button b1
{
  Index = true;
}

//--------------------------------------- SHORT PAPER BUTTON ---------------------------------------//
void Add_Short(void *ptr)  // Release event for button b1
{
  Available_Short = readUnsignedIntFromEEPROM(1);

  if (Quantity_Short < Available_Short) {
    Quantity_Short = Quantity_Short + 1;  // Add 1 to the current value of the counter
    Serial.print("IShort.val=");          // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(Quantity_Short);         // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

void Substract_Short(void *ptr)  // Release event for button b1
{
  if (Quantity_Short > 0) {
    Quantity_Short = Quantity_Short - 1;  // Add 1 to the current value of the counter
    Serial.print("IShort.val=");          // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(Quantity_Short);         // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

void Done_Short(void *ptr) {
  Available_Short = readUnsignedIntFromEEPROM(1);

  if (Quantity_Short == 0) {
    Serial.print("txtErrorP5.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Input Quantity");   // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(1500);
    Serial.print("txtErrorP5.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  } else if (Available_Short >= Quantity_Short) {
    if (User_Points >= Total_Points_Required) {
      User_Points = User_Points - Total_Points_Required;
      delay(100);
      SERIAL_SEND_DISPENSE();
      delay(100);
      Dispense_Short = true;
    } else {
      Serial.print("txtErrorP5.txt=");      // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("Insufficient Points");  // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.print("txtErrorP5.txt=");      // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("Insufficient Points");  // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      delay(1500);
      Serial.print("txtErrorP5.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
    }
  } else {
    Serial.print("txtErrorP5.txt=");     // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");                  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Insufficient Paper");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");                  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);                  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(1500);
    Serial.print("txtErrorP5.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

//--------------------------------------- LONG PAPER BUTTON ---------------------------------------//
void Add_Long(void *ptr)  // Release event for button b1
{
  Available_Long = readUnsignedIntFromEEPROM(5);

  if (Quantity_Long < Available_Long) {
    Quantity_Long = Quantity_Long + 1;  // Add 1 to the current value of the counter
    Serial.print("ILong.val=");         // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(Quantity_Long);        // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);                 // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

void Substract_Long(void *ptr)  // Release event for button b1
{
  if (Quantity_Long > 0) {
    Quantity_Long = Quantity_Long - 1;  // Add 1 to the current value of the counter
    Serial.print("ILong.val=");         // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(Quantity_Long);        // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);                 // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

void Done_Long(void *ptr) {
  Available_Long = readUnsignedIntFromEEPROM(5);

  if (Quantity_Long == 0) {
    Serial.print("txtErrorP6.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Input Quantity");   // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(1500);
    Serial.print("txtErrorP6.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  } else if (Available_Long >= Quantity_Long) {
    if (User_Points >= Total_Points_Required) {
      User_Points = User_Points - Total_Points_Required;
      delay(100);
      SERIAL_SEND_DISPENSE();
      delay(100);
      Dispense_Long = true;
    } else {
      Serial.print("txtErrorP6.txt=");      // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("Insufficient Points");  // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.print("txtErrorP6.txt=");      // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("Insufficient Points");  // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      delay(1500);
      Serial.print("txtErrorP6.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
    }
  } else {
    Serial.print("txtErrorP6.txt=");     // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");                  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Insufficient Paper");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");                  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);                  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(1500);
    Serial.print("txtErrorP6.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

//--------------------------------------- BALLPEN BUTTON ---------------------------------------//
void Add_Ballpen(void *ptr)  // Release event for button b1
{
  Available_Ballpen = readUnsignedIntFromEEPROM(10);

  if (Quantity_Ballpen < Available_Ballpen) {
    Quantity_Ballpen = Quantity_Ballpen + 1;  // Add 1 to the current value of the counter
    Serial.print("IPen.val=");                // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(Quantity_Ballpen);           // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);                       // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

void Substract_Ballpen(void *ptr)  // Release event for button b1
{
  if (Quantity_Ballpen > 0) {
    Quantity_Ballpen = Quantity_Ballpen - 1;  // Add 1 to the current value of the counter
    Serial.print("IPen.val=");                // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(Quantity_Ballpen);           // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);                       // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

void Done_Ballpen(void *ptr) {
  Available_Ballpen = readUnsignedIntFromEEPROM(10);

  if (Quantity_Ballpen == 0) {
    Serial.print("txtErrorP7.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Input Quantity");   // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(1500);
    Serial.print("txtErrorP7.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  } else if (Available_Ballpen >= Quantity_Ballpen) {
    if (User_Points >= Total_Points_Required) {
      User_Points = User_Points - Total_Points_Required;
      delay(100);
      SERIAL_SEND_DISPENSE();
      delay(100);
      Dispense_Ballpen = true;
    } else {
      Serial.print("txtErrorP7.txt=");      // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("Insufficient Points");  // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.print("txtErrorP7.txt=");      // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("Insufficient Points");  // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      delay(1500);
      Serial.print("txtErrorP7.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
    }
  } else {
    Serial.print("txtErrorP7.txt=");       // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");                    // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Insufficient Ballpen");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");                    // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);                    // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(1500);
    Serial.print("txtErrorP7.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}
//--------------------------------------- INDEX CARD BUTTON ---------------------------------------//
void Add_Index(void *ptr)  // Release event for button b1
{
  Available_Index = readUnsignedIntFromEEPROM(15);

  if (Quantity_Index < Available_Index) {
    Quantity_Index = Quantity_Index + 1;  // Add 1 to the current value of the counter
    Serial.print("IIndex.val=");          // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(Quantity_Index);         // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

void Substract_Index(void *ptr)  // Release event for button b1
{
  if (Quantity_Index > 0) {
    Quantity_Index = Quantity_Index - 1;  // Add 1 to the current value of the counter
    Serial.print("IIndex.val=");          // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(Quantity_Index);         // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

void Done_Index(void *ptr) {
  Available_Index = readUnsignedIntFromEEPROM(15);

  if (Quantity_Index == 0) {
    Serial.print("txtErrorP8.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Input Quantity");   // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(1500);
    Serial.print("txtErrorP8.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  } else if (Available_Index >= Quantity_Index) {
    if (User_Points >= Total_Points_Required) {
      User_Points = User_Points - Total_Points_Required;
      delay(100);
      SERIAL_SEND_DISPENSE();
      delay(100);
      Dispense_Index = true;
    } else {
      Serial.print("txtErrorP8.txt=");      // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("Insufficient Points");  // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.print("txtErrorP8.txt=");      // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("Insufficient Points");  // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      delay(1500);
      Serial.print("txtErrorP8.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
      Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
      Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
      Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
    }
  } else {
    Serial.print("txtErrorP8.txt=");    // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");                 // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Insufficient Card");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");                 // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);                 // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(1500);
    Serial.print("txtErrorP8.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

//---------------------------------------------- BACK BUTTONS ----------------------------------------------//
void Back_Page_02(void *ptr)  // Release event for button b1
{
  Back_Page2 = true;
  Page2_Display = false;
}

void Back_Page_03(void *ptr)  // Release event for button b1
{
  Back_Page3 = true;
  Page3_Display = false;
  setServoAngle(Servo_Entrance, 0);
}

void Back_Page_04(void *ptr)  // Release event for button b1
{
  Back_Page4 = true;
  Back_Page10 = false;
}

void Back_Page_05(void *ptr)  // Release event for button b1
{
  Back_Page5 = true;
}

void Back_Page_06(void *ptr)  // Release event for button b1
{
  Back_Page6 = true;
}

void Back_Page_07(void *ptr)  // Release event for button b1
{
  Back_Page7 = true;
}

void Back_Page_08(void *ptr)  // Release event for button b1
{
  Back_Page8 = true;
}

void Back_Page_10(void *ptr)  // Release event for button b1
{
  Back_Page10 = true;
  Page10_Display = false;
}

//------------------------------------------------ DONE INSERT --------------------------------------------------------//
void Done_Insert(void *ptr)  // Release event for button b1
{
  if (pulses_bottles != 0) {
    SERIAL_DONE_INSERT();
  } else {
    Serial.print("txtErrorP3.txt=");       // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");                    // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Please Insert Bottle");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");                    // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);                    // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.print("txtErrorP3.txt=");       // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");                    // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Please Insert Bottle");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");                    // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);                    // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(1500);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
  }
}

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  Arduino_Serial.begin(9600);
  SPI.begin();
  mfrc522_01.PCD_Init();
  pinMode(SIGNAL_ARDUINO, OUTPUT);
  pinMode(SIGNAL_ACCEPTED, INPUT_PULLUP);
  pinMode(SIGNAL_REJECTED, INPUT_PULLUP);
  pinMode(INDUCTIVE_SENSOR, INPUT_PULLUP);
  pinMode(BTN_SHORT, INPUT_PULLUP);
  pinMode(BTN_LONG, INPUT_PULLUP);
  pinMode(BTN_BALLPEN, INPUT_PULLUP);
  pinMode(BTN_INDEX, INPUT_PULLUP);
  pinMode(TRIG_BOTTLE, OUTPUT);
  pinMode(ECHO_BOTTLE, INPUT);
  pinMode(TRIG_BIN, OUTPUT);
  pinMode(ECHO_BIN, INPUT);
  digitalWrite(SIGNAL_ARDUINO, HIGH);

  bReward.attachPush(Select_Rewards);
  bInsert.attachPush(Select_Insert);
  bRedeem.attachPush(Button_Redeem);

  bShort.attachPush(Short_Paper_Reward);
  AddShort.attachPush(Add_Short);
  SubShort.attachPush(Substract_Short);
  DoneShort.attachPush(Done_Short);

  bLong.attachPush(Long_Paper_Reward);
  AddLong.attachPush(Add_Long);
  SubLong.attachPush(Substract_Long);
  DoneLong.attachPush(Done_Long);

  bBallpen.attachPush(Ballpen_Reward);
  AddPen.attachPush(Add_Ballpen);
  SubPen.attachPush(Substract_Ballpen);
  DonePen.attachPush(Done_Ballpen);

  bIndex.attachPush(Index_Card_Reward);
  AddIndex.attachPush(Add_Index);
  SubIndex.attachPush(Substract_Index);
  DoneIndex.attachPush(Done_Index);

  bPage2.attachPush(Back_Page_02);
  bPage3.attachPush(Back_Page_03);
  bPage4.attachPush(Back_Page_04);
  bPage5.attachPush(Back_Page_05);
  bPage6.attachPush(Back_Page_06);
  bPage7.attachPush(Back_Page_07);
  bPage8.attachPush(Back_Page_08);
  bPage10.attachPush(Back_Page_10);

  bDone.attachPush(Done_Insert);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  scale.set_scale();
  scale.tare();                             //Reset the scale to 0
  long zero_factor = scale.read_average();  //Get a baseline reading
  Serial.print("Zero factor: ");            //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~60 Hz updates

  setServoAngle(Servo_Loadcell, 200);
  setServoAngle(Servo_Entrance, 0);
  setServoAngle(Servo_Accepted, 90);

  setServoAngle(Servo_Short_01, 90);
  setServoAngle(Servo_Short_02, 90);
  setServoAngle(Servo_Long_01, 90);
  setServoAngle(Servo_Long_02, 90);
  setServoAngle(Servo_Ballpen, 90);
  setServoAngle(Servo_Index, 90);

  Serial3.println("AT\r\n");  // AT Command to receive a live SMS
  delay(1000);
  Serial3.print("AT+CMGF=1\r\n");  // Select SMS Message Format (see SMS AT Commands Reference)
  delay(1000);

  delay(1000);
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
}

void setServoAngle(uint8_t n, uint8_t angle) {
  uint16_t pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(n, 0, pulse);
}

void writeUnsignedIntIntoEEPROM(int address, unsigned int number) {
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

unsigned int readUnsignedIntFromEEPROM(int address) {
  return (EEPROM.read(address) << 8) + EEPROM.read(address + 1);
}

void LOADCELL_VERIFICATION() {
  scale.set_scale(calibration_factor);  //Adjust to this calibration factor
  Serial.print("Reading: ");
  weight = scale.get_units(5);
  Serial.print("Kilogram:");
  Serial.print(weight);
  Serial.print(" Kg");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if ((weight <= 0.50) && (Detect_Bottle <= 6) && (Insert == true)) {
    VERIFICATION_PROCESS();
  }

  else if ((weight >= 0.50) && (Detect_Bottle <= 6) && (Insert == true)) {
    setServoAngle(Servo_Entrance, 60);
    Serial.print("txtErrorP3.txt=");       // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");                    // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Heavy Item Detected!");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");                    // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);                    // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("txtErrorP3.txt=");       // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");                    // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Heavy Item Detected!");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");                    // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);                    // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);

    delay(1500);
    Serial.print("txtErrorP3.txt=");      // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Please Remove Item!");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("txtErrorP3.txt=");      // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Please Remove Item!");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");                   // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);                   // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);

    delay(6000);

    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  } else {
    // setServoAngle(Servo_Entrance, 0);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
    delay(20);
    Serial.print("txtErrorP3.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("");                 // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");               // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);               // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
}

void loop() {

  while (Arduino_Serial.available() > 0) {
    c = Arduino_Serial.read();

    if (c == '\n') {
      break;
    } else {
      dataIn += c;
    }
  }
  if (c == '\n') {
    Serial.print("dataIn:");
    Serial.println(dataIn);

    for (int i = 0; i < dataIn.length(); i++) {
      if (i == 0 || i % 4 == 0) {
        Data = dataIn.substring(i, until);
        myInts[arrayIndex] = Data;
        until = until + 4;
        arrayIndex++;
      }
    }
    Validation = myInts[0].toInt();
    User_Points = myInts[1].toInt();
    Serial.println(Validation);
    Serial.println(User_Points);

    c = 0;
    dataIn = "";
    Data = "";
    arrayIndex = 0;
    until = 4;
  } else {
    nexLoop(nex_listen_list);
    RFID_READER_CARD();
    RFID_USER_VERIFICATION();
    INSERT_BOTTLE();
    REDEEM_REWARDS();
    START_DISPENSE();
    RESET_REWARD();
  }
}

void START_DISPENSE() {
  //------------------------ SHORT-DISPENSE ------------------------//
  if (Short == true && Dispense_Short == true) {
    if (Dispense_Display == false) {
      Serial.print("page 9");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Serial.print("page 9");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
    }
    DISPENSE_SHORT(Quantity_Short);
  }

  //------------------------ LONG-DISPENSE ------------------------//
  if (Long == true && Dispense_Long == true) {
    if (Dispense_Display == false) {
      Serial.print("page 9");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Serial.print("page 9");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
    }
    DISPENSE_LONG(Quantity_Long);
  }

  //------------------------ BALLPEN-DISPENSE ------------------------//
  if (Ballpen == true && Dispense_Ballpen == true) {
    if (Dispense_Display == false) {
      Serial.print("page 9");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
      Serial.print("page 9");
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      delay(20);
    }
    DISPENSE_BALLPEN(Quantity_Ballpen);
  }

  //------------------------ INDEX-DISPENSE ------------------------//
  if (Index == true && Dispense_Index == true) {
    if (Dispense_Display == false) {
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
      Dispense_Display = true;
    }
    DISPENSE_INDEX(Quantity_Index);
  }
}
