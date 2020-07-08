# NOVUS NXprog Modbus library

This is a port to NXprog from [Arduino Modbus library](https://www.arduino.cc/en/ArduinoModbus/ArduinoModbus) that implements the Modbus RTU (Remote Terminal Unit) protocol over RS485. The APIs are identical to the Arduino version but TCP support is not present. This library supports both Client (master in Modbus terminology) and Server (aka slave).

To know more about Modbus please refer to these documents and sites:
* [Modbus Tutorial from Control Solutions](https://www.csimn.com/CSI_pages/Modbus101.html)
* [Arduino Modbus library](https://www.arduino.cc/en/ArduinoModbus/ArduinoModbus)
* [NOVUS Manuals](https://www.novusautomation.com/site/default.asp?Idioma=1&TroncoID=926290&SecaoID=619163&SubsecaoID=0)

## Language reference
The NXprog Modbus library is an extension of the standard Arduino Modbus and it was designed to be highly compatible with existing code based on the standard library.

To use this library you just need to include the header:
```C
#include <Modbus.h>
```
###Modbus RTU Client Class

In this mode, the NXprog may retrieve and issue commands from/to Server devices attached in RS485 interface. This mode is activated by programming NXprog in ***Bridge*** mode. It differs from the other NXprog modes, namely ***Gateway*** and ***Slave*** (aka Server), and can not be programmed by NXperience. 

  * [begin()](./ModbusClient.md#begin)
  * [end()](./ModbusClient.md#end)
  * [requestFrom()](./ModbusClient.md#requestFrom)
