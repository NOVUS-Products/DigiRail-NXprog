#include <NovusRS485.h>
#include <NovusIO.h>

/*
 *  THIS PART CAN BE MODIFIED (BEGIN)
 */
bool MonitorSerial_PlotSerial = 1; // 0: Monitor Serial | 1: Plot Serial

bool Plot_N1200 = false; // Appears in Serial Plotter if true
bool Plot_TXBlock = true; // Appears in Serial Plotter if true
bool Plot_tcJ = true; // Appears in Serial Plotter if true
bool Plot_RHT = true; // Appears in Serial Plotter if true

int PeriodBlink_Green = 2000; // Time to blink [ms] GREEN LED in STAND-BY mode

int AlarmPeriod = 250; //Red LED will blink at this period [ms] if any peripherical activates alarm

int AlarmTemperature_TxBlock = 28; // Value that TXBlock will activate alarm [ºC]
int AlarmTemperature_tcJ = 28; // Value that tc_J will activate alarm [°C]
int AlarmHumidity_RHT = 60; // Value that RHT will activate alarm [%]
/*
 *  THIS PART CAN BE MODIFIED (END)
 */

float SetPointChange = 2.0;

unsigned long PreviousTime_Green = 0;
unsigned long CurrentTime_Green = 0;

int PeriodBlink_Red = 0; //
unsigned long PreviousTime_Red = 0;
unsigned long CurrentTime_Red = 0;

bool Alarm_N1200 = false;
bool Alarm_tcJ = false;
bool Alarm_TxBlock = false;
bool Alarm_RHT = false;

int StateMachine = 0;

// variables for print
  float ValueN1200SetPoint = 0;
  
  bool ActualState_Red = LOW;
  
  bool ActualState_Green = LOW;
  
  float Temperature_TxBlock = 0;
  
  float temperature_tcJ = 0;
  
  float Temperature_RHT = 0;
  float Humidity_RHT = 0;
  float DewPoint_RHT = 0;

typedef enum{
  LEDStandby = 1,
  N1200Alarm,
  N1200SetPoint,
  RHTClimate,
  TXBlock,
  ThermocoupleJ,
  PrintValues
};

void setup() {  
  int PowerOn = 0; // This  value means the first value the channel will assume in the starting of NOVUS DigiRail NXProg;
  int Safevalue = 0; // The value assumed when an error has been occured;
  int Debounce = 10; // time to estabilize the reading, in ' debounce x 100ms';

  Serial.begin(9600); //Starts serial with baudrate 9600
  delay(100);
  Serial.println("Configuring...");
     
//Novus.analogInput_Mode(Channel, type, temp, Safevalue);
  Novus.analogInput_Mode(1, tc_J, CELSIUS, Safevalue); //Configure analog input channel 1 to read a thermocouple type J in Celsius degrees
  Novus.analogInput_Mode(2, _4_20mA, NONE, Safevalue); //Configure analog input channel 2 to read a thermocouple type T in Celsius degrees
  
//Novus.analogOutput_Mode(Channel, Mode, PowerOn, Safevalue);
  Novus.analogOutput_Mode(1, _4_20mA, PowerOn, Safevalue); //Configure analog output channel 1 to write in N1200 set point
  
//Novus.digitalInput_Mode(Channel ,function ,type , Debounce);
  Novus.digitalInput_Mode(1 ,LOGIC , DRY_CONTACT , Debounce); //Configure digital inpur channel 1 to read alarm from N1200
  
//Novus.digitalOutput_enInstant(Channel, PowerOn, Safevalue);
  Novus.digitalOutput_enInstant(1, PowerOn, Safevalue); //Configure digital output channel 1 to write in the greeen LED
  Novus.digitalOutput_enInstant(2, PowerOn, Safevalue); //Configure digital output channel 2 to write in the red LED

//Novus_RS485.enable(Mode, SlaveAddress, Baudrate, Parity, Stopbits);
  Novus_RS485.enable(MASTER,NONE,_19200,NONE,1); //Configure RS485 to be a Master with Baudrate 19200, no parity and Stopbits  
    
  Novus.applyConfig(); //Necessary to apply configurations in DigiRail NXprog
  
//Novus.digitalWrite(Channel,Value);
  Novus.digitalWrite(1,HIGH); //Turns both Leds ON to show the code is starting
  Novus.digitalWrite(2,HIGH); //Turns both Leds ON to show the code is starting
  delay(5000); //Wait 5s
  Novus.digitalWrite(1,LOW);  //Turns both Leds OFF to show the code is starting
  Novus.digitalWrite(2,LOW);  //Turns both Leds OFF to show the code is starting
  
  StateMachine = LEDStandby;
}

void loop() {
  switch ( StateMachine ) //State machine between the functionalitys
  {
    //-----------------------------------------------------------------
    //-------------------------- LEDStandby ---------------------------
    //-----------------------------------------------------------------
    case LEDStandby: // Stand By, green LED blinks in DIGITAL OUTPUT 1  and red only blinks if an alarm has been activated
    {
      CurrentTime_Green = millis(); // Arduinos function to blink Green LED
      CurrentTime_Red = millis(); // Arduinos function to blink Red LED
      
      if (( Alarm_N1200 ) || ( Alarm_tcJ ) || ( Alarm_TxBlock ) || ( Alarm_RHT ))
      {
        
      //Novus.digitalWrite(Channel,Value);
        Novus.digitalWrite(1,LOW); //Turns off Green Led
        
        if (CurrentTime_Red - PreviousTime_Red >= PeriodBlink_Red)  //It's time to blink Red LED
        {
          PreviousTime_Red = CurrentTime_Red; // Restart time
                  
          ActualState_Red = !ActualState_Red; // Blink Red LED accordingly to its last state
          
        //Novus.digitalWrite(Channel,Value);
          Novus.digitalWrite(2,ActualState_Red); //Write the new value in the Red Led
        }
      }
      else
      {
        
      //Novus.digitalWrite(Channel,Value);
        Novus.digitalWrite(2,LOW); //Turns off Red Led
        
        if (CurrentTime_Green - PreviousTime_Green >= PeriodBlink_Green)  //It's time to blink Green LED
        {
          PreviousTime_Green = CurrentTime_Green; // Restart time
                  
          ActualState_Green = !ActualState_Green; // Blink Green LED accordingly to its last state
          
        //Novus.digitalWrite(Channel,Value);
          Novus.digitalWrite(1,ActualState_Green); //Write the new value in the Green Led
        }        
      }
      
      StateMachine = N1200Alarm;
      break;
    }

    //-----------------------------------------------------------------
    //-------------------------- N1200Alarm ---------------------------
    //-----------------------------------------------------------------    
    case N1200Alarm: // Read Alarm from N1200 in DIGITAL INPUT 1
    {
                      //Novus.digitalRead(Channel)
      Alarm_N1200 = Novus.digitalRead(1); //Read the Digital input 1
   
      if ( Alarm_N1200 == true)
      {
        // Alarm occured
        PeriodBlink_Red = AlarmPeriod;
      }
      else
      {
        // Normally working
        PeriodBlink_Red = 0;
      }
      
      StateMachine = ThermocoupleJ;
      break;
    }
    
    //-----------------------------------------------------------------
    //------------ ThermocoupleJ Connected do NXprog-------------------
    //-----------------------------------------------------------------
    case ThermocoupleJ: // tc_J in ANALOG INPUT 1
    {
      //                 Novus.analogRead(Channel)
      temperature_tcJ = Novus.analogRead(1); //Read the Analog input 1
      temperature_tcJ -= 6; //Adjusting value
 
      if (temperature_tcJ >= AlarmTemperature_tcJ)
      {
        // Alarm occured
        Alarm_tcJ = true;
        PeriodBlink_Red = AlarmPeriod;
      }
      else
      {
        // Normally working
        Alarm_tcJ = false;
        PeriodBlink_Red = 0;      
      }
      
      StateMachine = TXBlock;
      break;
    }
    
    //-----------------------------------------------------------------
    //---------------------------- TXBlock ----------------------------
    //-----------------------------------------------------------------
    case TXBlock: // TX Block with tc_T in ANALOG INPUT 2
    {
      //                 Novus.analogRead(Channel)
      Temperature_TxBlock = Novus.analogRead(2); //Read the Analog input 2
      Temperature_TxBlock = ((Temperature_TxBlock - 40) * (100)) / (2000 - 40); //Adjusting scale
    
      if (Temperature_TxBlock >= AlarmTemperature_TxBlock)
      {
        // Alarm occured
        Alarm_TxBlock = true;
        PeriodBlink_Red = AlarmPeriod;
      }
      else
      {
        // Normally working
        Alarm_TxBlock = false;
        PeriodBlink_Red = 0;      
      }
      
      StateMachine  = N1200SetPoint;
      break;
    }
    
    //-----------------------------------------------------------------
    //------------------------ N1200SetPoint --------------------------
    //-----------------------------------------------------------------
    case N1200SetPoint: // Write a Remote SP from N1200 in ANALOG OUTPUT 1
    {
      char str = '0';
      float conversion = 0.0;
      int x = 0;

      while(Serial.available()) //Read everything from serial and saves in STR buffer;
      {
        str = Serial.read();
        if (str=='+')
        {
          ValueN1200SetPoint += SetPointChange; // Increments   
          if ( ValueN1200SetPoint > 105 )
          {
            ValueN1200SetPoint = 100;
          }
        }
        if (str=='-')
        {         
          ValueN1200SetPoint -= SetPointChange; // Decrements  
          if ( ValueN1200SetPoint < 0 )
          {
            ValueN1200SetPoint = 0;
          }
        }
        delay(1);
      }
      
      conversion = (ValueN1200SetPoint - 0) * (20 - 4) / (100 - 0) + 4;//Adjusting scale
      
      Novus.analogWrite(1,conversion); //writes value (in mA) to analog channel 1
        
      StateMachine = RHTClimate;
      break;
    }
    
    //-----------------------------------------------------------------
    //-------------------------- RHTClimate ---------------------------
    //-----------------------------------------------------------------
    case RHTClimate: // RHT_Climate in RS485
    {
      delay(10);
      uint16_t Temperature = 0;
      uint16_t Humidity = 0;
      uint16_t DewPoint = 0;
  
      int MaxBytes_Send = 8;
      int MaxBytes_Receive = 19;
      uint16_t ModbusPDU_send[MaxBytes_Send]={0};       //Array to send to RS485
      uint16_t ModbusPDU_received[MaxBytes_Receive]={0}; //Array to receive from RS485
      
      ModbusPDU_send[0] = 3;    // MODBUS Slave address
      ModbusPDU_send[1] = 3; // MODBUS Function: 3- Read registers
      //Registers: humidity = 0 / temperature = 1 / DewPoint = 6
      ModbusPDU_send[2] = 0;  // High Byte of Starter Register
      ModbusPDU_send[3] = 0;  // Low byte of Starter Register
      ModbusPDU_send[4] = 0;  // High byte of quantity
      ModbusPDU_send[5] = 7;  // Low byte of quantity
      
      //Calculating CRC
      uint16_t u16CRC = getCRC(&ModbusPDU_send[0],6);
      ModbusPDU_send[6] =  (uint8_t) (u16CRC & 0xFF); 
      ModbusPDU_send[7] =  (uint8_t) (u16CRC >> 8);
      
      //          Novus_RS485.communicate(PDU to send, Quantity of bytes sent, PDU to receive, Quantity of bytes to receive);
      int state = Novus_RS485.communicate(&ModbusPDU_send[0], MaxBytes_Send, &ModbusPDU_received[0], MaxBytes_Receive); // Send MODBUS PDU and waits for the answer
      
      if (state==0) // If state=0, no errors found. 
      {
        Humidity = ((uint16_t) ModbusPDU_received[3]<< 8) | (ModbusPDU_received[4]);
        Humidity_RHT = Humidity / 10.0;
        Temperature = ((uint16_t) ModbusPDU_received[7] << 8) | (ModbusPDU_received[8]);
        Temperature_RHT = Temperature / 10.0;
        DewPoint = ((uint16_t) ModbusPDU_received[15] << 8) | (ModbusPDU_received[16]);
        DewPoint_RHT = DewPoint / 10.0;
      }
      if ( Humidity_RHT >= AlarmHumidity_RHT )
      {
        // Alarm occured
        Alarm_RHT = true;
        PeriodBlink_Red = AlarmPeriod;
      }
      else
      {
        // Normally working
        Alarm_RHT = false;
        PeriodBlink_Red = 0;
      }

      StateMachine = PrintValues;
      break;
    }
    
    //---------------------------------------------------------------
    //------------------------- PrintValues -------------------------
    //---------------------------------------------------------------
    case PrintValues: // Print in Serial the values collected
    {
      int ShowMin = 24;
      
      if (MonitorSerial_PlotSerial) // Plot Serial
      {
        //Remember to close plot serial before pass the code
        if ( Plot_N1200 )
        {
          if (Alarm_N1200)
          {
            Serial.print(29);
          }
          else
          {
            Serial.print(ShowMin);
          }
          Serial.print(',');
        }
        
        if ( Plot_TXBlock )
        {
          Serial.print(Temperature_TxBlock);
          Serial.print(',');
          if (Alarm_TxBlock)
          {
            Serial.print(AlarmTemperature_TxBlock);
          }
          else
          {
            Serial.print(ShowMin);
          }
          Serial.print(',');        
        }
        if ( Plot_tcJ )
        {
          Serial.print(temperature_tcJ);
          Serial.print(',');
          if (Alarm_tcJ)
          {
            Serial.print(AlarmTemperature_tcJ);
          }
          else
          {
            Serial.print(ShowMin);
          }
          Serial.print(',');
        }
        if ( Plot_RHT )
        {
          Serial.print(Temperature_RHT);
          Serial.print(',');
          Serial.print(Humidity_RHT);
          Serial.print(',');
          if (Alarm_RHT)
          {
            Serial.print(AlarmHumidity_RHT);
          }
          else
          {
            Serial.print(ShowMin);
          }
          Serial.print(',');
          Serial.print(DewPoint_RHT);
        }
        Serial.println();
      }
      else // Monitor Serial
      {
//        Serial.print("N1200 Alarm: ");
//        Serial.println(Alarm_N1200);
//        Serial.print("N1200 Set point: ");
//        Serial.println(ValueN1200SetPoint);
        Serial.print("Temperature TXBlock: ");
        Serial.println(Temperature_TxBlock,2);
        Serial.print("Temperature TCJ: ");
        Serial.println(temperature_tcJ,2);
        Serial.print("Temperature RHT Climate: ");
        Serial.println(Temperature_RHT);
        Serial.print("Humidity RHT Climate: ");
        Serial.println(Humidity_RHT);
        Serial.print("Dew Point RHT Climate: ");
        Serial.println(DewPoint_RHT);
        Serial.print("\n\n The N1200 SetPoint can be changed by writting in the Serial monitor:\n");
        Serial.println("\t + to increment its value");
        Serial.println("\t - to decrement its value");
        Serial.println("_____________________________________________________________________");
      }
      StateMachine = LEDStandby;
      delay(10);
      break;
    }
  }
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
