# NOVUS NXprog port for RTC library

This is a fork of JeeLab's fantastic real-time clock library for Arduino (see https://jeelabs.org/2010/02/05/new-date-time-rtc-library/). It was modified to add support to onboard [NX PCF2127 Accurate RTC with an integrated quartz crystal for industrial
applications](https://www.nxp.com/docs/en/data-sheet/PCF2127.pdf).

This library depends on Wire library that is included in NXprog platform distribution.

## begin

Initializes the communication to the internal RTC. begin() needs to be called before any other RTC library method.

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
