/*
Cayenne Ethernet Example

This sketch connects to the Cayenne server using an Arduino Ethernet Shield W5100
and runs the main communication loop.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Set the token variable to match the Arduino token from the Dashboard.
2. Compile and upload this sketch.

For Cayenne Dashboard widgets using digital or analog pins this sketch will automatically
send data on those pins to the Cayenne server. If the widgets use Virtual Pins, data
should be sent to those pins using virtualWrites. Examples for sending and receiving
Virtual Pin data are under the Basics folder.
*/

//#define CAYENNE_DEBUG         // Uncomment to show debug messages
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneEthernet.h>
#include <dht.h>

dht DHT;
#define DHT11_PIN 5

//-------------------------------------soil moisture
int sensor_pin=A0;
static int output_value;
//--------------------------------------

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "s22hn7h9k2";
void setup()
{
  Serial.begin(9600);
  Cayenne.begin(token);
  
}

void loop()
{//---------------------------------------------soil moisture
  output_value = analogRead(sensor_pin);
  output_value = map(output_value,1023,600,0,100);
  Serial.print("Moisture :");
  Serial.print(output_value);
  Serial.println("%");
  delay(1000);

//---------------------------------------------DHT11
// READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
 /* // DISPLAY DATA
  float t = DHT.humidity;
  Serial.print((t+1), 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);
  */
  Cayenne.run();
}

CAYENNE_OUT(V0)
{
  float t = DHT.temperature;
  Cayenne.virtualWrite(V0, t); //virtual pin
}

CAYENNE_OUT(V1)
{
  float h = DHT.humidity;
  Cayenne.virtualWrite(V1, h); //virtual pin
  }


CAYENNE_OUT(V3)
{ float out = analogRead(sensor_pin);
  int out2 = map(output_value,1023,600,0,100);
  
  Cayenne.virtualWrite(V3, out); //virtual pin
  }
