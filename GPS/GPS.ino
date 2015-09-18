/*
 * GPS.ino
 * Copyright (C) 2015 cameron <cameron@Megatron-Virtual>
 *
 * Distributed under terms of the MIT license.
 */

#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(10, 11);  //RX and TX respectively (TX Not Important)
const int sentencSize = 80;

char sentence[sentenceSize];

void setup()
{
    Serial.begin(9600);
    gpsSerial.begin(9600);
}
