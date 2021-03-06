#include <stdlib.h>
#include <SD.h>
#include "DHT.h" // git://github.com/adafruit/DHT-sensor-library.git
#include <Wire.h>
#include "RTClib.h" // git://github.com/adafruit/RTClib.git

RTC_DS1307 RTC;

/*
  Seeed SD card 3.1 datalogger
 
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10
 	 
 */

// on seeed sd card 3.1 shield cs= 10
const int chipSelect = 10;

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);
int loopCount = 0;

// set below variable to your local timezone
uint32_t utc_offset_hrs = 10;

uint32_t utc_offset_secs;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  dht.begin();

  utc_offset_secs = (utc_offset_hrs * 60) * 60;
}

void loop()
{
  // time
  DateTime now = RTC.now();

  // utc+ 10
  DateTime aest (now.unixtime() + utc_offset_secs);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("data.csv", FILE_WRITE);

  String dataString = "";

  // write the first row as col headers
  if (loopCount == 0 && dataFile.size() == 0) {
    dataString.concat("Time (UNIX)");
    dataString.concat(",");
    dataString.concat("Temperature (c)");
    dataString.concat(",");
    dataString.concat("RH (%)");
    Serial.println(dataString);
    dataFile.println(dataString);
  }

  // if the file is available, write to it:
  if (dataFile) {
    if (loopCount > 0) {
      // Reading temperature or humidity takes about 250 milliseconds!
      // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
      float h = dht.readHumidity();
      float t = dht.readTemperature();

      // convert floats to Strings    
      char humBuff[10], tempBuff[10];
      dtostrf(h,0,2,humBuff);
      dtostrf(t,0,2,tempBuff);

      // make the string
      dataString.concat(String(now.unixtime()));
      dataString.concat(",");
      dataString.concat(String(tempBuff));
      dataString.concat(",");
      dataString.concat(String(humBuff));

      // make human readable spreadsheet time
      String spreadsheet = "";
      spreadsheet.concat(aest.year());
      spreadsheet.concat("-");
      spreadsheet.concat(padDigits(aest.month()));
      spreadsheet.concat("-");
      spreadsheet.concat(padDigits(aest.day()));
      spreadsheet.concat(" ");
      spreadsheet.concat(padDigits(aest.hour()));
      spreadsheet.concat(":");
      spreadsheet.concat(padDigits(aest.minute()));
      spreadsheet.concat(":");
      spreadsheet.concat(padDigits(aest.second()));
      
      // check if returns are valid, if they are NaN (not a number) then something went wrong!
      if (isnan(t) || isnan(h)) {
        Serial.println("Failed to read from DHT");
      } 
      else {
        // write the file
        dataFile.println(dataString);
      }

      // print to the serial port too:
      	Serial.println(spreadsheet);
	Serial.println(dataString);
    }
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  }

  dataFile.close();

  // take a reading every minute..
  if (loopCount > 0) {
    delay(10000);
  }

  loopCount ++;
}

/////////////////////////
/////////////////////// functions
//////////////////////////////////

String padDigits(int input) {
  String outputStr = "";
  if (input < 10) {
    outputStr.concat("0");
  }
  outputStr.concat(input);
  return outputStr;
}
