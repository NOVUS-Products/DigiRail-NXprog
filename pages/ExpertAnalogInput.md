# NOVUS Expert functions for Analog Input

## setMode
Performs a complete configuration of the operation mode of specified analog input. When this function is successfully executed the analog input will be enabled.

### Syntax
```C
NovusExpertAIn.setMode(pin, type, unit, safeState); 
```

### Parameters
**pin**: `A1` or `A2` pin.

**type**: input type. **Data type**: `nx_ain_sensor_t`. See [Sensor Type](./AnalogConfiguration.md/#sensor-type) definitions.

**unit**: temperature unit. **Data type**: `nx_ain_temp_unit_t`. See [Temperature unit](./AnalogConfiguration.md/#temperature-unit) definitions.

**safeState**: value to be displayed when there is an error in the configured input. **Data type**: `float`.

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.

### Example code
```C
bool ledBlink = true;
int temperatureValue = 0;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    NovusExpertAIn.setMode(A1, tc_T, _CELSIUS, 0);
}

void loop() {
    // read the temperature in value:
    temperatureValue = analogRead(A1);

    Serial.print("sensor = ");
    Serial.println(temperatureValue);

    if(ledBlink)
        ledBlink = false;
    else
        ledBlink = true;

    digitalWrite(LED_BUILTIN, (PinStatus) ledBlink);
  
    delay(2000);
}
```

## setModeLinear
Performs configuration of the operation mode of specified linear analog input. This function only works for linear input type and when the analog input will be enabled when it is successfully executed.

### Syntax
```C
NovusExpertAIn.setModeLinear(pin, type, safeState); 
```

### Parameters
**pin**: `A1` or `A2` pin.

**type**: input type. **Data type**: `nx_ain_sensor_t`. See [Sensor Type](./AnalogConfiguration.md/#sensor-type) definitions.

**safeState**: value to be displayed when there is an error in the configured input. **Data type**: `float`.

### Return
This function returns `true` when executed successfully. It returns false when input type is not linear.  **Data type**: `bool`.

### Example code
```C
bool ledBlink = true;
int temperatureValueA = 0;

void setup() {
    // initialize serial communications at 9600 bps:
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    NovusExpertAIn.setModeLinear(A2, _0_60mV, 0);
}

void loop() {
    // read the analog in value:
    temperatureValueA = analogRead(A2);

    // print the results to the Serial Monitor:
    Serial.print("sensor = ");
    Serial.println(temperatureValueA);

    if(ledBlink)
        ledBlink = false;
    else
        ledBlink = true;
    digitalWrite(LED_BUILTIN, (PinStatus) ledBlink);
  
    delay(2000);
}
```

## setRange
Sets the lower and higher value for the range -65.535 to 65.535 in a linear input (like 0-60mV, 0-5V, etc). 

These are the default range values when the port is configured by function `NovusExpertAIn.setMode`:

Sensor type | Low value | High | Unit
--- | --- | --- | ---
 0 - 60 mV | 0 | 60000 | uV (microvolt)
0 - 5 V | 0 | 5000 | mV (millivolt)
0 - 10V | 0 | 10000 | mV (millivolt)
0 - 20 mA | 0 | 20000 | uA (microampere)
4 - 20 mA | 0 | 20000 | uA (microampere)

### Syntax
```C
NovusExpertAIn.setRange(pin, low, high) 
```

### Parameters
**pin**: `A1` or `A2` pin.

**low**: **Data type**: `uint16_t`.

**high**: **Data type**: `uint16_t`.

### Return
This function returns `true` when executed successfully. It returns `false` when a communication error occurs when the pin is not an input or the input type is a temperature sensor. **Data type**: `bool`.

## setUnit

Configure temperature sensors to use °C or °F units.

### Syntax
```C
NovusExpertAIn.setUnit(pin, unit) 
```

### Parameters
**pin**: `A1` or `A2` pin.

**unit**: temperature unit. **Data type**: `nx_ain_temp_unit_t`. See [Temperature unit](./AnalogConfiguration.md/#temperature-unit) definitions.

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not an analog input or when the analog input is not a temperature sensor. **Data type**: `bool`.

## enFilter

Configure **Time Constant** value of a filter to be applied over the measured input signal. This parameter is used to improve the stability of the measured signal. Adjustable between 0 and 1200 seconds. 

### Syntax
```C
NovusExpertAIn.enFilter(pin, time) 
```

### Parameters
**pin**: `A1` or `A2` pin.

**time**: time constant between 0 and 1200. **Data type**: `int`.

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not an analog input or when the analog input is not a temperature sensor. **Data type**: `bool`.

## setSamplingRate

Set the number of readings performed each second by the analog input channel on the received input signal: 1 reading per second or 10 readings per second.

### Syntax
```C
NovusExpertAIn.setSamplingRate(pin, rate) 
```

### Parameters
**pin**: `A1` or `A2` pin.

**rate**: sampling rate. **Data type**: `nx_ain_sampling_rate_t`,  as defined in [Sampling rate](./AnalogConfiguration.md/#Sampling-rate).

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not an analog input or when the analog input is not a temperature sensor.
**Data type**: `bool`.

## setState

Enables or disables a specified analog input.

### Syntax
```C
NovusExpertAIn.setState(pin, enable) 
```

### Parameters
**pin**: `A1` or `A2` pin.

**enable**: desired state for the pin. **Data type**: `bool`.

### Return
This function returns `true` when executed successfully.
**Data type**: `bool`.

