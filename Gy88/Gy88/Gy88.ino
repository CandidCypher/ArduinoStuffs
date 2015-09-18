/* 
 *
 * This driver/header file was based off of the good work done by "Krodal" from
 * the Arduino Universe and the people behind the FreeIMU stuff. 
 *
 * The purpose of this driver is to integrate the GY-88 10DOF sensor board into
 * a test environment for the purpose of building it into SparkControl
 *
 * The target environment for this build was the Arduino Uno which uses A5(SCL)
 * and A4(SDA)
 *
 * Author: Cameron Owens
 * Developer: CoroWare Robotic Solutions
 * Date: May 19, 2015
 *
 */

#include <Wire.h> //Library for I2C communications


//Address Spaces for Sensors on I-Two-See Bus
const int CompAddress=0x1E; //Address Space for Compass (Sensor also has 0x3D Read and 0x3C Write)
const int MPUAddress=0x68; //Address Space for IMU
const int BarAddress=0x77; //Address Space for Barometer

//Storage Space for Read Values

//Calibration Values for Barometer
int ac1, ac2, ac3, b1, b2, mb, mc, md;
float altitude;
short temperature;
short bar_Temperature;
short uncallibrated_temp;
const float p_naught = 101325; //Pressure at Sea Level (Pascals)

//Values for Compass & Accelerometer
int x, y , z;
unsigned int ac4, ac5, ac6;
long b5, pressure, x1, x2, x3, b3, b6, p;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ, MagX, MagY, MagZ;
const unsigned char OSS = 0; //Oversampling Setting

//Constants used for Calibration Filter

float Mag_DEC = 4.20; //Degrees for Austin Texas
//Tuning Constants for Kalman Filter
//#define twoKpDef(2.0f * 0.5f)
//#define twoKiDef (2.0f * 0.25f)
//#define betaDef 0.2f
//Constants used for DCM Filter
const float Kp_ROLLPITCH = 1.2f;
const float Ki_ROLLPITCH = 0.0234f;
const float Kp_Yaw = 1.75f;
const float Ki_Yaw = 0.0025f;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    
    //Start-up Compass
    Wire.beginTransmission(CompAddress);
    Wire.write(0x02); //select mode register
    Wire.write(0x00); //Continuous Measurement Mode
    Wire.endTransmission(); //  Free's I2C Lines
    
    //Start-up MPU
    Wire.beginTransmission(MPUAddress);
    Wire.write(0x6B); //Power Management Register
    Wire.write(0); //Wakes MPU-6050
    Wire.endTransmission(); //Free's I2C Lines
    
    //Start-up Barometer
    BarometerCalibration();
    delay(2000);
}



void loop()
{
    getIMUData(); //To simplify code, created a function to call for data from sensor
    getCompassData(); // ""
    pressure = bmp085GetPressure(bmp085ReadUP());
    altitude = (float)44330 * (1 - pow(((float) pressure/p_naught), 0.190295));
    
    //getBarometricData(); // ""
    Serial.print(AcX);
    Serial.print(',');
    Serial.print(AcZ);
    Serial.print(',');
    Serial.print(AcY);
    Serial.print(',');
    Serial.print(GyX);
    Serial.print(',');
    Serial.print(GyZ);
    Serial.print(',');
    Serial.print(GyY);
    Serial.print(',');
    Serial.print(x);
    Serial.print(',');
    Serial.print(y);
    Serial.print(',');
    Serial.print(z);
    Serial.print(',');
    Serial.print(temperature);
    Serial.print(':');
    Serial.println();  
  }

void getIMUData()
{
  Wire.beginTransmission(MPUAddress);
  Wire.write(0x3B); //Writes to Enable Register "Turn on Communications"
  Wire.endTransmission(false); //False message sends 'restart' message
                                //Restart communication to while we are
                                //listening

  Wire.requestFrom(MPUAddress, 14, true); // request(Address, #bytes, stop_flag)
  //High byte = Integer part, Low byte = Decimal part
  AcX = Wire.read()<<8|Wire.read(); //2 X-acceleration bytes (High and low)
  AcY = Wire.read()<<8|Wire.read(); //2 Y-acceleration bytes (High and Low)
  AcZ = Wire.read()<<8|Wire.read(); //2 Z-acceleration bytes (High and Low)
  Tmp = Wire.read()<<8|Wire.read(); //2 Temp bytes (High and Low)
  GyX = Wire.read()<<8|Wire.read(); //2 X-axis gyro bytes (High and Low)
  GyY = Wire.read()<<8|Wire.read(); //2 Y-axis gyro bytes (High and Low)
  GyZ = Wire.read()<<8|Wire.read(); //2 Z-Axis gyro bytes

  /* For mor information please refer to the data sheet:
     https://www.olimex.com/Products/Modules/Sensors/MOD-MPU6050/resources/RM-MPU-60xxA_rev_4.pdf
*/
}


void getCompassData()
{
Wire.beginTransmission(CompAddress);
Wire.write(0x03); // Write to the MSB register to start data stream
Wire.endTransmission(false); //Free up I2C communication Line

Wire.requestFrom(CompAddress, 6, true); //Request(Address, #bytes, stop_flag)

if(6<=Wire.available())
  {
  x = Wire.read()<<8|Wire.read(); //2 Bytes for X Magnetometer (High and Low)
  z = Wire.read()<<8|Wire.read(); //2 Bytes for Z Magnetometer (High and Low)
  y = Wire.read()<<8|Wire.read(); //2 Bytes for Y Magnetometer (High and Low)
  }
}


void BarometerCalibration()
{
  Wire.beginTransmission(BarAddress); //Opens Communication to Barometer
  Wire.write(0xAA);
  Wire.endTransmission(false);
  
  Wire.requestFrom(BarAddress, 22, true);
  
  //IDK Paramter does not have a listed meaning according to the datasheet
  //http://www.adafruit.com/datasheets/BMP085_DataSheet_Rev.1.0_01July2008.pdf
  
  /*
  As far as I can tell, these values are used for initial parameters for later
  calculations
  */
  
  ac1 = Wire.read()<<8|Wire.read(); //2 Bytes IDK Parameter (MSB and LSB)
  ac2 = Wire.read()<<8|Wire.read(); //2 Bytes IDK Parameter (MSB and LSB)
  ac3 = Wire.read()<<8|Wire.read(); //2 Bytes IDK Parameter (MSB and LSB)
  ac4 = Wire.read()<<8|Wire.read(); //2 Bytes IDK Parameter (MSB and LSB)
  ac5 = Wire.read()<<8|Wire.read(); //2 Bytes IDK Parameter (MSB and LSB)
  ac6 = Wire.read()<<8|Wire.read(); //2 Bytes IDK Parameter (MSB and LSB)
  b1 = Wire.read()<<8|Wire.read(); //2 Bytes IDK Parameter (MSB and LSB)
  b2 = Wire.read()<<8|Wire.read(); //2 Bytes IDK Parameter (MSB and LSB)
  mb = Wire.read()<<8|Wire.read(); //2 Bytes IDK Parameter (MSB and LSB)
  mc = Wire.read()<<8|Wire.read(); //2 Bytes IDK Parameter (MSB and LSB)
  md = Wire.read()<<8|Wire.read(); //2 Bytes IDK Parameter (MSB and LSB)

}

void getBarometerData()
{
  Wire.beginTransmission(BarAddress);
  Wire.write(0xF4);
  Wire.write(0x2E);
  Wire.endTransmission();
  delay(5);
  
  Wire.requestFrom(BarAddress, 2, false);
  uncallibrated_temp = Wire.read()<<8|Wire.read();
  
  x1 = (((long)uncallibrated_temp - (long)ac6)*(long)ac5) >> 15;
  x2 = ((long)mc << 11)/(x1 + md);
  b5 = x1 + x2;

  bar_Temperature = ((b5 + 8)>>4);  
}


// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
long bmp085GetPressure(unsigned long up)
{
  long x1, x2, x3, b3, b6, p;
  unsigned long b4, b7;
  
  b6 = b5 - 4000;
  // Calculate B3
  x1 = (b2 * (b6 * b6)>>12)>>11;
  x2 = (ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;
  
  // Calculate B4
  x1 = (ac3 * b6)>>13;
  x2 = (b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
  
  b7 = ((unsigned long)(up - b3) * (50000>>OSS));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;
    
  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;
  
  return p;
}

// Read 1 byte from the BMP085 at 'address'
char bmp085Read(unsigned char address)
{
  unsigned char data;
  
  Wire.beginTransmission(BarAddress);
  Wire.write(address);
  Wire.endTransmission();
  
  Wire.requestFrom(BarAddress, 1);
  while(!Wire.available())
    ;
    
  return Wire.read();
}

// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
int bmp085ReadInt(unsigned char address)
{
  unsigned char msb, lsb;
  
  Wire.beginTransmission(BarAddress);
  Wire.write(address);
  Wire.endTransmission();
  
  Wire.requestFrom(BarAddress, 2);
  while(Wire.available()<2)
    ;
  msb = Wire.read();
  lsb = Wire.read();
  
  return (int) msb<<8 | lsb;
}

// Read the uncompensated temperature value


// Read the uncompensated pressure value
unsigned long bmp085ReadUP()
{
  unsigned char msb, lsb, xlsb;
  unsigned long up = 0;
  
  // Write 0x34+(OSS<<6) into register 0xF4
  // Request a pressure reading w/ oversampling setting
  Wire.beginTransmission(BarAddress);
  Wire.write(0xF4);
  Wire.write(0x34 + (OSS<<6));
  Wire.endTransmission();
  
  // Wait for conversion, delay time dependent on OSS
  delay(2 + (3<<OSS));
  
  // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
  Wire.beginTransmission(BarAddress);
  Wire.write(0xF6);
  Wire.endTransmission();
  Wire.requestFrom(BarAddress, 3);
  
  // Wait for data to become available
  while(Wire.available() < 3)
    ;
  msb = Wire.read();
  lsb = Wire.read();
  xlsb = Wire.read();
  
  up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
  
  return up;
}

