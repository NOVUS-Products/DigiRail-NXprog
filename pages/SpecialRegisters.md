# Modbus registers accessible from Arduino application

NXprog implements a set of 16-bit registers for Arduino application usage. These registers are accessible by Modbus protocol using the Ethernet or RS-485 connection. These registers provide a simple but efficient way to share information between any system control and data
acquisition (SCADA) and an Arduino application running in NXprog.

These registers will be available when NXprog is configured as Slave. This will allow that any external application configured as Modbus Master have access to these register using the commands:
* **READ HOLDING REGISTERS** (0x03)
* **WRITE HOLDING REGISTERS** (0x06)
* **WRITE MULTIPLE HOLDING REGISTERS** (0x16)

The range of available registers is from Modbus address 400 to 499. The Arduino application uses the same address range using the functions implemented in `SpecialRegisters` class as described below.

## writeSingleRegister

Writes a new value to a designated register.

### Syntax
```C
writeSingleRegister(address, value)
```

### Parameters
**address**: Modbus register address (value from 400 to 499). **Data type**: `uint16_t`

**value**: value to be stored. **Data type**: `uint16_t`.

### Return

This function returns `true` when executed successfully. It returns `false` if the address is out of range or an error occurred. **Data type**: `bool`.

### Example code
```C
SpecialRegisters reg;
uint16_t counter = 0;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    reg.writeSingleRegister(400, counter);  // change register 400 every second
    counter++;
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    Serial.print("Counter: ");
    Serial.println(counter);
}
```

## readSingleRegister

Reads the new value from a register.

### Syntax
```C
readSingleRegister(address, &value)
```

### Parameters
**address**: Modbus register address (value from 400 to 499). **Data type**: `uint16_t`

**value**: value read. **Data type**: `uint16_t *`.

### Return

This function returns `true` when executed successfully. It returns `false` if the address is out of range or an error occurred. **Data type**: `bool`.

### Example code
```C
SpecialRegisters reg;
uint16_t value = 0;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    delay(500);
    reg.readSingleRegister(400, &value);  // read value every 0.5  second
    // turn on LED based on value
    if(value == 0)
        digitalWrite(LED_BUILTIN, LOW);
    else
        digitalWrite(LED_BUILTIN, HIGH);
}
```
