/* 
This program is designed using an ATTiny85 to sense voltage is high on the
glowforge laser cutter fan pin. If it is high, then using a relay turn on a fan for an exhaust.
*/


// Defining pins
const int powerState_led_pin = 1;  // green led.
const int fan_pin = 0;             // connected to fan pin on glowforge.
const int relay_pin = 4;

// Global variables
bool relay_state = false;          // if relay is on or off.
unsigned long last_high_time = 0;  // last time voltage was high.

// extra time to run the fan after the voltage drops back to 0.
// this is not exact time due to run time.
const int extra_run_time = 1000 * 30;

// Other variables
unsigned long TimeOfLastDebounce = 0;
const long DebounceTime = 0.01;


// ************* Functions *************

void run_led(int pin, bool state = false) {
  /*
  Function to run the led.

    Parameters:
      pin: pin to led.
      state: true - on, false - off.
  */
  digitalWrite(pin, state);
}


void run_relay(int pin, bool state = false) {
  /* 
    Function to run the relay

      Parameters:
        pin: pin to relay.
        state: power state of relay, true - on, false - off.
  */

  if (state) {
    analogWrite(pin, 255);
    run_led(powerState_led_pin, true);
  } else {
    analogWrite(pin, 0);
    run_led(powerState_led_pin, false);
  }
}


// ************* Main Program *************


void setup() {
  /* Set up function to initialize things */
  pinMode(powerState_led_pin, OUTPUT);
  pinMode(relay_pin, OUTPUT);
  pinMode(fan_pin, INPUT);

  // flashing led for start up.
  for (int i = 0; i < 10; i++) {
    run_led(powerState_led_pin, false);
    delay(50);
    run_led(powerState_led_pin, true);
    delay(50);
  }
  run_led(powerState_led_pin, false);
}

void loop() {
  /* Main Loop */

  if ((millis() - TimeOfLastDebounce) > DebounceTime) {  // if statement for debouncing.

    bool power_state = digitalRead(fan_pin);  // reading fan pin on the glowforge.

    if (power_state) {  // if power state is high:
      if (!relay_state) {
        // if the relay is off, then turn it on and the running light.
        relay_state = true;
        run_led(powerState_led_pin, relay_state);
        run_relay(relay_pin, relay_state);
      }
      last_high_time = millis();  // last time fan pin was read high.
    } else {
      if ((millis() - last_high_time) >= extra_run_time) {  // after the extra run time, turn off the relay and light :
        relay_state = false;
        run_led(powerState_led_pin, relay_state);
        run_relay(relay_pin, relay_state);
      }
    }
  }

  TimeOfLastDebounce = millis();  // debouncing
}
