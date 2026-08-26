## LED Driver

**What it is:** 
A class that abstracts the code involved with making an LED blink.

**Public API**

- `on()` — supplies the pin with voltage. Turning on the sensor(LED) attached to it.

- `off()` — supplies the pin with zero voltage. Turning off the sensor (LED) attached to it.

- `setMode(bool x)` - gives the pin an output or input state.

- `getPin()` - returns the pin number assigned to the constructor during creation of object.

**Usage**

​```cpp

// a 3-5 line snippet showing it instantiated and called once

​```

**Known limitations:** anything it doesn't handle yet (e.g. "no debounce built in — pair with Debouncer").
