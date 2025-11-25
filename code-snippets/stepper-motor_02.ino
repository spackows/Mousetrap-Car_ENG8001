
#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11

#define STEPS_PER_REVOLUTION 2048

#define CLOCKWISE 0
#define COUNTER_CLOCKWISE 1
int  g_step_number = 0;

bool g_b_test_done = false;


void setup() 
{
   Serial.begin( 9600 );

   pinMode( STEPPER_PIN_1, OUTPUT );
   pinMode( STEPPER_PIN_2, OUTPUT );
   pinMode( STEPPER_PIN_3, OUTPUT );
   pinMode( STEPPER_PIN_4, OUTPUT );
}


void loop() 
{
   if( !g_b_test_done )
   {
      delay( 10 );
      Serial.println( "Turning 13 degrees clockwise.." );
      turn( CLOCKWISE, 13.0 );
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
}


