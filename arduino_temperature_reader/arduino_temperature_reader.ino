// ARDUINO TEMPERATURE READER //////////////////////////

#include <DS3231.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>


Time now;
DS3231  rtc(SDA, SCL);

#define ONE_WIRE_BUS_PIN 5
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);

// First sensor
DeviceAddress Probe01 = { 0x28, 0xFF, 0xD5, 0xE6, 0x86, 0x16, 0x05, 0x4E }; 
// Second sensor
DeviceAddress Probe02 = { 0x28, 0xFF, 0xB7, 0xE7, 0x86, 0x16, 0x05, 0x53 }; 
// Third sensor
DeviceAddress Probe03 = { 0x28, 0xFF, 0xF9, 0xAC, 0x8C, 0x16, 0x03, 0xDB }; 


void setup()
{
    Serial.end();
    Serial.begin(9600);
    
    // DS3231 real time clock ///////////////////////////
    rtc.begin();
    // Uncomment the following three lines to set date and time.
    //rtc.setDOW(THURSDAY);        // Set the day of the week.
    //rtc.setTime(21, 40, 15);      // Set time HH MM SS (24hr format).
    //rtc.setDate(8, 12, 2017);   // Set date DD MM YYYY.
    now = rtc.getTime();
    
    // DS18B20 One-Wire Sensors /////////////////////////
    sensors.begin();
    sensors.setResolution(Probe01, 10);
    sensors.setResolution(Probe02, 10);
    sensors.setResolution(Probe03, 10);
    //Serial.print("Sensor1 Resolution: ");
    //Serial.println(sensors.getResolution(Probe01), DEC);
    //sensors.setResolution(Probe02, 10);
    //Serial.print("Sensor2 Resolution: ");
    //Serial.println(sensors.getResolution(Probe02), DEC);
    //sensors.setResolution(Probe03, 10);
    //Serial.print("Sensor2 Resolution: ");
    //Serial.println(sensors.getResolution(Probe03), DEC);
}


void loop()
{    
    
    now = rtc.getTime();
    sensors.requestTemperatures();
    Serial.print(now.year);
    String month_var = "";
    int m = now.mon;
    if(m < 10) { month_var += '0'; }
    month_var += m;
    Serial.print(month_var);
    String date_var = "";
    int d = now.date + 1;
    if(d < 10) { date_var += '0'; }
    date_var += d;
    Serial.print(date_var);
    Serial.print(",");
    Serial.print(rtc.getTimeStr());
    Serial.print(",");
    float s1 = sensors.getTempFByIndex(0);
    if (s1 == -127.00) {
        Serial.print("Error");
    } else {
    Serial.print(s1);
    }
    Serial.print(",");
    float s2 = sensors.getTempFByIndex(0);
    if (s2 == -127.00) {
        Serial.print("Error");
    } else {
    Serial.print(s2);
    }
    Serial.print(",");
    float s3 = sensors.getTempFByIndex(0);
    if (s3 == -127.00) {
        Serial.print("Error");
    } else {
    Serial.print(s3);
    }
    Serial.println(" ");
    delay(1000);
}
