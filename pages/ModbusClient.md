# NOVUS Modbus client

See below the available methods in `ModbusRTUClient` object.

## begin
Starts the Modbus RTU client.
**Important**: the NXprog RS485 **will not** return to the state prior to `start` when the function `end` is used.

### Syntax
```C
begin(baudrate);
begin(baudrate, mode);
```

### Parameters
**badrate**: the baudrate for communication.
**mode**: configuration mode (see valid values in the table below). It will configured in default mode when not informed.

| Value | Configuration     |
| ----- | ---- |
| SERIAL_8O1 | 8 bit, odd parity, 1 stop bit |
| SERIAL_8O2 | 8 bit, odd parity, 2 stop bit |
| SERIAL_8E1 | 8 bit, even parity, 1 stop bit |
| SERIAL_8E2 | 8 bit, even parity, 2 stop bit |
| **SERIAL_8N1** | 8 bit, no parity, 1 stop bit **(this is the dafault mode)** |
| SERIAL_8N2 | 8 bit, no parity, 2 stop bit |



### Return
1 on success, 0 on failure

### Example code
```C
#include <Modbus.h>

#define DEVICE_ID 0x01
#define REGISTER_ADD 0x10

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Modbus RTU Client - Read Holding Register");

  // start the Modbus RTU client
  if (!ModbusRTUClient.begin(9600)) {
    Serial.println("Failed to start Modbus RTU Client!");
    while (1);
  }
}

void loop() {

  Serial.print("Register value: ");
  Serial.println(readRegister(DEVICE_ID, REGISTER_ADD));
  delay(2000);
}

long readRegister(int slave_id, uint16_t holding_register) {

  long result = 0;
  Serial.print("Reading registers ... ");

  if (!ModbusRTUClient.requestFrom(slave_id, HOLDING_REGISTERS, holding_register, 2)) {
    Serial.print("Failed to read register: ");
    Serial.print(holding_register);
    Serial.println(" !");
    Serial.print("Error: ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");
    while (ModbusRTUClient.available()) {
      result = result << 16;
      result += ModbusRTUClient.read();
    }
  }
  return result;
}
```

## end
Stop the client and clean it. 
**Important**: the NXprog RS485 will not be reconfigured to mode it was configured before `start` function.

### Syntax
```C
end();
```

### Parameters
None

### Return
None

## requestFrom
Read the status of multiple coils and discrete inputs and values from multiple holding registers and input registers.
After reading, the application must use `available` and `read` to process the read values.

### Syntax
```C
int requestFrom(int type, int address, int number);
int requestFrom(int slave_id, int type, int address, int number);
```

### Parameters
**slave_id** - id of target, it is 0x00 when not specified
**type** - type of read. Accepted values are: `COILS`, `DISCRETE_INPUTS`, `HOLDING_REGISTERS`, or `INPUT_REGISTERS`
**address** - start address to use for operation
**number** - number of values to read

### Return
0 on failure, number of values read on success

### Example code
See example in begin above.
