# NXprog onboard EEPROM library
Arduino Library for NXprog onboard [Microchip 24LC256 256K I2C CMOS Serial EEPROM](http://ww1.microchip.com/downloads/en/devicedoc/21203m.pdf).
This is a fork from [Gonçalo Passos library](https://github.com/gngz/24LC256-Arduino-Library/wiki).


## writeByte

Writes a byte into EEPROM cell address.

### Syntax
```C
eeprom.writeByte(address, data)
```

### Parameters
**address**: cell address. **Data type**: `uint16_t`. 

**data**: information to write into the memory.**Data type**: `byte`. 

### Return

This function returns the operation status. The return values are `WRITE_SUCCESS` or `WRITE_ERROR`.


### Example code
In this example, the value user types in Arduino Serial Monitor will be written in cell 42 of EEPROM.

```C
#include <EEPROM.h>

E24LC256 eeprom;
String strCounter;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds

}

void loop() {
    if(Serial.available() != 0){
        strCounter = Serial.readString(); 
        eeprom.writeByte(42, strCounter.toInt());
    }

    delay(5000);
    Serial.print("Cell 42: ");
    Serial.println(eeprom.readByte(42));
}
```

## readByte

Reads a byte from EEPROM cell address.

### Syntax
```C
eeprom.readByteByte(address)
```

### Parameters
**address**: cell address. **Data type**: `uint16_t`. 

### Return

This function returns the data stored in the memory.**Data type**: `byte`. 

### Example code
See the example above.


## updateByte

Updates a byte in the EEPROM cell address. Write operation is performed only when stored value is different. This will save EEPROM memory write cycles.

### Syntax
```C
eeprom.updateByte(address, data)
```

### Parameters
**address**: cell address. **Data type**: `uint16_t`. 

**data**: information to be written into the memory.**Data type**: `byte`. 

### Return

This function returns the operation status. The return values are `WRITE_SUCCESS` or `WRITE_ERROR`.

### Example code
```C
#include <EEPROM.h>

E24LC256 eeprom;
String strCounter;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds

}

void loop() {
    if(Serial.available() != 0){
        strCounter = Serial.readString(); 
        eeprom.updateByte(42, strCounter.toInt());
    }

    delay(5000);
    Serial.print("Cell 42: ");
    Serial.println(eeprom.readByte(42));
}
```

## writePage

Writes up to 64 bytes into the EEPROM page address.

### Syntax
```C
eeprom.writePage(address, size, &buffer)
```

### Parameters
**address**: starting address of the page. **Data type**: `uint16_t`. 

**size**: number of bytes to be written. **Data type**: `int`. 

**buffer**: information to be written into the memory.**Data type**: `byte *`. 

### Return

This function returns operation status. The return values are `WRITE_SUCCESS` or `WRITE_ERROR`.

### Example code
In this example, the string that the user types in Arduino Serial Monitor will be written in EEPROM.

```C
#include <EEPROM.h>

E24LC256 eeprom;
String userInput;
int length;
char stored_string[64];

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds
    length = 0;

}

void loop() {
    if(Serial.available() != 0){
        userInput = Serial.readString(); 
        length = userInput.length();
        eeprom.writePage(42, length, userInput.c_str());
    }

    delay(500);
    if(length != 0) {
        eeprom.readPage(42, length, stored_string);
        stored_string[length] = 0;
        Serial.print("Stored length: ");
        Serial.println(length-1);
        Serial.print("Stored content: ");
        Serial.println(stored_string);
        length = 0;
    }
}
```

## readPage

Reads multiple EEPROM cell address's and saves into a buffer.

### Syntax
```C
eeprom.readPage(address, size, &buffer)
```

### Parameters
**address**: starting address of the page. **Data type**: `uint16_t`. 

**size**: number of bytes to be read. **Data type**: `int`. 

**buffer**: address of the buffer.**Data type**: `byte *`. 

### Return

This function returns the number of bytes read or `WRITE_ERROR` if it didn't succeed.

### Example code
See the example above.

## length

Returns EEPROM maximum storage in bytes.

### Syntax
```C
eeprom.length()
```

### Parameters
None.

### Return

This function returns the storage size in bytes.

### Example code
```C
#include <EEPROM.h>

E24LC256 eeprom;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {

    delay(2000);
    Serial.print("EEPROM size: ");
    Serial.println(eeprom.length());
}
```

