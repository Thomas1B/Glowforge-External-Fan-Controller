# Glowforge External Fan Controller


This program is designed to read the voltage from the fan pin on the Glowforge laser cutter. When the pin is high, a relay is turned on to run an exhaust fan. After the voltage drops back to 0, the fan runs for a little longer to allow for better exhaust of fumes.

## Components

To make the controller the following components are needed:<br>
1. Attiny85.
2. AC Relay, with activation voltage of 3.3V or 5V.
3. Red led.
4. Green led.
5. 2K resistor x 2.
6. 10K resistor.
7. 0.1uF Capacitor x 2.
8. Button.
9. Switch.

Also needed is some arduino board to program the attiny85.

DigiKey (https://www.digikey.ca/) is a great place to buy electronics from.

The attiny85 is very small microcontroller, convienent for simple projects. The AC relay is used to run an external exhaust fan when the controller senses high voltage. The red led is used to notify that the controller has power, and the green is show that relay shoud be running (which is useful for debugging if the fan should be run and it's not). The button is used a reset and the switch is used to manually active the relay.

## Diagrams
 more to come!