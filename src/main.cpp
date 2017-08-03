#define DEBUG 1  //Print to Serial
#define UPDATE_INTERVAL 60000L  //Log temp in every minute
#define PRINTDEBUG(STR) \
  {  \
    if (DEBUG) Serial.println(STR); \
  }


#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

const char* ssid     = "openwrt";
const char* password = "5QYYjVSL";

#include "Arduino.h"
#include <LiquidCrystal_I2C.h>

/*
D1(Nodemcu) –> SCL(LCD)
D2(Nodemcu)–> SDA(LCD)
+ve (VU) 5V power supply –> VCC(LCD)
ground -ve  –> GND(LCD)
*/


#include <NtpClientLib.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Function to connect WiFi
void connectWifi(const char* ssid, const char* password) {
  int WiFiCounter = 0;
  // We start by connecting to a WiFi network
  PRINTDEBUG("Connecting to ");
  PRINTDEBUG(ssid);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && WiFiCounter < 30) {
    delay(1000);
    WiFiCounter++;
    PRINTDEBUG(".");
  }

  PRINTDEBUG("");
  PRINTDEBUG("WiFi connected");
  PRINTDEBUG("IP address: ");
  PRINTDEBUG(WiFi.localIP());
  NTP.begin("pool.ntp.org",1,true);
}


void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin(D2,D1);
  // initialize the LCD
	lcd.init();

	// Turn on the blacklight and print a startup message.
	lcd.backlight();
	lcd.print("Hello, world!");
  delay(2000);

  if (DEBUG) Serial.begin(115200);  //Start Serial
  connectWifi(ssid, password); // Start WiFi
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  delay(1000);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

   // wait for a second
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IP:");
  lcd.print(WiFi.localIP());
  lcd.setCursor(0,1);
  lcd.print(NTP.getTimeStr());
}