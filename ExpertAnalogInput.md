## analogInput_setRange
Performs complete configuration of the operation mode of a specified analog input. When this function is successfully executed the analog input will be enabled.

## analogInput_setMains
Set the working frequency of the mains (50Hz or 60Hz).

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
