#include <NovusRS485.h>
#include <NovusIO.h>
 
 /* Max PDU supported by Modbus: 256 bytes
  *  
  *  To use Modbus, you allways has to choose what device do you want to control, using his Address in the first slot.
  *  Next stape is decide wich function will be used, and its parameters.
  *  
  *                           |   0   |   1  |    2    |   3     |   4    |    5   |    6   |   7   | 4+(Qnt*2) | 5+(Qnt*2) |
  * Read register(s):  3  --> | Slave | Func | Regst H | Regst L | Qnt H  | Qnt L  |  CRC L | CRC H | 
  * Return reading  :     <-- | Slave | Func |   Qnt   | Val0 H  | Val0 L | Val1 H | Val1 L |  ...  |   CRC L   |   CRC H   | 
  * 
  * To read a register using Modbus, use function 3 (0x03). Inform the starter register and the quantity you wish to read.
  * 
  *                           |   0   |   1  |    2    |    3    |   4   |   5   |   6   |   7   |
  * Write register :   6  --> | Slave | Func | Regst H | Regst L | Val H | Val L | CRC L | CRC H | 
  * Return writing :      <-- | Slave | Func | Regst H | Regst L | Val H | Val L | CRC L | CRC H |  
  * 
  * To write in a SINGLE register using Modbus, use function 6 (0x06). Inform the register wished and the value to write.
  * 
  *                           |   0   |   1  |    2    |    3    |   4   |   5   |     6   |    7    |    8   |    9   |   10   | ... | 9+(Qnt*2) | 9+(Qnt*2) |
  * Write register :   16 --> | Slave | Func | Regst H | Regst L | Qnt H | Qnt L |  2*Qnt  | Val0 H  | Val0 L | Val1 H | Val1 L | ... |   CRC L   |   CRC H   |
  * Return writing :      <-- | Slave | Func | Regst H | Regst L | Val H | Val L |  CRC L  | CRC H   | 
  * 
  * To write in MULTIPLE registers using Modbus, use function 16 (0x20). Inform the starter register, the quantity of registers and the values to write.
  *
  */

/* Do NOT modify */
#define MAX 256
uint16_t ModbusPDU_send[MAX]={0};    //Array to send to RS485
uint16_t ModbusPDU_received[MAX]={0}; //Array to receive from RS485
uint16_t MAX_send=0; //Number of bytes sent
uint16_t MAX_received=0; //Number of bytes received


/* User parameters */
uint8_t channel=1;
uint16_t safeValue=0;

uint8_t SlaveAddress=8;     //Choosed address
uint8_t ModbusFunction=6;   //Read(3), Write_1(6), Write_N(16), ...
uint16_t StarterRegister=1; //Choosed register
uint16_t Quantity=1;        //Quantity of registers to write or read
uint8_t Values[2]={0};     //values to write or read


void setup() {
   
  Serial.begin(9600);
  while(!Serial);
  
  Novus_RS485.enable(MASTER,NONE,_19200,NONE,1);
  Novus.analogInput_Mode(channel,tc_T,CELSIUS,safeValue);
  Novus.applyConfig();
  
}



void loop() {
  // put your main code here, to run repeatedly:
   uint16_t temp=(uint16_t)(10*Novus.analogRead(channel)); //Multiplying 10 because of decimal point
   Serial.print("Temperature is: ");
   Serial.print(temp);
   Serial.println(" ºC\n");
   Values[0]= (uint8_t)((temp >> 8) & 0xFF); // High part of temperature
   Values[1]= (uint8_t)((temp >> 0) & 0xFF); // Low part of temperature
   
   creatingPDU();
   printing_send();  
   
   int state = Novus_RS485.communicate(&ModbusPDU_send[0], MAX_send, &ModbusPDU_received[0], MAX_received);
   if (state == 0)
   {
		printing_receive();
   }
   else
   {
	   Serial.print(F("Returned error "));
	   Serial.println(state);
   }
   delay(1000); //wait 1s to send again
}




void printing_receive()
{
  Serial.print(F(" PDU received: [ "));
  for (int x=0; x < MAX_received; x++)
  {
  if (ModbusPDU_received[x] > 0XF) 
  {
    Serial.print(ModbusPDU_received[x],HEX);
  }
  else
  {
    Serial.print(F("0"));
    Serial.print(ModbusPDU_received[x],HEX);
  }
  Serial.print(" ");
  if (x == (MAX_received-1))
  {
  Serial.println(F("]\n"));
  }
  }
}

void printing_send()
{
  if(ModbusFunction == 3)
  {
    Serial.println(F("exm: [ Ad Fn Rh Rl Qh Ql Cl Ch ]"));
  }
  else if (ModbusFunction == 6)
  {
    Serial.println(F("exm: [ Ad Fn Rh Rl Vh Vl Cl Ch ]"));
  }
  else if (ModbusFunction == 16)
  {
    Serial.println(F("exm: [ Ad Fn Sh Sl Qh Ql NB Vh Vl Vh Vl Vh Vl Cl Ch ]"));
  }
  Serial.print(F("PDU: [ "));
  for (int x=0; x < MAX_send; x++)
  {
    if (ModbusPDU_send[x] > 0XF) 
    {
      Serial.print(ModbusPDU_send[x],HEX);
    }
    else
    {
      Serial.print(F("0"));
      Serial.print(ModbusPDU_send[x],HEX);
    }
    
    Serial.print(F(" "));
    if (x == (MAX_send-1))
    {
      Serial.print(F("]\nP_r: [ "));
    }
  }
}

void creatingPDU()
{
  ModbusPDU_send[0] = SlaveAddress;              // Slave address
  ModbusPDU_send[1] = ModbusFunction;                // 3- Read single register | 6- Write single register | 16- Write multiple register
  ModbusPDU_send[2] = ((StarterRegister & 0xFF00) >> 8);           // High byte of register
  ModbusPDU_send[3] = ((StarterRegister & 0x00FF) >> 0);           // Low byte of register
  if (ModbusFunction == 3) //Read function
  {
    ModbusPDU_send[4] = ((Quantity >> 8) & 0xFF);       // High byte of quantity
    ModbusPDU_send[5] = ((Quantity >> 0) & 0xFF);       // Low byte of quantity
    
    MAX_send = 8; //Max PDU sent
    MAX_received = 5 + Quantity*2; //Max PDU receive
  }
  else if (ModbusFunction == 6) //Write single function
  {
    ModbusPDU_send[4] = Values[0]; //((Values[0] >> 8) & 0xFF);       // High byte of value
    ModbusPDU_send[5] = Values[1]; //((Values[1] >> 0) & 0xFF);       // Low byte of value
    
    MAX_send = 8; //Max PDU sent
    MAX_received = 8; //Max PDU receive
  }
  else if (ModbusFunction == 16) //Write multiple function
  {
    ModbusPDU_send[4] = ((Quantity >> 8) & 0xFF);       // High byte of quantity
    ModbusPDU_send[5] = ((Quantity >> 0) & 0xFF);       // Low byte of quantity
    ModbusPDU_send[6] = 2*Quantity;             // byte count
    for (int x=0; x<Quantity ;x++)
    {
      ModbusPDU_send[7+2*x] = ((Values[x] >> 8) & 0xFF); // High byte of value
      ModbusPDU_send[8+2*x] = ((Values[x] >> 0) & 0xFF); // Low byte of value
    }
    
    MAX_send = 9 + 2*Quantity; //Max PDU sent
    MAX_received = 8; //Max PDU receive
   }
   
   //Calculating CRC
   uint16_t u16CRC = getCRC( &ModbusPDU_send[0],(MAX_send - 2));
   ModbusPDU_send[(MAX_send - 2)]  =  (uint8_t) (u16CRC & 0xFF); 
   ModbusPDU_send[(MAX_send - 2) + 1]      =  (uint8_t) (u16CRC >> 8);
}
 
uint16_t getCRC( uint16_t *pBufferSerial, uint8_t u8NumBytes )
{
  /* Calculate CRC  from the byte '0' until the number of bytes indicated by 'u8NumBytes' */
    uint16_t u16CRC;
    uint16_t u16Index;
    uint8_t bLSB;
    uint8_t u8Aux;

    u16CRC = 0xffff;

   // Passing throught all the bytes
    for( u16Index = 0; u16Index < u8NumBytes; u16Index++ )
    {
        // XOR between frames byte and Low part of CRC
        u8Aux = pBufferSerial[u16Index] ^ (uint8_t)(u16CRC & 0xff);

        u16CRC &= 0xff00;
        u16CRC |= u8Aux;

        u8Aux = 8;
        while( u8Aux-- )
        {
            // stop when LSB = 1
            bLSB = u16CRC & 0x01; // Extracion do LSB
            u16CRC = u16CRC>>1;

            if( bLSB )
            {
                u16CRC = u16CRC ^ 0xA001;   // XOR between CRC and 0xA001
            }
        }
    }

    return u16CRC;

}

bool verificaCRC( uint16_t *pBufferSerial, uint8_t u8Index )
{
  // Return FALSE when occurred error in CRC.
    uint16_t u16CRC;

    // ucIndex is the number of bytes received.
    // IMPORTANT: remove 2 from MAX_received, because the CRC is not counted here
    u8Index -= 2;

    u16CRC = getCRC( pBufferSerial, u8Index );

    if( (pBufferSerial[u8Index++] == (uint8_t)(u16CRC & 0xff)) && (pBufferSerial[u8Index] == (uint8_t)(u16CRC>>8)) )
    {
        return false;
    }
    else
    {
        return true;
    }
}
 
