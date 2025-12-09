#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11

#define STEPS_PER_REVOLUTION 2048

#define CLOCKWISE 0
#define COUNTER_CLOCKWISE 1

#define TRIG_PIN 3
#define ECHO_PIN 2

int  g_step_number = 0;

bool g_b_test_done = false;

long duration, cm;

void setup() 
{
   Serial.begin( 9600 );

   pinMode( STEPPER_PIN_1, OUTPUT );
   pinMode( STEPPER_PIN_2, OUTPUT );
   pinMode( STEPPER_PIN_3, OUTPUT );
   pinMode( STEPPER_PIN_4, OUTPUT );
   pinMode( TRIG_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);
}


void loop() 
{
   digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  duration = pulseIn(ECHO_PIN, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
   if( cm <= 60 )
   {
      delay( 10 );
      Serial.println( "Processing object dodge sweep..." );
      turn(COUNTER_CLOCKWISE, 30);
      delay(100);
      turn(CLOCKWISE, 30);
      g_b_test_done = true;
      Serial.println( "Done" );
   }
}


void turn( int direction, float degrees )
{
   float num_steps = ( degrees * STEPS_PER_REVOLUTION ) / 360.0;

   for( int i = 0; i < num_steps; i++ )
   {
      step( direction );
   }
}


void step( int direction )
{
   if( CLOCKWISE == direction )
   {
      firePin( g_step_number + 1 );
   }
   else
   {
      firePin( 4 - g_step_number );
   }

   g_step_number = ( g_step_number + 1 ) % 4;
   
}


void firePin( int pin_num )
{
   digitalWrite( STEPPER_PIN_1, ( 1 == pin_num ) ? HIGH : LOW );
   digitalWrite( STEPPER_PIN_2, ( 2 == pin_num ) ? HIGH : LOW );
   digitalWrite( STEPPER_PIN_3, ( 3 == pin_num ) ? HIGH : LOW );
   digitalWrite( STEPPER_PIN_4, ( 4 == pin_num ) ? HIGH : LOW );
   delay(2);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

