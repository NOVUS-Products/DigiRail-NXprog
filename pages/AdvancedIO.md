# NXprog Advanced Input and Output functions

The NXprog core library is compatible with Arduino Advanced IO functions. The code generated to almost all Arduino platforms will run on NXprog without changes. But notice that there are some important differences:

* The valid frequency for `tone` function are **1 Hz and 5 Hz only**.
* The `tone` duration **must** always be specified and must be greater than 100.

The output pins are the pins R1 to R4 when relay output type and K1 to K8 when transistor-sourcing type. 
For input pins, the NXprog has up to 8 ports (from D1 to D8).

The number and type of input and output pins vary depending on NXprog model. Please refer to your model's **Instructions Manual**.

Please refer to the function details listed below.

## tone

It generates a square wave of the specified frequency of 50% duty cycle on a digital output port. The duration must be specified and the tone can be interrupted by calling to `noTone` function. 

***Important notes***
1. NXprog can only produce 50% duty cycle square waves of 1 Hz and 5 Hz. All other frequencies do not produce any output. The [setActuationMode](./ExpertDigitalOutput.md#setActuationMode) function offers more flexibility.
1. Notice that when executed successfully this function will reconfigure the output port to `_DOUT_PULSE_TRAIN` mode and will remain in this mode until it is reconfigured using one of the functions described in [NOVUS Expert functions for Digital Output](./ExpertDigitalOutput.md). 
1. In NXprog the values for pulse duration are represented in tenths of seconds, therefore, the minimum pulse duration for this function is 100. Values smaller than 100 will not produce any output.
1. The number of pulses generated during the time defined in `duration` must be greater than 1 otherwise no output will be produced.

### Syntax
```C
tone(pin, frequency, duration)
```

### Parameters

**pin**: the name of the digital output pin. In NXprog the pins are `K1` to `K8` or `R1` to `R4` as displayed in NXprog front panel.

**frequency**: The frequency of the tone in Hz. This value must be 1 Hz or 5 Hz.  **Data type**: `unsigned int`.

**duration**: defined duration of a pulse in milliseconds. This value must be between  100 and 65535. **Data type**: `unsigned long`.

### Return
This function doesn't return any value.

## noTone

Stops the generation of a square wave triggered by tone(). It does not affect if the output port is not configured to `_DOUT_PULSE_TRAIN` mode.

### Syntax
```C
noTone(pin)
```

### Parameters

**pin**: the name of the digital output pin. In NXprog the pins are `K1` to `K8` or `R1` to `R4` as displayed in NXprog front panel.
