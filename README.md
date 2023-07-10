# Stop_Watch

Implement the Stop Watch system with the specifications listed below:
1. Use ATmega32 Microcontroller with frequency 1Mhz.
2. Configure Timer1 in ATmega32 with CTC mode to count the Stop Watch time.
3. Use six Common Anode 7-segments.
4. Connect the six 7-segments in the project using the multiplexed technique.
5. Stop Watch counting should start once the power is connected to the MCU.
6. Configure External Interrupt INT0 with falling edge. Connect a push button with the 
   internal pull-up resistor. If a falling edge detected the Stop Watch time should be reset.
7. Configure External Interrupt INT1 with raising edge. Connect a push button with the external      pull-down resistor. If a raising edge detected the Stop Watch time should be paused.
8. Configure External Interrupt INT2 with falling edge. Connect a push button with the internal      pull-up resistor. If a falling edge detected the Stop Watch time should be resumed.
-------------------------------------------------------------------------------------
Drivers: GPIO, Timer, External Interrupts and 7-Segement - Microcontroller: ATmega32.
-------------------------------------------------------------------------------------
