#include <NovusETHERNET.h>

// Create IPs used as a IPAdress structure
IPAddress ip(10,51,11,214);
IPAddress mask(255,255,0,0);
IPAddress gateway(10,51,1,254);
IPAddress DNS(0,0,0,0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while(!Serial);

  Novus_ETHERNET.enable(0,ip,mask,gateway,DNS);; // Enables ETHERNET with static IP
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
