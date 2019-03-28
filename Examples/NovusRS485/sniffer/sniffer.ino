#include <NovusRS485.h>
#include <NovusIO.h>

#define Size 15
unsigned int readvalues[Size*2]={0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  
  int Status =1;
  do
  {
    Serial.println("\n\n-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|\n");
    Status = Novus_RS485.enable(SNIFFER,NONE,57600,0,1);
    if (Status != 0)
    {
      Serial.print("Status: ");
      Serial.println(Status);
      Serial.println("\nTrying again in 1s\n");
      delay(1000);
    }
  }while(Status!=0);
}

void loop() {
  // put your main code here, to run repeatedly:

  Novus_RS485.flush(&readvalues[0],Size);
  
  Serial.println("\n==================| NEW |================\n");
  int Status=Novus_RS485.sniffer_bytes(Size,5000,&readvalues[0]);
  if (Status != 0)
  {
    Serial.println("----*----*----*----*----*----*----*----*");
    Serial.print("\t\tStatus: ");
    Serial.println(Status);
    Serial.println("----*----*----*----*----*----*----*----*");
  }
  else
  {
	  Serial.println(" Received: ");
	  for (int x=0; x<Size; x++)
	  {
		Serial.print(readvalues[x],HEX);
		Serial.print("\t");
		if ((x == 7))
		{
		  Serial.println();
		}
	  }
	  Serial.println();
  }
  Serial.println("\nReading again in 1s\n");
  delay(1000);
}
