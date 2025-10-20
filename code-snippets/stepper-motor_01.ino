
#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11

#define CLOCKWISE 0
#define COUNTER_CLOCKWISE 1

int step_number = 0;


void setup() 
{
   pinMode( STEPPER_PIN_1, OUTPUT );
   pinMode( STEPPER_PIN_2, OUTPUT );
   pinMode( STEPPER_PIN_3, OUTPUT );
   pinMode( STEPPER_PIN_4, OUTPUT );
}


void loop() 
{
   step( CLOCKWISE );
   delay( 2 );
}


void step( int direction )
{
   if( CLOCKWISE == direction )
   {
      firePin( step_number + 1 );
   }
   else
   {
      firePin( 4 - step_number );
   }

   step_number = ( step_number + 1 ) % 4;
   
}


void firePin( int pin_num )
{
   digitalWrite( STEPPER_PIN_1, ( 1 == pin_num ) ? HIGH : LOW );
   digitalWrite( STEPPER_PIN_2, ( 2 == pin_num ) ? HIGH : LOW );
   digitalWrite( STEPPER_PIN_3, ( 3 == pin_num ) ? HIGH : LOW );
   digitalWrite( STEPPER_PIN_4, ( 4 == pin_num ) ? HIGH : LOW );
}


