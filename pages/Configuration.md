# Novus Configuration retrieve functions
The current NXprog configuration can be retrieved by the object `NovusConfig` using the functions described in follwoing sections.

## getAInConfig

Read the configuration of an analog input pin.

### Syntax
```C
NovusConfig.getAInConfig(pin, &output)
```

### Parameters
**pin**: `A1` or `A2` pin.

**output**: current configuration. **Data type**: `ain_cfg_t *` as described in [Analog Input configuration data](./AnalogConfiguration.md#analog-input-configuration-data)

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not an analog input or an error occured. **Data type**: `bool`.

### Example code
```C
ain_cfg_t   conf_AI;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds

    Serial.println("Press enter to show current configuration");
}

void showConfig() {
    NovusConfig.getAInConfig(A1, &conf_AI);
    Serial.println(">>>>>>>>>>>>><<<<<<<<<<<<<<");
    Serial.println("ANALOG INPUT 1 CONFIGURATION");
    Serial.print("  Enabled: ");
    Serial.println(conf_AI.enabled);
    Serial.print("  Sensor type: ");
    Serial.println(conf_AI.type); 
    Serial.print("  Temperature unit: ");
    Serial.println(conf_AI.unit);
    Serial.print("  Scale bottom: ");
    Serial.println(conf_AI.scale_bottom);
    Serial.print("  Scale top: ");
    Serial.println(conf_AI.scale_top);
    Serial.print("  Filter: ");
    Serial.println(conf_AI.filter);
    Serial.print("  Sampling rate: ");
    Serial.println(conf_AI.sampling_rate);
}

void loop() {
    if(Serial.available() != 0){
      Serial.readString();
      showConfig(); 
    }
 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
```

## getAOutConfig

Read the current configuration of an analog output pin.

### Syntax
```C
NovusConfig.getAOutConfig(pin, &output)
```

### Parameters
**pin**: `O1` or `O2` pin.

**output**: current configuration. **Data type**: `aout_cfg_t *` as described in [Analog Output configuration data](./AnalogConfiguration.md#analog-output-configuration-data)

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not an analog output or an error occured. **Data type**: `bool`.

### Example code
```C
aout_cfg_t  conf_AO;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds

    Serial.println("Press enter to show current configuration");
}

void showConfig() {
    NovusConfig.getAOutConfig(O1,&conf_AO);  
    Serial.println(">>>>>>>>>>>>><<<<<<<<<<<<<<");
    Serial.println("ANALOG OUTPUT 1 CONFIGURATION");
    Serial.print("  Enabled: ");
    Serial.println(conf_AO.enabled);
    Serial.print("  Type: ");
    Serial.println(conf_AO.type); 
    Serial.print("  Range: ");
    Serial.println(conf_AO.range);
    Serial.print("  PowerOn state: ");
    Serial.println(conf_AO.pon_state);
    Serial.print("  PowerOn value: ");
    Serial.println(conf_AO.pon_value);
    Serial.print("  Safe value watchdog: ");
    Serial.println(conf_AO.watchdog_value);
}

void loop() {
    if(Serial.available() != 0){
      Serial.readString();
      showConfig(); 
    }
  
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
```

## getDInConfig
Read the current configuration of an digital input pin.

### Syntax
```C
NovusConfig.getDInConfig(pin, &input)
```

### Parameters
**pin**: `D1` to `D4` pins.

**output**: current configuration. **Data type**: `din_cfg_t *` as described in [Digital Input configuration data](./DigitalConfiguration.md#digital-input-configuration-data)

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not an digital input or an error occured. **Data type**: `bool`.

### Example code
```C
din_cfg_t   conf_DI;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds

    Serial.println("Press enter to show current configuration");
}

void showConfig() {
    NovusConfig.getDInConfig(D1, &conf_DI);

    Serial.println(">>>>>>>>>>>>><<<<<<<<<<<<<<");
    Serial.println("DIGITAL INPUT 1 CONFIGURATION");
    Serial.print("  Enabled: ");
    Serial.println(conf_DI.enabled);
    Serial.print("  Function type: ");
    Serial.println(conf_DI.function); 
    Serial.print("  Connection type: ");
    Serial.println(conf_DI.connection_type);
    Serial.print("  Debounce: ");
    Serial.println(conf_DI.debounce);
}

void loop() {
    if(Serial.available() != 0){
      Serial.readString();
      showConfig(); 
    }
  
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);

    
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
```

## getDOutConfig

Read the current configuration of an digital output pin.

### Syntax
```C
NovusConfig.getDOutConfig(pin, &output);
```

### Parameters
**pin**: `R1` to `R4` pins `K1` to `K8` our , identified as `R1` to `R4` when relay-type digital outputs.

**output**: current configuration. **Data type**: `dout_cfg_t *` as described in [Digital Output configuration data](./DigitalConfiguration.md#digital-output-configuration-data)

### Return

This function returns `true` when executed successfully. It returns `false` if the selected pin is not an digital output or an error occured. **Data type**: `bool`.

### Example code
```C
dout_cfg_t  conf_DO;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds

    Serial.println("Press enter to show current configuration");
}

void showConfig() {
    NovusConfig.getDOutConfig(K1, &conf_DO);

    Serial.println(">>>>>>>>>>>>><<<<<<<<<<<<<<");
    Serial.println("DIGITAL OUTPUT 1 CONFIGURATION");
    Serial.print("  Enabled: ");
    Serial.println(conf_DO.enabled);
    Serial.print("  Actuation mode: ");
    Serial.println(conf_DO.mode); 
    Serial.print("  Pulse duration: ");
    Serial.println(conf_DO.pulse_time);
    Serial.print("  Repetition duration: ");
    Serial.println(conf_DO.pulse_period);
    Serial.print("  Number of pulses: ");
    Serial.println(conf_DO.num_pulses);
    Serial.print("  Safe state: ");
    Serial.println(conf_DO.safe_state);
    Serial.print("  PowerOn state: ");
    Serial.println(conf_DO.poweron_state); 
}

void loop() {
    if(Serial.available() != 0){
      Serial.readString();
      showConfig(); 
    }
  
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
```

## getDigiRailFWVersion
Read the DigiRail baseboard version.

### Syntax
```C
NovusConfig.getDigiRailFWVersion(&value)
```

### Parameters
**value**: current firmware version. **Data type**: `uint16_t *`.

### Return

This function returns `true` when executed successfully.

### Example code
```C
uint16_t    NXprogFV;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.setTimeout(10); // 10 milliseconds

    Serial.println("Press enter to show current configuration");
}

void showConfig() {
    NovusConfig.getDigiRailFWVersion(&NXprogFV);

    Serial.println(">>>>>>>>>>>>><<<<<<<<<<<<<<");
    Serial.println("DIGI RAIL FIRMWARE VERSION");
    Serial.println(NXprogFV);
}

void loop() {
    if(Serial.available() != 0){
      Serial.readString();
      showConfig(); 
    }
  
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);

    
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
```
