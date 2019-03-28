#include <NovusIO.h>


/*Choosing accordingly to defines */
//---------function
//LOGIC 
//COUNTER_UP 
//COUNTER_DOWN
//TIME

//---------type
//PNP 
//NPN 
//DRY_CONTACT 
 
/*  Variables and Constants */
long int previous_time = 0; // Variable to count time in Arduino, just to print every 5s in Serial

int Channel = 1; // The desired read channel;
int function = LOGIC; //the desired function of channel choosed
int type = DRY_CONTACT; //the desired kind of contact
int Debounce = 10; // time to estabilize the reading, in ' debounce x 100ms';

void setup(){

  Serial.begin(9600);
  while( !Serial)
  {
    /* Wait until Serial become available */ 
  }
  
  
  /* ------------------------------------------------------
      Start of INITIALIZING  and CONFIGURING NOVUS MixIO */
  Novus.digitalInput_Mode(Channel ,function ,type , Debounce); //Canal, Funcao, Type, Debouce
  
  Novus.applyConfig(); //Necessary to apply your configuration in MixIO. 
  /*  End of INITIALIZING  and CONFIGURING NOVUS MixIO 
  ------------------------------------------------------ */
}

void loop(){
  // put your main code here, to run repeatedly:
  
  long int current_time = millis();
  char received_char = ' ';
  
  if (current_time - previous_time >= 5000)
  {
    previous_time = current_time;
    Serial.println(" Write R, to read the value from digital input! ");  // Print this every 5s
  }
  if (Serial.available())
  {
    received_char = Serial.read();
    if ((received_char == 'R')||(received_char == 'r'))
    {

      /* ------------------------------------------------------
          Start of CHANNEL'S READING                            */
      int Reading_input = Novus.digitalRead(Channel);
      /*  End of CHANNEL'S READING 
      ------------------------------------------------------ */

      //Reading mode returns the value read in the port
      Serial.print(" The value read was: ");
      Serial.println(Reading_input);
    }
  }
}
