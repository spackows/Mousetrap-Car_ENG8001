
// Needed to turn on the light to signal
// the whisker has sensed the block
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>
const int RED = 25;
const int OFF = 0;
const int MEDBRIGHT = 5;

// Needed to track the data coming
// from the float meter
const byte FLOAT_PIN = 8;
int float_state = HIGH;
unsigned long prev_time = millis();

// Track whether the block has been sensed
bool b_sensed = false;

void setup() 
{
   // Log what's happening
   Serial.begin( 9600 );

   // Set up the light
   WiFiDrv::pinMode( RED, OUTPUT );
   WiFiDrv::analogWrite( RED, OFF );

   // Set up the float meter sensor
   pinMode( FLOAT_PIN, INPUT );
}

void loop() 
{
   if( !b_sensed && ( millis() - prev_time ) > 500 ) // See what's up every half second
   {
      float_state = digitalRead( FLOAT_PIN );
      Serial.println( float_state );

      prev_time = millis();

      if( LOW == float_state )
      {
         b_sensed = true;
         WiFiDrv::analogWrite( RED, MEDBRIGHT );
         Serial.println( "Whisker sensed block" );
      }
   }
}

