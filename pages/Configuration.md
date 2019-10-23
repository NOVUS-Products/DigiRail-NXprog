# Novus Configuration retrieve functions
The current NXprog configuration can be retrieved by the object `NovusConfig` using the functions described in follwoing sections.

## getAInConfig

Read the configuration of an analog input pin.

### Syntax
```C
NovusConfiguration.getAInConfig(pin, *output)
```

### Parameters
**pin**: `A1` or `A2` pin.

**output**: current configuration. **Data type**: `ain_cfg_t` as described in [Analog Input configuration data](./AnalogConfiguration.md#analog-input-configuration-data)

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not an analog input or an error occured. **Data type**: `bool`.

## getAOutConfig

Read the current configuration of an analog output pin.

### Syntax
```C
NovusConfiguration.getAOutConfig(const int pin, *output)
```

### Parameters
**pin**: `O1` or `O2` pin.

**output**: current configuration. **Data type**: `aout_cfg_t` as described in [Analog Output configuration data](./AnalogConfiguration.md#analog-output-configuration-data)

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not an analog output or an error occured. **Data type**: `bool`.

## getDInConfig
Read the current configuration of an digital input pin.

### Syntax
```C
NovusConfiguration.getDInConfig(pin, *input)
```

### Parameters
**pin**: `D1` to `D4` pins.

**output**: current configuration. **Data type**: `din_cfg_t` as described in [Digital Input configuration data](./DigitalConfiguration.md#digital-input-configuration-data)

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not an digital input or an error occured. **Data type**: `bool`.

## getDOutConfig

Read the current configuration of an digital output pin.

### Syntax
```C
NovusConfiguration.getDOutConfig(pin, *output);
```

### Parameters
**pin**: `D1` to `D4` pins `K1` to `K8` our , identified as `R1` to `R4` when relay-type digital outputs.

**output**: current configuration. **Data type**: `dout_cfg_t` as described in [Digital Output configuration data](./DigitalConfiguration.md#digital-output-configuration-data)

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not an digital output or an error occured. **Data type**: `bool`.

## getDigiRailFWVersion
Read the current configuration of an digital output pin.

### Syntax
```C
NovusConfiguration.getDigiRailFWVersion(uint16_t *value)
```

### Parameters
**value**: current firmware version. **Data type**: `uint16_t *`.

### Return

This function returns `true` when executed successfully.
