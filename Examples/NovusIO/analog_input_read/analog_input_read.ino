#include <NovusIO.h>

/*Choosing accordingly to defines */

//---------type
//tc_J
//tc_K
//tc_T
//tc_E
//tc_N
//tc_R
//tc_S
//tc_B

//NTC

//Pt100
//Pt1000

//_0_20mA
//_4_20mA

//_0_60mV
// _0_5V
// _0_10V

//---------temp
//CELSIUS
//FAHRENHEIT
 
/*  Variables and Constants */
long int previous_time = 0; // Variable to count time in Arduino, just to print every 5s in Serial;

int Channel = 1; // The desired channel to read;
int type = tc_T; // The desired kind of input
int temp = CELSIUS; // the temperature degrees
int Safevalue = 0xFF; // The value assumed when an error has been occured;

void setup(){
  Serial.begin(9600);
  while( !Serial) {/* Wait until Serial become available */ }
  
  /* ------------------------------------------------------
      Start of INITIALIZING  and CONFIGURING NOVUS MixIO */
  Novus.analogInput_Mode(Channel, type, temp, Safevalue); //Configuring Channel 1 from analog Input as a read of Thermocouple T in Celsius degrees.
  
  Novus.applyConfig(); //Necessary to apply your configuration in NOVUS MixIO. 
  /*  End of INITIALIZING  and CONFIGURING NOVUS MixIO 
  ------------------------------------------------------ */
}

void loop(){
  // put your main code here, to run repeatedly:
  
  long int current_time = millis();
  char received_char = ' ';
  
  if (current_time - previous_time >= 500)
  {
    previous_time = current_time;
//    Serial.println(" Write R, to read the value from analog input! ");  // Print this every 1s
//  }
//  if (Serial.available())
//  {
//    received_char = Serial.read();
//    if ((received_char == 'R')||(received_char == 'r'))
//    {

      /* ------------------------------------------------------
          Start of CHANNEL'S READING                            */
      float Reading_input = Novus.analogRead(Channel);
      /*  End of CHANNEL'S READING 
      ------------------------------------------------------ */

      //Reading mode returns the value read in the port
      Serial.print(" The value read was: ");
      Serial.print(Reading_input,1); //Print the value with 1 decimal point
      if ( temp == CELSIUS )
      {
        Serial.println(" ºC");        
      }
      else if ( temp == FAHRENHEIT )
      {
        Serial.println(" ºF"); 
      }
//    }
  }
}
