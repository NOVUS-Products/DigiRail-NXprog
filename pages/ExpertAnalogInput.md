# NOVUS Expert functions for Analog Input

## setMode
Performs a complete configuration of the operation mode of specified analog input. When this function is successfully executed the analog input will be enabled.

### Syntax
```C
NovusExpertAIn.setMode(pin, type, unit, safeValue); 
```

### Parameters
**pin**: `A1` or `A2` pin.

**type**: input type. **Data type**: `nx_ain_sensor_t`. See [Sensor Type](./AnalogConfiguration.md/#sensor-type) definitions.

**unit**: temperature unit. **Data type**: `nx_ain_temp_unit_t`. See [Temperature unit](./AnalogConfiguration.md/#temperature-unit) definitions.

**safeValue**: value to be displayed when there is an error in the configured input. **Data type**: `int32_t`. For temperature sensors, this value may be negative.

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.

### Example code
```C
bool ledBlink = true;
int32_t temperatureValue = 0;

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

This function also sets the lower and higher value for the range -65.535 to 65.535 for the linear input (like 0-60mV, 0-5V, etc). 

These are the default range values:

Sensor type | Low value | High | Unit
--- | --- | --- | ---
 0 - 60 mV | 0 | 60000 | uV (microvolt)
0 - 5 V | 0 | 5000 | mV (millivolt)
0 - 10V | 0 | 10000 | mV (millivolt)
0 - 20 mA | 0 | 20000 | uA (microampere)
4 - 20 mA | 4000 | 20000 | uA (microampere)

When the port is configured by function `NovusExpertAIn.setMode` it assumes one of pair above.

### Syntax
```C
NovusExpertAIn.setModeLinear(pin, type, safeValue, low, high); 
```

### Parameters
**pin**: `A1` or `A2` pin.

**type**: input type. **Data type**: `nx_ain_sensor_t`. See [Sensor Type](./AnalogConfiguration.md/#sensor-type) definitions.

**safeValue**: value to be displayed when there is an error in the configured input. **Data type**: `int32_t`. 

**low**: low value for the range. **Data type**: `int32_t`.

**high**: high value for the range. **Data type**: `int32_t`.

### Return
This function returns `true` when executed successfully. It returns false when input type is not linear.  **Data type**: `bool`.

### Example code
```C
bool ledBlink = true;
int32_t linearValueA2 = 0;

void setup() {
    // initialize serial communications at 9600 bps:
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    NovusExpertAIn.setModeLinear(A2, _0_60mV, 0, 0, 60000);
}

void loop() {
    // read the analog in value:
    linearValueA2 = analogRead(A2);

    // print the results to the Serial Monitor:
    Serial.print("sensor = ");
    Serial.println(linearValueA2);

    if(ledBlink)
        ledBlink = false;
    else
        ledBlink = true;
    digitalWrite(LED_BUILTIN, (PinStatus) ledBlink);
  
    delay(2000);
}
```

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

### Example code
```C
bool ledBlink = true;
ain_cfg_t   conf_AI;
int state = 1;
// Commands
String command; 
char command_buf[80];

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds
    NovusExpertAIn.setMode(A1, tc_T, _CELSIUS, 0);
}

void loop() {
    if(Serial.available() != 0){
        command = Serial.readString(); 
        command.toCharArray(command_buf, sizeof(command_buf));
        state = atoi(command_buf);
        if (state == 0)
            NovusExpertAIn.setState(A1, false);   
        else
            NovusExpertAIn.setState(A1, true);   
    }
    NovusConfig.getAInConfig(A1, &conf_AI);
    Serial.println(">>>>>>>>>>>>><<<<<<<<<<<<<<");
    Serial.println("ANALOG INPUT 1 CONFIGURATION");
    Serial.print("  Enabled: ");
    Serial.println(conf_AI.enabled);
  
    if(ledBlink)
        ledBlink = false;
    else
        ledBlink = true;

    digitalWrite(LED_BUILTIN, (PinStatus) ledBlink);
  
    delay(2000);
}
```

## setSafeVaslue
Configures the value to be displayed when there is an error in the configured input.

### Syntax
```C
NovusExpertAIn.setSafeValue(pin, safeValue); 
```

### Parameters
**pin**: `A1` or `A2` pin.

**safeValue**: value to be displayed when there is an error in the configured input. **Data type**: `int32_t`. For temperature sensors, this value may be negative.

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.

### Example code
```C
bool ledBlink = true;
int32_t temperatureValue = 0;
int32_t safeValue = 0;
// Commands
String command; 
char command_buf[80];

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds
    NovusExpertAIn.setMode(A1, tc_T, _CELSIUS, 0);
}

void loop() {
    if(Serial.available() != 0){
        // user enter the new safe value (negative values are accepted)
        command = Serial.readString(); 
        command.toCharArray(command_buf, sizeof(command_buf));
        safeValue = atol(command_buf);
        NovusExpertAIn.setSafeValue(A1, safeValue);   
    }
  
    // read the temperature in value:
    temperatureValue = analogRead(A1);

    Serial.print("sensor A1 = ");
    Serial.println(temperatureValue);

    if(ledBlink)
        ledBlink = false;
    else
        ledBlink = true;

    digitalWrite(LED_BUILTIN, (PinStatus) ledBlink);
  
    delay(2000);
}
```
