## analogRead
Reads the value from the specified analog pin. NXprog provides 2 analog inputs for both Ramix RL and DO models. 
For temperature sensors, this function truncates the reading to integer values. It takes about 30 milliseconds (0.03 s) to read an analog input, so the maximum reading rate is about 30 times a second. Check analog input sampling rate in NXprog manual. 
Please refer to NXprog manual for information about resolution and precision.
The input type can be modified using the NOVUS Expert function `NovusExpert.analogInput_setMode` and verified using `NovusConfig.getAIConfig` function.

### Syntax
```C
analogRead(pin)
```

### Parameters
**pin**: the name of the analog input pin to read from. In NXprog the pins are A1 and A2 as displayed in NXprog front panel.

### Return
The analog reading on the pin. The value return depends on the pin's (channel) configuration. Refer to [AnalogConfiguration](./AnalogConfiguration.md) about analog input sensors and modes.

**Data type**: `uint32_t`. The return type differs from default Arduino definition for this function but is required to comply with NXprog higher resolution.


## analogWrite
Writes an analog value to a pin. NXprog models Ramix RL and DO offers 2 channels of analog output with three types of signals:
- 0-20 mA 
- 4-20 mA
- 0-10 V

The output type can be modified using the NOVUS Expert function `NovusExpert.analogOutput_setMode` described in [NOVUS Expert](ExpertAnalogIO.md).
After a call to this function, the pin will keep the same configuration until the next call. 

### Syntax
```C
analogWrite(pin, value)
```

### Parameters
**pin**: the name of the analog input pin to write to. In NXprog the pins are O1 and O2 as labeled in NXprog front panel.

**value**: the 16-bit value will depend on the current configuration of the pin (channel). Refer to [AnalogConfiguration](./AnalogConfiguration.md) about analog output types.

### Return
This function does not return any value.
