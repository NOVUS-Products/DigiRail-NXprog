#include <NovusIO.h>


/*Choosing accordingly to defines */
//---------function
//_0_20mA
//_4_20mA
//_0_10V
 
/*  Variables and Constants */
long int previous_time = 0; // Variable to count time in Arduino, just to print every 5s in Serial

int Channel = 1; // The desired channel to write;
int Mode = _0_10V; // Choosing the output mode
int PowerOn = 0; // This  value means the first value the channel will assume in the moment of starting NOVUS MixIO;
int Safevalue = 0xFF; // The value assumed when an error has been occured;
int ValueWrite=0; 
void setup()
{
  Serial.begin(9600);
  while(!Serial)
  {
    /* Wait until Serial become available */ 
  }
  
  /* ------------------------------------------------------
      Start of INITIALIZING  and CONFIGURING NOVUS MixIO */
  Novus.analogOutput_Mode(Channel, Mode, PowerOn, Safevalue);
  
  Novus.applyConfig(); //Necessary to apply your configuration in MixIO. 
  /*  End of INITIALIZING  and CONFIGURING NOVUS MixIO 
  ------------------------------------------------------ */
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  long int current_time = millis();
  char received_char = ' ';
  int sendValue = 0;
  
  if (current_time - previous_time >= 5000)
  {
    previous_time = current_time;
    Serial.println(" Write 0 to turn off the channel.");  // Print this every 5s
    Serial.println(" Write 1 to turn on the channel.");  // Print this every 5s
    Serial.println(" Write I to increment the ValueWrite on the channel.");  // Print this every 5s
  }
  if (Serial.available())
  {
    received_char = Serial.read();
    if (received_char == '0')
    {
      ValueWrite=0;
      Serial.println("Value sent is: 0");
      /* ------------------------------------------------------
          Start of CHANNEL'S WRITING                         */
      Novus.analogWrite(Channel,0);
      /*  End of CHANNEL'S WRITING
      ------------------------------------------------------ */
    }
    else if (received_char == '1')
    {
      if (Mode == _0_10V)
      {
        Serial.println("Value sent is: 5V");
      }
      else if (Mode == _0_20mA)
      {
        Serial.println("Value sent is: 10mA");
      }
      else if (Mode == _4_20mA)
      {
        Serial.println("Value sent is: 12mA");
      }
      /* ------------------------------------------------------
          Start of CHANNEL'S WRITING                         */
      Novus.analogWrite(Channel,16000); 
      // scale is 0 to 32000 and mode is 0 to 10V,
      //so writing 16000 means that will be written 5V
      /*  End of CHANNEL'S WRITING
      ------------------------------------------------------ */
    }
    else if ((received_char == 'I')||(received_char == 'i'))
    {
      ValueWrite++;
      Serial.print("Value sent is: ");
      Serial.print(ValueWrite);
      if (Mode == _4_20mA)
      {
		if ((ValueWrite > 20)||(ValueWrite < 4))
		{
			ValueWrite=4;
		}
		Serial.println(" mA");
      }
      else if (Mode == _0_20mA)
      {
		if ((ValueWrite > 20)||(ValueWrite < 0))
		{
			ValueWrite=0;
		}
		Serial.println(" mA");
      }
      else if (Mode == _0_10V)
      {
		if ((ValueWrite > 10)||(ValueWrite < 0))
		{
			ValueWrite=0;
		}
		Serial.println(" V");
      }
      
      /* ------------------------------------------------------
          Start of CHANNEL'S WRITING                         */
      Novus.analogWrite(Channel,ValueWrite); 
      /*  End of CHANNEL'S WRITING
      ------------------------------------------------------ */
    }
  }
}
