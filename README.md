# Details

Uses half-stepped microstepping to drive stepper motor. The following sequence is used to drive individual stepper coils:

	[0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09]

This is written directly to the PORTB register of the ATTiny85. This is equivalent to the following sequence of individual coil states:

      1 2 3 4
	[[1,0,0,0],
	 [1,1,0,0],
	 [0,1,0,0],
	 [0,1,1,0],
	 [0,0,1,0],
	 [0,0,1,1],
	 [0,0,0,1],
	 [1,0,0,1]]
 
 The control output for coil 1 is also used to keep USB battery packs awake. A 2n2222 NPN transistor is triggered by 
 the control output of coil 1. A resistor is used to draw 50 mA when the transistor is triggered in order to briefly
 exceed the threshold level for the DC-DC converter used in most USB battery packs. This corresponds to a 25% duty cycle
 of 50 mA pulses, excluding the current draw by the stepper motor. 
