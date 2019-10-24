# NOVUS Expert functions for Digital Input

## setMode
Configure the digital input to a valid operating mode. The digital input will be enabled when this function succeeds.


### Syntax
```C
NovusExpertDIn.setMode(pin, function, connection_type, debounce, preset)
```

### Parameters
**pin**: the name of the digital input pin to read from. In NXprog the pins are `D1` to `D8` as displayed on the front panel.

**function**: the function to be performed by the digital input.**Data type**: `nx_din_function_t` as defined in [Function type](./DigitalConfiguration.md/#Function-type). 

**connection_type**: the type of sensor to be used. **Data type**: `nx_din_type_t` as defined in [Connection type](./DigitalConfiguration.md/#Connection-type). 

**debounce**: the time to be disregarded by the counter after detecting the edge at the input. Functionality available when selecting
the sensor type Dry Contact. Interval limited to 10 s (10 000 ms) maximum.**Data type**: `uint16_t`.

**preset**: the initial value for the rising edge, falling edge, and integrator ON/OFF counter. **Data type**: `uint32_t`.

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.


## setFunctionMode
Configure the digital input for one of the pre-defined functions as listed below. The digital input will be enabled when this function succeeds.

### Syntax
```C
NovusExpertDIn.setFunctionMode(pin, function) 
```

### Parameters
**pin**: the name of the digital input pin to read from. In NXprog the pins are `D1` to `D8` as displayed on the front panel.

**function**: **Data type**: `nx_din_function_t` as defined in [Function type](./DigitalConfiguration.md/#Function-type).

### Return
This function returns `true` when executed successfully.
**Data type**: `bool`.

## setState
Enables or disables a specified digital input.

### Syntax
```C
NovusExpertDIn.setState(pin, enable) 
```

### Parameters
**pin**: `D1` to `D4` pin.

**enable**: desired state. **Data type**: `bool`.

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.


## setConnectionType

Sets the type of sensor to be used in a digital input.  The digital input will be enabled when this function succeeds.

### Syntax
```C
NovusExpertDIn.setConnectionType(pin, connection_type)
```

### Parameters
**pin**: the name of the digital input pin to read from. In NXprog the pins are `D1` to `D8` as displayed on the front panel.

**connection_type**: the type of sensor to be used. **Data type**: `nx_din_type_t` as defined in [Connection type](./DigitalConfiguration.md/#Connection-type). 

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.

## setDebounce

It sets the time to be disregarded by the counter after detecting the edge at the input. Functionality available when selecting
the sensor type Dry Contact. Interval limited to 10 s (10 000 ms) maximum. The digital input will be enabled when this function succeeds.

### Syntax
```C
NovusExpertDIn.setDebounce(pin, debounce)
```

### Parameters
**pin**: the name of the digital input pin to read from. In NXprog the pins are `D1` to `D8` as displayed on the front panel.

**debounce**: the time to be disregarded.**Data type**: `uint16_t`.

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.

## readCounter
Reads counter value for digital input, when it's set as a Counter, that is in mode `DIN_COUNTER_NEG_EDGE` or `DIN_COUNTER_POS_EDGE` as defined in [Function type](./DigitalConfiguration.md/#Function-type).

### Syntax
```C
NovusExpertDIn.readCounter(pin)
```

### Parameters
**pin**: the name of the digital input pin to read from. In NXprog the pins are `D1` to `D8` as displayed on the front panel.

### Return
This function returns the current value of the counter when executed successfully and `NX_INVALID_COUNTER` otherwise. **Data type**: `uint32_t`.

## readTimer

Read timer register if digital input mode is set as Timer Counter, that is in mode `DIN_INTEGRATOR` as defined in [Function type](./DigitalConfiguration.md/#Function-type).

### Syntax
```C
NovusExpertDIn.readTimer(pin, onoff)
```

### Parameters
**pin**: the name of the digital input pin to read from. In NXprog the pins are `D1` to `D8` as displayed on the front panel.

**onoff**:  `false` to retrieve time in OFF state, `false` for time in ON state.**Data type**: `bool`.

### Return
This function returns the current time in the state defined in `onoff` parameter when executed successfully and `NX_INVALID_TIME` otherwise. **Data type**: `uint32_t`.
