## Analog Input configuration data
Identified as A1 and A2, on its front panel. The configuration of an analog input channel can be read using the functions `NovusConfig.getAInConfig`.
This function return `ain_cfg_t` data structure defined in `novus/nx_config.h` with the following members:

Member | Type | Comment
--- | --- | ---
 enabled | `bool` | channel is enabled/disabled
type | `nx_ain_sensor_t` | Sensor type
unit | `nx_ain_temp_unit_t` | Temperature unit
scale_bottom | `uint32_t` | Input range (scale bottom)
scale_top | `uint32_t` | Input range (scale top)
sampling_rate | `nx_ain_sampling_rate_t` | Sampling rate

These channels are suitable for measuring temperature or any other values represented by standard linear electrical signals. `unit` member is used when the selected `type` is a temperature sensor like Pt100, type J, type K, etc. Refer to NXprog Instruction Manual about supported types.

For more details, please refer to the NXprog manual.

### Sensor type
The possible input types are defined by the constants below. 
* Temperature Sensors:
  * `tc_J`: type J
  * `tc_K`: type K
  * `tc_T`: type T
  * `tc_E`: type E
  * `tc_N`: type N
  * `tc_R`: type R
  * `tc_S`: type S
  * `tc_B`: type B
  * `Pt100`: type Pt100
  * `Pt1000`: type Pt1000
  * `NTC`: type NTC
* Linear Analog Signals
  * `_0_60mV`
  * `_0_5V`
  * `_0_10V`
  * `_0_20mA`
  * `_4_20mA`

For details about connecting sensors and measuring ranges, please refer to NXprog Instruction Manual.

### Temperature unit
This setting is required when the sensor is one of the Temperature Sensors group in Sensor type. The allowed values for this member are:
* `_CELSIUS`
* `_FAHRENHEIT`

### Input range
This measurement range is required when the sensor is one of the Linear Analog Signals group in Sensor type.

### Sampling rate
Defines the number of readings performed each second by the analog input channel as defined the constants: 
* `_1_per_sec`
* `_10_per_sec`

## Analog Output configuration data
Identified as O1 and O2 as labeled on the NXprog front panel. The configuration of an analog output channel can be read using the functions `NovusConfig.getAOutConfig` and set using the function `NovusExpert.analogOutput_setMode`.
This function return `dout_cfg_t` data structure defined in `novus/nx_config.h` with the following members:

Member | Type | Comment
--- | --- | ---
 enabled | `bool` | channel is enabled/disabled
type | `nx_aout_type_t` | Output type
range | `nx_aout_range_t` | Operating range
pon_state | `nx_aout_poweron_state_t` | Power on state
pon_value | `uint16_t` | Configured power on value
watchdog_value | `uint16_t` | Safe value watch dog

For more details, please refer to NXprog Instruction Manual.

### Output type
Analog outputs have three types of signals: 
- **0-20 mA**: select this output using the constant `_AOUT_0_20mA`
- **4-20 mA**: constant `_AOUT_4_20mA`
- **0-10 V**: constant `_AOUT_0_10V`

### Operating range
Allows you to set the operating range of the analog output:
* **0.00 to 100.00 %**: The register that controls the analog output expects percentage values within the range 0 to 100 %. In an Arduino project, use the constant `_AOUT_RANGE_PERCENT` to select this input mode. When using this mode, the values used in function `analogWrite` are the percent value multiplied by 100 (e.g. 325 is 3.25%): 
    * 0: Corresponds to 0.00% that is the minimum value of the analog output (0 mA, 4 mA or 0 V). 
    * 10000 Corresponds to 100.00% that is the maximum value of the analog output (20 mA, 20 mA or 10 V).
* **0 to 32 000**: The register that controls the analog output expects a value of up to 32 000. This is selected by the constant `_AOUT_RANGE_VALUE`. In function `analogWrite` the value input data ranges from:
    * 0: Corresponds to the minimum value of the analog output (0 mA, 4 mA or 0 V); to
    * 32000: Corresponds to the maximum value of the analog output (20 mA, 20 mA or 10 V). 
    
### Poweron state
 It allows you to set an initial value for the analog output when turning on the device and receiving a command. There are three possible options: 
 * **Disabled**: Allows the analog output to remain off after device initialization and until a valid command is received. Use `_PO_AOUT_DISABLED` to select this mode.
 * **Configured Value**: Allows you to set the value to be adopted in the Initial Value parameter after the device initialization and until a valid command is received. Use `_PO_AOUT_CONFIGURED_VALUE` to select this mode.
 * **Last Valid Value**: Allows the analog output to adopts the last valid value recorded. Use `_PO_AOUT_LAST_VALID_VALUE` to select this mode.

 ### Safe value watchdog
 It allows you to set a value for the analog output in case of loss of  Ethernet and/or RS485 communication. 