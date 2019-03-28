#include <NovusIO.h>


/*  Variables and Constants */
long int previous_time = 0; // Variable to count time in Arduino, just to print every 5s in Serial

int Channel = 2; // The desired read channel;
int Time_ON = 15; // Time the pulse will stay ON; ( t = value * 100[ms])
int Period = 20; // Total time of the pulse; ( t = value * 100[ms])
int Number = 5; //Number of pulses MixIO will do;

void setup(){
  Serial.begin(9600);
  while ( !Serial)
  {
    /* Wait until Serial become available */
  }

  /* ------------------------------------------------------
      Start of INITIALIZING  and CONFIGURING NOVUS MixIO */
  Novus.digitalOutput_enPulse(Channel, Time_ON, Period, Number);

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
    Serial.println(" Write 1 to send the pulses.");  // Print this every 5s
  }
  if (Serial.available())
  {
    received_char = Serial.read();
    if (received_char == '1')
    {
      /* ------------------------------------------------------
          Start of CHANNEL'S WRITING THE PULSES              */
      Novus.digitalWrite(Channel, 1);
      /*  End of CHANNEL'S WRITING THE PULSES
        ------------------------------------------------------ */
    }
  }
}
