/*
 * Rain Gauge Datalogging Code for the Wemos D1 Mini microcontroller
 * 
 * Used to log data when the rain gauge is in use outside.
 * 
 * Logs the pressure difference between the two pressure sensors and the temperature of each sensor every 15 minutes. The data is logged 
 * to a file called "datalog.txt" on the micro SD card.
 * 
 * Make sure that RST is connected to D0, so that the microcontroller will wake up after 15 minutes! 
 * However, when uploading this code, make sure that RST is disconnected from D0, because the code might not upload otherwise.
 * 
 * datalog.txt File Format 
 * [date & time] [pressure from sensor1 in Pascals] [pressure from sensor2 in Pascals] 
 * 
*/

#include <Wire.h>

/**************BMP Pressure Sensors****************/

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bme1; // I2C
Adafruit_BMP280 bme2; // I2C

double t_bmp280_1, t_bmp280_2;
double p_bmp280_1, p_bmp280_2;
boolean setupStatus = true;
double p_difference;

/*****************SD CARD READER*******************/

#include <SPI.h>
#include <SD.h>
int SD_CS = D3; //D3 for catalex 
File dataFile; //used to open/ create file to write to
String descriptor; //store labels for the data 
String dataString; // used to store temp + pressure data
String sdData;

/****************REAL TIME CLOCK********************/

#include <RtcDS1307.h>
RtcDS1307<TwoWire> Rtc(Wire);
#define countof(a) (sizeof(a) / sizeof(a[0]))
char currentTime[20];
RtcDateTime now;
uint8_t hour_12hrformat;
String AMPM;
String timeString;

/********************* LCD *************************/
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); 

/***************************************************/
  
void setup() {

  Serial.begin(115200);
  while (!Serial){
    ; // wait for serial port to connect. Needed for native USB port Only
  }

  
  /********************* BMP280 SET-UP *************************/ 
  if (!bme1.begin(0x77)) {  //SDO to 3.3V, atmospheric pressure
    Serial.println("Could not find a valid BMP280_1 sensor, check wiring!");
    while(1);
  }

  if (!bme2.begin(0x76)){ //SDO to ground, water + atmospheric pressure
    Serial.println("Could not find a valid BMP280_2 sensor, check wiring!");
    while(1);
  }

  /******************** END BMP280 SET-UP ************************/


  /***************** REAL TIME CLOCK SET-UP **********************/
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

  if (!Rtc.IsDateTimeValid()) 
  {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");

        // following line sets the RTC to the date & time this sketch was compiled
        // it will also reset the valid flag internally unless the Rtc device is
        // having an issue

        Rtc.SetDateTime(compiled);
   }

  if (!Rtc.GetIsRunning())
  {
      Serial.println("RTC was not actively running, starting now");
      Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) 
  {
      Serial.println("RTC is older than compile time!  (Updating DateTime)");
      Rtc.SetDateTime(compiled);
  }
  else if (now > compiled) 
  {
      Serial.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled) 
  {
      Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }

  // never assume the Rtc was last configured by you, so
  // just clear them to your needed state
  Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low); 

  /**************** END  REAL TIME CLOCK SET-UP ********************/

 
  /****************** SD CARD READER SET-UP ***********************/
  SPI.begin();
  pinMode(SD_CS, OUTPUT);
  //digitalWrite(SD_CS, LOW); 

  Serial.println("\nInitializing SD card...");
   while(!SD.begin(SD_CS)){
      Serial.println("Card Failure");
      Serial.println("Will check for SD card again in 5 seconds...");
      delay(5000);
    
  }
      Serial.println("Card Ready");
 
  /***************** END SD CARD READER SET-UP *********************/


  /******************** LCD SCREEN  SET-UP ************************/
  lcd.begin(16,2);
  lcd.init();
  
  /****************** END LCD SCREEN  SET-UP **********************/

}
 

void loop() {

  // BMP1 (Pressure sensor 1)
  p_bmp280_1 = bme1.readPressure();

  // BMP2 (Pressure sensor 2)
  p_bmp280_2 = bme2.readPressure();

  // RTC (Real time clock)
  if (!Rtc.IsDateTimeValid()) 
  {
      // Common Causes:
      //    1) the battery on the device is low or even missing and the power line was disconnected
      Serial.println("RTC lost confidence in the DateTime!");
  }

  now = Rtc.GetDateTime();

  // SD card 
  dataFile = SD.open("datalog.txt", FILE_WRITE);

  // Write to txt file on SD card
  if (dataFile){

    // Change time to 12 hour format
    hour_12hrformat = now.Hour();
    if (hour_12hrformat > 12){
       hour_12hrformat -= 12;
       AMPM = "PM";
    }else{
      if(hour_12hrformat == 0){ //if midnight, change hour from 0 to 12
        hour_12hrformat = 12;
      }
      AMPM = "AM"; 
    }
    
    // To print date + time using RTC
    snprintf_P(currentTime, 
            countof(currentTime),
            PSTR("%02u/%02u/%04u %02u:%02u"),
            now.Month(),
            now.Day(),
            now.Year(),
            hour_12hrformat,
            now.Minute());
            
    timeString = String(currentTime);
    timeString = timeString + AMPM;
    
    // Data written to SD card (date/time, pressure from BMP1, pressure from BMP2)
    sdData = timeString + "\t" + p_bmp280_1 + "\t" + p_bmp280_2;

    // Write data to SD card
    Serial.println(sdData);
    dataFile.println(sdData);
    dataFile.close();
  
    // Print to LCD (for testing purposes)
    /*
    lcd.setCursor(0, 0);
    lcd.print("Difference in P:");
    lcd.setCursor(0,1);
    lcd.print(dataString);
    */
     
  }
  else{
    Serial.println("Couldn't open log file");
  }

  delay(1000); //wait 1 sec
 
  ESP.deepSleep(15*60*1000000, WAKE_RF_DEFAULT); //Sleep for 15 mins

}




