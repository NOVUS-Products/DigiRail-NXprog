# NXprog Digital Input and Output functions

The NXprog core library is compatible with Arduino Standard functions. The code generated to almost all Arduino platforms will run on NXprog without changes. But there are some important differences:

* There are different pins for Output and Input.
* The Input and Output modes are more flexible than those defined in Arduino  Standard functions. To operate in NXprog full potential the ports must be configured by `NovusExpertDIn`, `NovusExpertDOut`, `NovusExpertAIn`, and `NovusExpertAOut` functions.

The output pins are the pins R1 to R4 when relay output type and K1 to K8 when transistor-sourcing type. 
For input pins, the MXprog has up to 8 ports (from D1 to D8).

The number and type of input and output pins vary depending on the NXprog model. Please refer to your model's **Instructions Manual**.

Please refer to the function details listed below.

## pinMode
This function is not used in NXprog since the pins are used exclusively for input or output. 

## digitalRead
This function behaves exactly as described in [Arduino digital Read function](<https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/>).

The input operation mode can be modified using the NOVUS Expert function `NovusExpertDIn.setMode` described in [NOVUS Expert](./ExpertDigitalInput.md#setmode) and verified using `NovusConfig.getDInConfig` function.

### Syntax
```C
digitalRead(pin)
```

### Parameters
**pin**: the name of the digital input pin to read from. In NXprog the pins are D1 to D8 as displayed in the NXprog front panel.

### Return
The current pin state, `HIGH` or `LOW`.

**Data type**: `uint32_t`. The return type differs from the default Arduino definition for this function but is required to comply with NXprog higher resolution.


## digitalWrite
Writes a value to a pin. NXprog models offer up to 8 digital output channels.

The output type can be modified using the NOVUS Expert function `NovusExpertDOut.setMode` described in [NOVUS Expert](./ExpertDigitalOutput.md#setmode).

### Syntax
```C
digitalWrite(pin, value)
```

### Parameters
**pin**: the name of the digital output pin to write to. In NXprog the pins are R1 to R4 or K1 to K8 as labeled in the NXprog front panel.

**value**: `HIGH` or `LOW` 

### Return
This function does not return any value.

## turnOffPWM

This function is not supported in NXprog.