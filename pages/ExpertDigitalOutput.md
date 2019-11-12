# NOVUS Expert functions for Digital Output

## setMode
Configure the digital output to a valid operating mode. It is important to notice that not all combinations of parameters are valid for digital output. Please refer to the table in [Actuation mode](./DigitalConfiguration.md/#Actuation-mode) about the combinations for valid operating modes. The digital output will be enabled when this function succeeds.

### Syntax
```C
NovusExpertDOut.setMode(pin, opMode, pulseTime, pulsePeriod, nPulse, po_state, po_value, safe_state)
```

### Parameters
**pin**: the name of the digital output pin. In NXprog the pins are `K1` to `K8` or `R1` to `R4` as displayed in the NXprog front panel.

**opMode**: actuation mode. **Data type**: `nx_dout_actuation_mode_t` as defined in [Actuation mode](./DigitalConfiguration.md/#Actuation-mode)

**pulseTime**: defined duration of a pulse in tenths of a second. If this value is 10 the pulse time will be 1 second.  **Data type**: `uint16_t`.

**pulsePeriod**: the defined period of the pulse train in tenths of a second. If this value is 30 the pulse period will be 3 seconds. **Data type**: `uint16_t`.

**nPulse**: number of pulses to be generate (see valid options in [Actuation mode](./DigitalConfiguration.md/#actuation-mode)). **Data type**: `uint16_t`.

**po_state**: the state assumed by the digital output after the NXprog initialization and in which must remain until the receiving of a digital
command that redefines its condition. **Data type**: `nx_dout_poweron_state_t` as defined in [Power On State](./DigitalConfiguration.md/#power-on-state). 

**po_value**: the value assumed by the digital output after the NXprog initialization. **Data type**: `bool`.

**safe_state**: the condition to be adopted by the digital output when a command is interrupted due to a communication failure. **Data type**: `bool`.

Please, refer to [DigitalConfiguration](./DigitalConfiguration.md) about digital output modes and parameters.

### Example code
```C
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);

    // initialize digital Output
    NovusExpertDOut.setMode(K1, _DOUT_SINGLE_PULSE, 10, 0, 1, _PO_DOUT_OFF, false, false);
    digitalWrite(K1, LOW);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH); 
    digitalWrite(K1, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(K1, LOW);
    delay(500);
}
```

## setState
Enables or disables a specified digital output.

### Syntax
```C
NovusExpertDOut.setState(pin, enable) 
```

### Parameters
**pin**: `R1` to `R4` or `K1` to `K8` pin.

**enable**: desired state. **Data type**: `bool`.

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.

### Example code
```C
dout_cfg_t   conf_DO;
String command; 
char command_buf[80];
int state = 1;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds

    // initialize digital Output
    NovusExpertDOut.setMode(K1, _DOUT_SINGLE_PULSE, 10, 0, 1, _PO_DOUT_OFF, false, false);
    digitalWrite(K1, LOW);
}

void loop() {
    if(Serial.available() != 0){
        // user entered the new state
        command = Serial.readString(); 
        command.toCharArray(command_buf, sizeof(command_buf));
        state = atoi(command_buf);
        if (state == 0)
            NovusExpertDOut.setState(K1, false);   
        else
            NovusExpertDOut.setState(K1, true);   
    }
    NovusConfig.getDOutConfig(K1, &conf_DO);
    Serial.println(">>>>>>>>>>>>><<<<<<<<<<<<<<");
    Serial.println("DIGITAL OUTPUT 1 CONFIGURATION");
    Serial.print("  Enabled: ");
    Serial.println(conf_DO.enabled);
    delay(2000);
}
```


## setSafeState
This function sets the condition to be adopted by the digital output when a command is interrupted due to a communication failure. The digital output will be enabled when this function succeeds.

### Syntax
```C
NovusExpertDOut.setSafeState(pin, safe_state) 
```

### Parameters
**pin**: `R1` to `R4` or `K1` to `K8` pin.

**safe_state**: desired state. **Data type**: `bool`.

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.

## setPowerOnState
It is the condition to be adopted by the digital output after the NXprog initialization and in which must remain until the receiving of a digital
command that redefines its condition. There are three 'Power On State' options as listed below. The digital output will be enabled when this function succeeds.


### Syntax
```C
NovusExpertDOut.setPowerOnState(pin, po_state) 
```

### Parameters
**pin**: `R1` to `R4` or `K1` to `K8` pin.

**po_state**: desired state. **Data type**: `nx_dout_poweron_state_t` as defined in [Power On State](./DigitalConfiguration.md/#Power-On-State). 

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.

## setActuationMode
Sets the digital output actuation mode: Logical State, Single Pulse or Pulse Train .

### Syntax
```C
NovusExpertDOut.setActuationMode(pin, opMode, pulseTime, pulsePeriod, nPulse)
```

### Parameters
**pin**: `R1` to `R4` or `K1` to `K8` pin.

**opMode**: actuation mode. **Data type**: `nx_dout_actuation_mode_t` as defined in [Actuation mode](./DigitalConfiguration.md/#Actuation-mode)

**pulseTime**: defined duration of a pulse in tenths of a second. For example, when this value is 10 the pulse time will be 1 second.  **Data type**: `uint16_t`.

**pulsePeriod**: the defined period of the pulse train in tenths of a second. For example, when this value is 30 the pulse period will be 3 seconds. **Data type**: `uint16_t`.

**nPulse**: number of pulses to be generate (see valid options in [Actuation mode](./DigitalConfiguration.md/#Actuation-mode)). This number must be greater than 1 when `opMode` is `_DOUT_PULSE_TRAIN`. **Data type**: `uint16_t`.

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.

### Example code
```C
bool generate_pulse = true;
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    // Configure digital output K1 as a pulse train
    // Every time 1 is written in K1, it will generate four 1 second pulses (2-second width)
    NovusExpertDOut.setActuationMode(K1, _DOUT_PULSE_TRAIN, 20, 40, 4); 
    digitalWrite(K1, LOW);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    if(generate_pulse) {
        // generate pulse train just once
        generate_pulse = false; 
        digitalWrite(K1, HIGH);  // 
    }
}
```

## enInstant
Configure channel as digital output instant value.

### Syntax
```C
NovusExpertDOut.enInstant(pin, po_state, safe_state)
```

### Parameters
**pin**: `R1` to `R4` or `K1` to `K8` pin.

**po_state**: desired state. **Data type**: `nx_dout_poweron_state_t` as defined in [Power On State](./DigitalConfiguration.md/#Power-On-State). 

**safe_state**: the condition to be adopted by the digital output when a command is interrupted due to a communication failure. **Data type**: `bool`.

Please, refer to [DigitalConfiguration](./DigitalConfiguration.md) about digital output modes and parameters.

### Return
This function returns `true` when executed successfully. **Data type**: `bool`.

### Example code
```C
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    NovusExpertDOut.enInstant(K1, _PO_DOUT_OFF, false); //Configure digital output channel 1 to write
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
    digitalWrite(K1, HIGH);            // turn digital outupt 1 on
    delay(1000);                       
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
    digitalWrite(K1, LOW);             // turn digital outupt 1 off
    delay(1000);                       
}
```
