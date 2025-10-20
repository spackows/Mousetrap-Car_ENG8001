
// Needed to turn on the light to signal
// the whisker has sensed the block
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>
const int RED = 25;
const int OFF = 0;
const int MEDBRIGHT = 5;

// Needed to track the data coming
// from the flow meter
const byte FLOW_PIN = 8;
int flow_count = 0;
int prev_count = 0;
unsigned long prev_time = millis();
bool b_wheel_turning = false;

void setup() 
{
   // Log what's happening
   Serial.begin( 9600 );

   // Set up the light
   WiFiDrv::pinMode( RED, OUTPUT );
   WiFiDrv::analogWrite( RED, OFF );

   // Set up the flow meter sensor
   pinMode( FLOW_PIN, INPUT_PULLUP );
   attachInterrupt( FLOW_PIN, flowCounter, FALLING );
   attachInterrupt( FLOW_PIN, flowCounter, RISING );
}

void loop() 
{
   if( ( millis() - prev_time ) > 500 ) // See what's up every half second
   {
      b_wheel_turning = ( flow_count == prev_count ) ? false : true;

      prev_count = flow_count;
      prev_time = millis();

      if( b_wheel_turning )
      {
         WiFiDrv::analogWrite( RED, MEDBRIGHT );
         Serial.println( "b_wheel_turning" );
      }
   }
}
  
void flowCounter()
{
   flow_count++;
}
