# NOVUS Expert functions for Analog Output

## setMode
Performs a complete configuration of the operation mode of a specified analog output. When this function is successfully executed the analog output will be enabled.

### Syntax
```C
NovusExpertAIn.setMode(pin, type, range, poweronState, poweronValue, watchdogValue) 
```

### Parameters
**pin**: the name of the analog output pin to read from. In NXprog the pins are `O1` and `O2` as displayed in NXprog front panel. 

**type**: output type. **Data type**: `nx_aout_type_t` as defined [here](./AnalogConfiguration.md#output-type).

**range**: set the operating range of the analog output (percent or range). Refer to [Analog Configuration](./AnalogConfiguration.md). **Data type**: `nx_aout_range_t`. See [Operating range definition](./AnalogConfiguration.md#operating-range).

**poweronState**:  set a initial value for the analog output when turning on the device and receiving a command. **Data type**: `nx_aout_poweron_state_t`. See the values defined for  [Power on state](./AnalogConfiguration.md#poweron-state).

**poweronValue**: value to be adopted in the Initial Value parameter after the device initialization and until a valid command is received. **Data type**: `uint16_t`.

**watchdogValue**:  value for the analog output in case of loss of RS485/Ethernet communication. **Data type**: `uint16_t`.

### Return
This function returns `true` when executed successfully.
**Data type**: `bool`.

## setState
Enables or disables a specified analog output.

### Syntax
```C
NovusExpertAIn.setState(pin, enable) 
```

### Parameters
**pin**: `O1` or `O2` pin.

**enable**: desired state for the pin. **Data type**: `bool`.

### Return
This function returns `true` when executed successfully.
**Data type**: `bool`.

## setPowerOnValue
Sets the value to be adopted in the Initial Value parameter after the device initialization and until a valid command is received.

### Syntax
```C
NovusExpertAIn.setPowerOnValue(pin, value) 
```

### Parameters
**pin**: `O1` or `O2` pin.

**value**: power on value for the pin. **Data type**: `uint16_t`.

### Return
This function returns `true` when executed successfully.
**Data type**: `bool`.

## setSafeValue
Sets a value for the analog output in case of loss of RS485/Ethernet communication. 

### Syntax
```C
NovusExpertAIn.setSafeValue(pin, value) 
```

### Parameters
**pin**: `O1` or `O2` pin.

**value**: safe value for the pin. **Data type**: `uint16_t`.

### Return
This function returns `true` when executed successfully. 
**Data type**: `bool`.

## setPowerOnState
Set an initial value for the analog output when turning on the device and receiving a command. 

```C
NovusExpertAIn.setPowerOnState(pin, value) 
```

### Parameters

**pin**: `O1` or `O2` pin.

**value**: power on state the pin. **Data type**: `nx_aout_poweron_state_t`.  See the values defined for  [Power on state](./AnalogConfiguration.md#poweron-state).

### Return
This function returns `true` when executed successfully. 

**Data type**: `bool`.
