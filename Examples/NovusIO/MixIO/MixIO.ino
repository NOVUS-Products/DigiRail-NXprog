#include <NovusIO.h>

void setup()
{    
  //Novus.digitalOutput_enInstant(Channel, PowerOn, Safevalue);
  Novus.digitalOutput_enInstant(1, 0, 0);  // Enable  digital output 1 to receive a single write;
  
  //Novus.digitalOutput_enPulse(Channel, Time_ON, Period, Number);
  Novus.digitalOutput_enPulse(2, 10, 20, 4); // Enable digital output 2 to pulse 4 times with period = 2s, where half-time the state is HIGH;
 
  //Novus.analogInput_Mode(Channel, type, temp, Safevalue); 
  Novus.analogInput_Mode(1, tc_T, CELSIUS, 0); // Enable analog Input 1 to read a PT100 sensor;
  
  Novus.applyConfig(); //Necessary to apply your configuration in MixIO. 
  Serial.begin(9600);
}

void loop()
{
  float temp =  Novus.analogRead(1); //Reading value of tc_T in channel 1
  Serial.print("temperature: ");
  Serial.print(temp);
  Serial.println(" ºC");
  
  if (temp < 10 )
  {
    Novus.digitalWrite(1,1); // Turn ON digital channel 1
    Novus.digitalWrite(2,0); // Not use digital channel 2
  }
  else if (temp > 33 )
  {
    Novus.digitalWrite(1,0); // Turn OFF digital channel 1
    Novus.digitalWrite(2,1); // Send a pulse to digital channel 2
  }
  delay(5000);

  
}
