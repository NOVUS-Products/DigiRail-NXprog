## analogOutput_setMode
Performs complete configuration of the operation mode of a specified analog output. When this function is successfully executed the analog output will be enabled.

### Syntax
```C
analogOutput_setMode(pin, type, range, poweronState, poweronValue, watchdogValue) 
```

### Parameters
**pin**: the name of the analog output pin to read from. In NXprog the pins are `O1` and `O2` as displayed in NXprog front panel. 

**type**: Data type: `nx_aout_type_t`

**range**: set the operating range of the analog output (percent or range. Refer to [Analog Configuration](./AnalogConfiguration.md). Data type: `nx_aout_range_t`.

**poweronState**:  set a initial value for the analog output when turning on the device and receiving a command. The values are defined in  [Analog Configuration](./AnalogConfiguration.md) documentation. Data type: `nx_aout_poweron_state_t`.

**poweronValue**: value to be adopted in the Initial Value parameter after the device initialization and until a valid command is received. Data type: `uint16_t`.

**watchdogValue**:  value for the analog output in case of loss of RS485/Ethernet communication. Data type: `uint16_t`.

### Return
This function returns `true` when executed successfully.
**Data type**: `bool`.

## analogOutput_setState
Enables or disables a specified analog output.

### Syntax
```C
analogOutput_setState(pin, enable) 
```

### Parameters
**pin**: `O1` or `O2` pin.

**enable**: desired state for the pin. Data type: `bool`.

### Return
This function returns `true` when executed successfully.
**Data type**: `bool`.

## analogOutput_setPowerOnValue
Sets the value to be adopted in the Initial Value parameter after the device initialization and until a valid command is received.

### Syntax
```C
analogOutput_setPowerOnValue(pin, value) 
```

### Parameters
**pin**: `O1` or `O2` pin.

**value**: power on value for the pin. Data type: `uint16_t`.

### Return
This function returns `true` when executed successfully.
**Data type**: `bool`.

## analogOutput_setSafeValue
Sets a value for the analog output in case of loss of RS485/Ethernet communication. 

### Syntax
```C
analogOutput_setSafeValue(pin, value) 
```

### Parameters
**pin**: `O1` or `O2` pin.

**value**: safe value for the pin. Data type: `uint16_t`.

### Return
This function returns `true` when executed successfully. 

**Data type**: `bool`.

## analogOutput_setPowerOnState
Set a initial value for the analog output when turning on the device and receiving a command. 

```C
analogOutput_setPowerOnState(pin, value) 
```

### Parameters

**pin**: `O1` or `O2` pin.

**value**: power on state the pin. Data type: `nx_aout_poweron_state_t`. See values defined in [Analog Configuration](./AnalogConfiguration.md) document.

### Return
This function returns `true` when executed successfully. 

**Data type**: `bool`.

## analogInput_setRange
Set lower and higher value for the range -65.535 to 65.535 in a linear input (like 0-60mV, 0-5V etc) . 

These are the default range values when the port is configured by function `analogInput_setMode`:

Sensor type | Low value | High | Unit
--- | --- | --- | ---
 0 - 60 mV | 0 | 60000 | uV (microvolt)
0 - 5 V | 0 | 5000 | mV (millivolt)
0 - 10V | 0 | 10000 | mV (millivolt)
0 - 20 mA | 0 | 20000 | uA (microampere)
4 - 20 mA | 0 | 20000 | uA (microampere)

### Syntax
```C
analogInput_setRange(pin, low, high) 
```

### Parameters
**pin**: `A1` or `A2` pin.

**low**: Data type: `uint16_t`.

**high**: Data type: `uint16_t`.

### Return
This function returns `true` when executed successfully. It returns `false` when a communication error occurs, when the pin is not a input or the input type is a temperature sensor.

**Data type**: `bool`.

## analogInput_setUnit

Configure temperature sensors to use °C or °F units.

### Syntax
```C
analogInput_setUnit(pin, unit) 
```

### Parameters
**pin**: `A1` or `A2` pin.

**unit**: temperature unit. Data type: `nx_ain_temp_unit_t`.

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not a analog input or when the analog input is not a temperature sensor.
**Data type**: `bool`.

## analogInput_enFilter
Configure **Time Constant** value of a filter to be applied over the measured input signal. Parameter used to improve the stability of the measured signal. Adjustable between 0 and 1200 seconds. 
### Syntax
```C
analogInput_enFilter(pin, time) 
```

### Parameters
**pin**: `A1` or `A2` pin.

**time**: time constant between 0 and 1200. Data type: `int`.

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not a analog input or when the analog input is not a temperature sensor.
**Data type**: `bool`.

## analogInput_setSamplingRate
Set the number of readings performed each second by the analog input channel on the received input signal: 1 reading per second or 10 readings per second.

### Syntax
```C
analogInput_setSamplingRate(pin, rate) 
```

### Parameters
**pin**: `A1` or `A2` pin.

**rate**: sampling rate. Data type: `nx_ain_sampling_rate_t`, see below.

Type | Value 
--- | --- 
`_1_per_sec` | 0
`_10_per_sec` | 1 

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not a analog input or when the analog input is not a temperature sensor.
**Data type**: `bool`.
