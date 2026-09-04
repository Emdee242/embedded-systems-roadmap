# Milestone 1 — Embedded C++ Foundations

Five small classes, built day by day, each one adding a new C++ concept on top of the last. Tested entirely in Wokwi / Serial Monitor — no physical hardware yet.

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
![Architecture diagram](../assets/Diagram/embedded_utility_library.svg)

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
if(embedDebounce.fall()){
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



# Milestone 2 — Hardware Communication
Four communication protocols, built day by day. These will be the foundations which the drivers will rely upon. ested entirely in Wokwi / Serial Monitor — no physical hardware yet.

---

## UART Echo

**What it is:**
A function demonstrating UART protocol and data exchange between the board and the serial monitor.

**Public API**

- `Serial.begin()` — configures the UART hardware's timing.
- `Serial.available()` — returns the amount of valid bytes sitting in the recieving RX buffer.
- `Serial.read()` — returns in ASCII value, the first valid byte in the RX buffer (). It returns -1 when the buffer is empty.
- `Serial.print(x)` — sends the parameter from the TX buffer to the serial monitor.

**Usage**

```cpp
void setup(){
Serial.begin(9600);
}
char incomingString;
void loop(){
if(Serial.available()){
  incomingString = Serial.read();
  Serial.print(incomingString);
  if(incomingString == '\n'){
    Serial.println();
  }
}
}
```

**Known limitations:** UART has a lower transfer than modern communication protocols (I2C, SPI).

---

## Day 2 — Datasheet Reading & Bit Manipulation

**What it is:** Not a driver — this was a research and skill-building exercise: locating a real register in a sensor's datasheet, and separately practicing the bitwise operations needed to work with register values correctly.

**Findings**

- Sensor: MPU6050
- Register: WHO_AM_I
- Address: 0x68
- Expected value: 0x68
- Why it matters: this is the first register you read once real I2C communication starts (Day 3) — it confirms you're actually talking to the correct chip before trusting any other data from it.

**Bit manipulation practice**

Practiced check/set/clear operations on a simulated register value (0x68), using a bitmask and AND/OR/AND-NOT — confirming bit 5 was set, then demonstrating that OR unconditionally sets a bit (no change, since it was already 1) and AND-with-complement clears it while leaving every other bit untouched.

```cpp
uint8_t registerVal = 0x68;
uint8_t bitMask = 1 << 5;
uint8_t readBit = registerVal & bitMask;        // check
uint8_t convertOne = registerVal | bitMask;      // set
uint8_t convertZero = registerVal & ~bitMask;    // clear
```

**Known limitations:** This is preparation work, not yet connected to real hardware — the WHO_AM_I register hasn't actually been read over I2C yet; that's Day 3.
