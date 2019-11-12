# NXprog Analog Input and Output functions
The NXprog core library is compatible with Arduino Standard functions. The code generated to almost all Arduino platforms will run on NXprog without changes. But to use this platform to its full potential, some small details need to be observed.

## analogRead
Reads the value from the specified analog pin. NXprog provides 2 analog inputs for both Ramix RL and DO models. 
For temperature sensors, this function truncates the reading to integer values. It takes about 30 milliseconds (0.03 s) to read an analog input, so the maximum reading rate is about 30 times a second. Check the analog input sampling rate in the NXprog manual. 
Please refer to the NXprog manual for information about resolution and precision.
The input type can be modified using the NOVUS Expert function `NovusExpertAIn.setMode` and verified using `NovusConfig.getAInConfig` function.

### Syntax
```C
analogRead(pin)
```

### Parameters
**pin**: the name of the analog input pin to read from. In NXprog the pins are A1 and A2 as displayed in the NXprog front panel.

### Return
The analog reading on the pin. The value return depends on the pin's (channel) configuration. Refer to [AnalogConfiguration](./AnalogConfiguration.md) about analog input sensors and modes. **Data type**: `int32_t`. The return type differs from the default Arduino definition for this function but is required to comply with NXprog higher resolution. For temperature sensors, this value may be negative.

The output value unit will depend on the configured [sensor type](./AnalogConfiguration.md#sensor-type) (temperature or linear sensor). See tables below.

Linear sensor |  Unit | Output Value Range
--- | --- | ---
0 - 60 mV | uV (microvolt) | 0 - 60000
0 - 5 V | mV (millivolt)  | 0 - 5000
0 - 10V | mV (millivolt) | 0 - 10000
0 - 20 mA | uA (microampere) | 0 - 20000
4 - 20 mA | uA (microampere) | 4000 - 20000


Temperature sensor |  Unit | Output Value Range
--- | --- | ---
 (all types) | 0.1 Celsius or 0.1 Fahrenheit | (refer to the sensor specifications)

### Example code
```C
bool ledBlink = true;
int32_t intValueA1;
double temperature;

// Commands
String command; 
char command_buf[80];

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    NovusExpertAIn.setMode(A1, tc_T, _CELSIUS, 0);   // configure port A1. 
}

void loop() {
    // read the analog in value:
    intValueA1 = analogRead(A1);

    // print the results to the Serial Monitor:
    Serial.print("temperature sensor A1 = ");
    temperature = intValueA1 / 10;
    Serial.println(temperature);

    if(ledBlink)
        ledBlink = false;
    else
        ledBlink = true;
    digitalWrite(LED_BUILTIN, (PinStatus) ledBlink);
  
    delay(2000);
}
```

## analogWrite
Writes an analog value to a pin. NXprog models Ramix RL and DO offers 2 channels of analog output with three types of signals:
- 0-20 mA 
- 4-20 mA
- 0-10 V

The output type can be modified using the NOVUS Expert function [`NovusExpertAOut.setMode`](./ExpertAnalogInput.md#setmode).
After a call to this function, the pin will keep the same configuration until the next call. 

### Syntax
```C
analogWrite(pin, value)
```

### Parameters
**pin**: the name of the analog output pin to write to. In NXprog the pins are O1 and O2 as labeled in the NXprog front panel.

**value**: the 16-bit value will depend on the current configuration of the pin (channel). Refer to [Analog Output configuration data](./AnalogConfiguration.md#analog-output-configuration-data) about analog output types.

### Return
This function does not return any value.


## analogReference
This function is not used in NXprog since the analog inputs have far more possibilities than a regular Arduino board. Please, refer to [AnalogConfiguration](./AnalogConfiguration.md) about analog configuration.
