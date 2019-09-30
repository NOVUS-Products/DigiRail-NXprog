## digitalInput_setFunctionMode
Configure the digital input for one of the pre-defined function as listed below.

Mode | Comment
--- | --- 
 Logical Status | Level is converted to the logic states 0 and 1. 
Counter Positive Edge |  Allows the digital input to count the number of pulses received at its terminals. The counter is incremented in the rising edge (transition from 0 to 1) of the received pulse. 
Counter Negative Edge |  The same as above for the falling edge (transition from 1 to 0) of the received pulse. 
Integrator ON/OFF |  Allows the sum (integration) of the time intervals measured with the digital input in logic state 0 to be performed and also the sum of the time intervals measured with the digital input in the logical state 1. It will provide the two information separately. Value displayed in seconds. 

### Syntax
```C
digitalInput_setFunctionMode(pin, function) 
```

### Parameters
**pin**: the name of the analog output pin to read from. In NXprog the pins are `D1` to `D8` as displayed in NXprog front panel.

**function**: Data type: `nx_din_function_t;`

### Return
This function returns `true` when executed successfully.
**Data type**: `bool`.
