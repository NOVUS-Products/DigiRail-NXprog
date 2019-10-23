# NXprog Advanced Input and Output functions

The NXprog core library is compatible with Arduino Advanced IO functions. The code generated to almost all Arduino platforms will run on NXprog without changes. But notice that there are some important differences:

* The frequency for `tone` function must be **smaller than 50 Hz**.
* The `tone` duration **must** always be specified and must be greater than 100.

The output pins are the pins R1 to R4 when relay output type and K1 to K8 when transistor-sourcing type. 
For input pins, the MXprog has up to 8 ports (from D1 to D8).

The number and type of input and output pins vary depending on NXprog model. Please refer to your model's **Instructions Manual**.

Please refer to the function details listed below.

## tone

It generates a square wave of the specified frequency (50 Hz or higher) and a 50% duty cycle on a digital output port. The duration must be specified and the tone can be interrupted by calling to `noTone` function. 

This function will only effective when the output port is configured to `DOUT_PULSE_TRAIN` mode. Please, refer to [DigitalConfiguration](./DigitalConfiguration.md) about digital output modes and parameters.

### Syntax
```C
tone(pin, frequency, duration)
```

### Parameters

**pin**: the name of the digital output pin. In NXprog the pins are `K1` to `K8` or `R1` to `R4` as displayed in NXprog front panel.

**frequency**: The frequency of the tone in Hz. This value must be smaller than 50 Hz.  **Data type**: `unsigned int`.

**duration**: defined duration of a pulse in milliseconds. This value must be between  100 and 65535. **Data type**: `unsigned long`.

### Return
This function doesn't return any value.

## noTone

Stops the generation of a square wave triggered by tone(). It does not affect if the output port is not configured to `DOUT_PULSE_TRAIN` mode.

### Syntax
```C
noTone(pin)
```

### Parameters

**pin**: the name of the digital output pin. In NXprog the pins are `K1` to `K8` or `R1` to `R4` as displayed in NXprog front panel.
