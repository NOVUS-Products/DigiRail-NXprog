#include <NovusDevice.h>

int channel=0, type=0, mode=0;

void setup() {
  Serial.begin(9600);  // Begin the Monitor Serial
  while(!Serial)
  {
    // Wait until Monitor Serial is available 
  }
  Serial.println("  Press R to read NOVUS MixIO according to configuration choosed.");
  Serial.println("  Press S to see wich configuration is used.");
  Serial.println("  Press C to change Channel choosed.");
  Serial.println("  Press T to change between (ALL, Digital and Analog) channels.");
  Serial.println("  Press M to change between (ALL, Input and Output) channels.");
  Serial.println("  Press 4 to read RS485 configuration.");
  Serial.println("  Press E to read ETHERNET configuration.");
}

void loop() {
  char msg=' ';
  if (Serial.available())
  {
    msg=Serial.read(); // Wait for the characters specified on Monitor Serial prints
    if ((msg =='R')||(msg =='r'))
    {
      ReadDevice.Configs(channel, type, mode); 
      Serial.println("  Press R to read NOVUS MixIO according to configuration choosed.");
      Serial.println("  Press S to see wich configuration is used.");
      Serial.println("  Press C to change Channel choosed.");
      Serial.println("  Press T to change between (ALL, Digital and Analog) channels.");
      Serial.println("  Press M to change between (ALL, Input and Output) channels.");
	  Serial.println("  Press 4 to read RS485 configuration.");
      Serial.println("  Press E to read ETHERNET configuration.");
      
    }
    if ((msg =='S')||(msg =='s'))
    {
	  // Print the channel choosed
      if(channel == 0)
      {
        Serial.print("\nchannel: ALL");
      }
      else
      {
        Serial.print("\nchannel: ");
        Serial.print(channel);
      }
      
	  // Print the type choosed
      if(type == 0)
      {
        Serial.print("\t type: ALL");
      }
      else if(type == 1)
      {
        Serial.print("\t type: DIGITAL");
      }
      else if(type == 2)
      {
        Serial.print("\t type: ANALOG");
      }
      
	  // Print the mode choosed
      if(mode == 0)
      {
        Serial.println("\t mode: ALL");
      }
      else if(mode == 1)
      {
        Serial.println("\t mode: INPUT");
      }
      else if(mode == 2)
      {
        Serial.println("\t mode: OUTPUT");
      }
    }
    if ((msg =='C')||(msg =='c')) //Changing the channel choosed to read configurations
    {
      channel++;  //Add 1 in channel
	  if (channel>4)
	  {
		  channel=0; // Channel accepts only: 0, 1, 2, 3 and 4
	  }
	  
	  // Print the correspondent value
      if(channel == 0)
      {
        Serial.print("\nchannel: ALL");
      }
      else
      {
        Serial.print("\nchannel: ");
        Serial.print(channel);
      }
    }
    if ((msg =='T')||(msg =='t')) //Changing the type choosed to read configurations
    {
      type++; //Add 1 in type
      if (type>2)
      {
        type=0; //Type  accepts only: 0, 1 and 2
      }
	  
	  // Print the correspondent value 
      if(type == 0)
      {
        Serial.println("\ntype changed for ALL");
      }
      else if(type == 1)
      {
        Serial.println("\ntype changed for DIGITAL");
      }
      else if(type == 2)
      {
        Serial.println("\ntype changed for ANALOG");
      }
    }
    if ((msg =='M')||(msg =='m')) //Changing the mode choosed to read configurations
    {
      mode++;  //Add 1 in mode
	  if (mode>2)
	  {
		  mode=0; //mode  accepts only: 0, 1 and 2
	  }
	  
	  // Print the correspondent value
      if(mode == 0)
      {
        Serial.println("\nmode changed for ALL");
      }
      else if(mode == 1)
      {
        Serial.println("\nmode changed for INPUT");
      }
      else if(mode == 2)
      {
        Serial.println("\nmode changed for OUTPUT");
      }
    }
	if (msg == '4')
	{
		ReadDevice.RS485Config();
	}
	if ((msg == 'E')||(msg == 'e'))
	{
		ReadDevice.ETHERNETConfig();
	}
  }
}