# NOVUS NXprog RTC library

This is a fork of JeeLab's fantastic real-time clock library for Arduino (see https://jeelabs.org/2010/02/05/new-date-time-rtc-library/). It was modified to add support to NXprog's onboard [NX PCF2127 Accurate RTC with an integrated quartz crystal for industrial
applications](https://www.nxp.com/docs/en/data-sheet/PCF2127.pdf).

This library depends on Wire library that is included in NXprog platform distribution.

**NOTE**: several examples are provided for this library including one to set the date and time. 

## begin

Initializes the communication to the internal RTC. This function must be called before any other RTC library method.

### Syntax
```C
rtc.begin()
```

### Parameters
None

### Return
This function always return `true`.

### Example code
```C
#include <RTC.h>

RTC_PCF2127 rtc;
DateTime _now;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    rtc.begin();
    _now = rtc.now();
}

void loop() {    
    delay(2000);
    _now = rtc.now();
    Serial.print(_now.day());
    Serial.print("/");
    Serial.print(_now.month());
    Serial.print("/");
    Serial.print(_now.year());
    Serial.print(" ");
    Serial.print(_now.hour());
    Serial.print(":");
    Serial.print(_now.minute());
    Serial.print(":");
    Serial.println(_now.second());
}
```

## now

Reads RTC's current date/time.

### Syntax
```C
rtc.now()
```

### Parameters
None

### Return
The current date/time of RTC.  **Data type**: `DateTime` (see below).

```C
class DateTime {
    public:
        DateTime (long t =0);
        DateTime (uint16_t year, uint8_t month, uint8_t day,
                  uint8_t hour =0, uint8_t min =0, uint8_t sec =0);
        DateTime (const char* date, const char* time);    
        uint16_t year() const
        uint8_t  month() const
        uint8_t  day() const
        uint8_t  hour() const
        uint8_t  minute() const
        uint8_t  second() const
        uint8_t  dayOfWeek() const
}
```
**Note**: dayOfTheWeek() ranges from 0 to 6 inclusive with 0 being 'Sunday'.

### Example code
```C
#include <RTC.h>

RTC_PCF2127 rtc;
DateTime _now;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    rtc.begin();
    _now = rtc.now();
}

void loop() {   
    delay(1000);
    _now = rtc.now();
    Serial.println(_now.second());
}
```

## adjust

Set the RTC's date/time.

### Syntax
```C
rtc.adjust(&dt)
```

### Parameters
**dt**: new date/time value. **Data type**: `DateTime` object (see above).

### Return

None

### Example code
In this example, the user sets the new date/time by typing the `epoch` value in Arduino Serial Monitor (you can calculate this value using  [Epoch Converter](https://www.epochconverter.com/))
```C
#include <RTC.h>

RTC_PCF2127 rtc;
DateTime _now;
String epoch; 

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds
    rtc.begin();
    _now = rtc.now();
}

void loop() {
    if(Serial.available() != 0){
        epoch = Serial.readString(); 
        rtc.adjust(DateTime(epoch.toInt()));
    }

    delay(1000);
    _now = rtc.now();
    Serial.print(_now.day());
    Serial.print("/");
    Serial.print(_now.month());
    Serial.print("/");
    Serial.print(_now.year());
    Serial.print(" ");
    Serial.print(_now.hour());
    Serial.print(":");
    Serial.print(_now.minute());
    Serial.print(":");
    Serial.println(_now.second());
}
```

## readnvram
Reads data from the PCF2127's NVRAM.

### Syntax
```C
rtc.readnvram(buf, size, address)
```
### Parameters

**buf**: Pointer to a buffer to store the data - make sure it's large enough to hold size bytes. **Data type**: `uint8_t *`.

**size**: Number of bytes to read. **Data type**: `uint16_t`.

**address**: Starting NVRAM address, from 0 to 511 **Data type**: `uint16_t`.

### Return

None

### Example code

In this example, the user enters the text in Arduino Serial Monitor. This text will be written in RTC NVRAM.

```C
#include <RTC.h>

#define STORAGE_SPACE 20
RTC_PCF2127 rtc;

String userInput;
char contents[STORAGE_SPACE];
int length;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds
    length = 0;
    rtc.begin();
}

void loop() {
    if(Serial.available() != 0){
        userInput = Serial.readString(); 
        length = userInput.length() - 1;
        rtc.writenvram(0, userInput.c_str(), length);
        Serial.print("Bytes read: ");
        Serial.println(length);
    }

    delay(500);
    if(length != 0) {
        rtc.readnvram(contents, length, 0);
        contents[length] = 0;
        Serial.print("Stored length: ");
        Serial.println(length);
        Serial.print("Stored content: ");
        Serial.println(contents);
        length = 0;
    }
}
```
## writenvram
Writes data to the PCF2127's NVRAM.

### Syntax
```C
rtc.writenvram(address, buf, size)
```
### Parameters

**address**: Starting NVRAM address, from 0 to 511 **Data type**: `uint16_t`.

**buf**: Pointer to buffer containing the data to write. **Data type**: `uint8_t *`.

**size**: Number of bytes in buf to write to NVRAM. **Data type**: `uint16_t`.

### Return

None

### Example code

See the example above.

## readBattLowFlag

Reads the battery battery low flag.

### Syntax
```C
rtc.readBattLowFlag()
```
### Parameters

None.

### Return

The battery low indication (`true` when the battery is low).


### Example code
```C
#include <RTC.h>

RTC_PCF2127 rtc;
DateTime _now;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    rtc.begin();
    _now = rtc.now();
}

void loop() {    
    delay(2000);
    _now = rtc.now();
    Serial.print(_now.day());
    Serial.print("/");
    Serial.print(_now.month());
    Serial.print("/");
    Serial.print(_now.year());
    Serial.print(" ");
    Serial.print(_now.hour());
    Serial.print(":");
    Serial.print(_now.minute());
    Serial.print(":");
    Serial.println(_now.second());
    Serial.print("Battery low indication: ");
    Serial.println(rtc.readBattLowFlag());
}
```

## setLowPowerMode

Put the RTC in the lowest power consumption mode. This mode is used to extend battery life spam.

This mode does not affect the normal RTC operations.

### Syntax
```C
rtc.setLowPowerMode()
```
### Parameters

None.

### Return

None.


### Example code
```C
#include <RTC.h>

RTC_PCF2127 rtc;
DateTime _now;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    rtc.begin();
    rtc.setLowPowerMode();
    _now = rtc.now();
}

void loop() {    
    delay(2000);
    _now = rtc.now();
    Serial.println(_now.second());
    Serial.print("Low power mode: ");
    Serial.println(rtc.isInLowPowerModeLowPowerMode());
}
```

## isInLowPowerMode

Checks if the RTC in the lowest power consumption mode.

### Syntax
```C
rtc.isInLowPowerModeLowPowerMode()
```
### Parameters

None.

### Return

This function returns true if the RTC is in the lowest power consumption mode.


### Example code
```C
#include <RTC.h>

RTC_PCF2127 rtc;
DateTime _now;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    rtc.begin();
    _now = rtc.now();
}

void loop() {    
    delay(2000);
    _now = rtc.now();
    Serial.println(_now.second());
    Serial.print("Low power mode: ");
    Serial.println(rtc.isInLowPowerModeLowPowerMode());
}
```
