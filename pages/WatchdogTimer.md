# NXprog Embedded Watchdog Timer

The watchdog timer is provided in NXprog as independent hardware. It is useful for applications that are intended to run for extended periods. 
The watchdog is a timer that will force a restart on the Arduino application if the 'toggle' signal is not called promptly. When activated, the Watchdog must be toggled every 1.6 seconds otherwise the application will reboot.

## enableWDT

Enable watchdog timer. After enabling the watchdog, the application must call `toggleWDT` every 1.6 seconds or less otherwise the application will reset.

### Syntax
```C
NovusExpert.enableWDT()
```

### Return

This function doesn't return any value.

### Example code
```C
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    NovusExpert.enableWDT();
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    NovusExpert.toggleWDT();  // toggle every 1 sec to prevent aplication to reset
}
```

## disableWDT

Disable watchdog timer. 

### Syntax
```C
NovusExpert.disableWDT()
```

### Return

This function doesn't return any value.

### Example code
```C
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    NovusExpert.disableWDT(); // watchdog will not be used in this application
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
```
## isWDTActive

This function returns the current watchdog enable state. 

### Syntax
```C
NovusExpert.isWDTActive()
```

### Return

Current watchdog enable state. **Data type**: `bool`.

### Example code
```C
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if(NovusExpert.isWDTActive())
        digitalWrite(LED_BUILTIN, HIGH);
    else
        digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
```

## toggleWDT

This function resets the watchdog timer. Next 'toggle' must be performed within 1.6 seconds otherwise the application will reboot.

### Syntax
```C
NovusExpert.toggleWDT()
```

### Return

This function doesn't return any value.

### Example code
```C
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    NovusExpert.enableWDT();
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    NovusExpert.toggleWDT();  // toggle every 1 sec to prevent aplication to reset
}
```
