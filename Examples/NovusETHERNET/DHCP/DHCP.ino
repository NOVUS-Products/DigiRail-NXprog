#include <NovusETHERNET.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while(!Serial);

  Novus_ETHERNET.enable(1); // Setting 1 as the parameter enables ethernet as DHCP
  Novus_ETHERNET.applyConfig();

}

void loop() {
  char msg=' ';
  
  if (Serial.available())
  {
    msg=Serial.read();

    if (msg=='R')
    {
       Novus_ETHERNET.readConfig(); //Read IP used in DHCP mode and print in Serial Monitor
    } 
  }
}
