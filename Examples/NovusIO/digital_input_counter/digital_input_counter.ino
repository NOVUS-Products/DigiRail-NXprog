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
 
/* User definnition */
int Channel = 1; // The desired read channel;
int function = COUNTER_UP; //the desired function of channel choosed
int type = DRY_CONTACT; //the desired kind of contact
int Debounce = 10; // time to estabilize the reading, accordingly to ' debounce x 100ms';

void setup(){

  Serial.begin(9600);
  while( !Serial)
  {
    /* Wait until Serial become available */
  }
  
  /* ------------------------------------------------------
      Start of INITIALIZING  and CONFIGURING NOVUS MixIO */
  Novus.digitalInput_Mode(Channel ,function ,type , Debounce);
  
  Novus.applyConfig(); // Applying the configuration to DigiRail
  /*  End of INITIALIZING  and CONFIGURING NOVUS MixIO 
  ------------------------------------------------------ */
}

void loop(){
	/* ------------------------------------------------------
		Start of CHANNEL'S READING                            */
	int Reading_input = Novus.digitalReadCounter(Channel);
	/*  End of CHANNEL'S READING 
	------------------------------------------------------ */

	if (function == COUNTER_UP) //Counter UP-Borders mode returns the number of UP-Boarders counted
	{
	  Serial.print("Occured ");
	  Serial.print(Reading_input);
	  Serial.print(" UP-Borders in the channel ");
	  Serial.println(Channel);
	}
	else if (function == COUNTER_DOWN) //Counter DOWN-Borders mode returns the number of DOWN-Boarders counted
	{
	  Serial.print("Occured ");
	  Serial.print(Reading_input);
	  Serial.print(" DOWN-Borders in the channel ");
	  Serial.println(Channel);
	}
	delay(1); // Wait 1 second to next read
}
