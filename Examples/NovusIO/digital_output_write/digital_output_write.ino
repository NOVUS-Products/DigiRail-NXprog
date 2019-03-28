#include <NovusIO.h>

 
/*  Variables and Constants */
long int previous_time = 0; // Variable to count time in Arduino, just to print every 5s in Serial

int Channel = 2; // The desired read channel;
int PowerOn = 0; // This  value means the first value the channel will assume in the moment of starting NOVUS MixIO;
int Safevalue = 0; // The value assumed when an error has been occured;

void setup()
{
  Serial.begin(9600);
  while( !Serial) {/* Wait until Serial become available */ }
  
  /* ------------------------------------------------------
      Start of INITIALIZING  and CONFIGURING NOVUS MixIO */
  Novus.digitalOutput_enInstant(Channel, PowerOn, Safevalue);
  
  Novus.applyConfig(); //Necessary to apply your configuration in MixIO. 
  /*  End of INITIALIZING  and CONFIGURING NOVUS MixIO 
  ------------------------------------------------------ */
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  long int current_time = millis();
  char received_char = ' ';
  
  if (current_time - previous_time >= 5000)
  {
    previous_time = current_time;
    Serial.println(" Write 0 to turn off the channel.");  // Print this every 5s
    Serial.println(" Write 1 to turn on the channel.");  // Print this every 5s
  }
  if (Serial.available())
  {
    received_char = Serial.read();
    if (received_char == '0')
    {
      Serial.println("turn it OFF");
      /* ------------------------------------------------------
          Start of CHANNEL'S WRITING                         */
      Novus.digitalWrite(Channel,0);
      /*  End of CHANNEL'S WRITING
      ------------------------------------------------------ */
    }
    else if (received_char == '1')
    {
      Serial.println("turn it ON");
      /* ------------------------------------------------------
          Start of CHANNEL'S WRITING                         */
      Novus.digitalWrite(Channel,1);
      /*  End of CHANNEL'S WRITING
      ------------------------------------------------------ */
    }
  }
}
