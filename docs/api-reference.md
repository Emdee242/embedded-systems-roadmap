# Milestone 1 — Embedded C++ Foundations

Five small classes, built day by day, each one adding a new C++ concept on top of the last. Tested entirely in Wokwi / Serial Monitor — no physical hardware yet.

---

## LED Driver

**What it is:**
A class that wraps `digitalWrite()` so an LED's pin lives as a private member instead of a loose global. `on()`, `off()`, and `setMode()` are the only ways to touch it from outside.

**Public API**

- `on()` — supplies the pin with voltage. Turns the LED on.
- `off()` — supplies the pin with zero voltage. Turns the LED off.
- `begin()` — configures the pin as OUTPUT.
- `getPin()` — returns the pin number assigned at construction.
- `ledState()` — returns the current LED state.

**Usage**

```cpp
LED led1(7);

void setup() {
  led1.begin();
}

void loop() { 
  // put your main code here, to run repeatedly:
led1.on();
delay(500);
led1.off();
delay(500);
}
```

**Known limitations:** No validation that the pin number passed in is actually a valid GPIO pin.

---

## Button Driver

**What it is:**
Same idea as the LED driver, but for reading a button instead of writing to an LED. Wraps `digitalRead()` and owns the pin, using `INPUT_PULLUP` so no external resistor is needed.

**Public API**

- `begin()` — configures the pin as `INPUT_PULLUP`.
- `readPin()` — returns the current raw state of the pin.

**Usage**

```cpp
Button Button1(7);

void setup() {
  Serial.begin(9600);
  Button1.begin();
}

void loop() {
  Serial.print(Button1.readPin());
}
```

**Known limitations:** This is a raw, unfiltered read — no debouncing. Mechanical bounce means a single physical press can register multiple false transitions. Pair with the Debouncer below for anything that actually needs to detect a clean press.

---

## Debouncer

**What it is:**
Takes a noisy raw button signal and outputs a single stable state, using `millis()` comparisons instead of `delay()`. Also exposes a `fall()` method to detect a clean falling-edge press event (useful for "did the button just get pressed," not just "is it currently pressed").

**Public API**

- `check()` — returns the current debounced (clean) state of the button.
- `fall()` — returns `true` exactly once, on the instant a clean HIGH→LOW transition is detected.

**Usage**

```cpp
Button Button1(7);
Debouncer Debouncer1(Button1);

void setup() {
  Serial.begin(9600);
  Button1.begin();
}

void loop() {
  Serial.print(Debouncer1.check());
}
```

**Known limitations:** The 50ms debounce window is hardcoded inside the class — not configurable through the constructor, so every Debouncer instance is stuck with the same bounce time regardless of the actual switch being used. `fall()` only detects a falling edge; there's no equivalent `rise()` for the opposite transition. Debouncer takes its Button by reference, so it's tightly coupled to a specific Button instance for its whole lifetime. the fall() function does two actions. checking system state and modifying a system command.

---

## Software Timer

**What it is:**
A reusable, non-blocking "has N milliseconds passed?" class — the generalized version of the timing logic hand-built inside the Debouncer. This becomes the backbone for most future non-blocking behavior in the project.

**Public API**

- `interval()` — returns `true` exactly once every time the configured interval has elapsed, then resets internally.
- `setTimer(unsigned long x)` —  declares the interval time.

**Usage**

```cpp
const unsigned long specificTimer = 1000;
Timer sensorTimer;

void setup(){
Serial.begin(9600);
sensorTimer.setTimer(specificTimer);
sensorTimer.reset();
}

void loop(){
if(sensorTimer.intervalPassed()){
  Serial.println(1);
}
}
```

**Known limitations:** The only way to interact with it is checking `interval()`.

---

## Circular Buffer

**What it is:**
A fixed-size array (1024 slots) that wraps around using `head`/`tail` indices and bitmask arithmetic instead of modulo. When full, new writes overwrite the oldest unread entry rather than getting rejected — matches how real UART/I²C FIFOs and rolling sensor logs behave.

**Public API**

- `write(int x)` — writes a value into the buffer. If full, silently overwrites the oldest entry and advances both `head` and `tail`.
- `read()` — returns the oldest unread value and advances `tail`. Returns `0` if the buffer is empty.
- `isFull()` — returns the current count of valid items in the buffer.

**Usage**

```cpp
Buffer Buffer1;

void loop() {
  Buffer1.write(42);
  int value = Buffer1.read();
}
```

**Known limitations:** `read()` returns `0` both as a legitimate stored value and as the "buffer is empty" signal — there's no way for the caller to tell those two cases apart. No way to peek at the buffer's contents without consuming an item. `isFull()` is named like a boolean check but actually returns the item count, not a true/false — worth renaming or splitting into a separate `isFull()`/`getCount()` pair later. Not thread-safe (not a concern yet, becomes relevant once FreeRTOS tasks are introduced in Milestone 6).

---

## Logger

**What it is:**
A Log function that reports the current hardware state and uses an enum class to denote the severity of the message.

**Severity:** 
Defines the severity levels for log messages.

```cpp
enum class Severity {
    INFO,
    WARN,
    ERROR
};
```

**Public API**

- `Log(const char* message, Severity Level)` — displays the inputted string message as well as severity level.
- `read()` — returns the oldest unread value and advances `tail`. Returns `0` if the buffer is empty.
- `isFull()` — returns the current count of valid items in the buffer.

**Usage**

```cpp
Buffer Buffer1;

void loop() {
  Buffer1.write(42);
  int value = Buffer1.read();
}
```

**Known limitations:** The output of Log is not being stored. 

---

###### Embedded Utility Library

**What it is:**
A combined reusable library containing the components developed throughout Milestone 1.

**Components:**
- LED
- Button
- Debouncer
- Timer
- Circular Buffer
- Logger

**Structure:**
[![architecture diagram](assets/Diagram/embedded_utility_library.svg)]

**Usage:**
```cpp
LED embedLED(8);
Button embedButton(7);
Debouncer embedDebounce(embedButton);
Timer embedTimer;
Buffer embedBuffer;

void setup(){
embedLED.begin();
embedButton.begin();
Serial.begin(9600);
embedTimer.setTimer(300);
embedTimer.reset();
}

bool buttonPressed = true;

void loop(){
if(embedDebounce.check() == LOW){
if(buttonPressed){
  embedTimer.reset();
  buttonPressed = false;
  embedLED.on();
  embedBuffer.write(1);
}
  if(embedTimer.intervalPassed()){
    if(embedLED.ledState()){
    embedLED.off();
    embedBuffer.write(0);  
    }else{
      embedLED.on();
      embedBuffer.write(1);
    }
  }
}else{
  embedLED.off();
  buttonPressed = true;
}
}
```
**Known Limitations:** The file contains the main code of all the components involved. Which will change when the .ino files are converted to .cpp and .h files in milestone 4.
