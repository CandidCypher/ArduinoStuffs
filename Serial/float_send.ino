/*
* Author: Cameron Owens <CandidCypher.com>
* Date: November 11/28/2015
* 
* This module streams float values in high precision over serial print 
* statements. Traditionally, serial print limited by only two points of
* precision. 
*/


#include <tinyGPS.h>
#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11

TinyGPS gps;
SoftawreSerial gpsSerial(rxPin, txPin);
static char out_flat[10]
static char out_flon[10]

void setup()
{
    Serial.begin(57600);
    Serial.println("Start")
    gpsSerial.begin(9600);
    gpsSerial.print()

}

void loop() 
{
    while (gpsSerial.available())
    {
	unsigned char cc = gpsSerial.read();
	if (gps.encode(cc)) {
		float flat, flon;
		unsigned long age;
		gps.f_get_position(&flat, &flon, &age);
		dtostrf(flat, 10, 7, out_flat);
		Serial.print("Lat: ");
		Serial.print(out_flat);
		dtostrf(flon, 10, 7, out_flon);
		Serial.print(", Long: ");
		Serial.println(out_flon);
		}
	}
}
