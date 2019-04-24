#include <avr/io.h>

int main(void)
{
	// initializations
	DDRB = 0x0F;         // enable PB0 - PB3 as outputs
	PORTB |= (1 << PB4); // enable pullup on pushbutton
	int seq[8] = {0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09}; //Half-step microstepped sequence
	float delay;

	//Iterate over stepper coil sequence in the forward direction (clockwise)
	void forward(float delay, int steps)
	{
		for(int i=0; i<steps; i++){
			for(int j=0; j<8; j++){
				PORTB = seq[j] | (1 << PB4); //Write PORTB register and preserve PB4 input state
				_delay_ms(delay);
			}
		}
	}
	//Iterate over stepper coil sequence in the forward direction (counterclockwise)
	void backwards(float delay, int steps)
	{
		for(int i=0; i<steps; i++){
			for(int j=7; j>=0; j--){
				PORTB = seq[j] | (1 << PB4); //Write PORTB register and preserve PB4 input state
				_delay_ms(delay);
			}
		}
	}
	while(1)
	{
		while((PINB & (1 << PB4))) //Pushbutton is not pressed, wait
		{
			_delay_ms(100);
		}
		
		for(t=0; t<20; t++) //Pause for two seconds. Uses for loop because CPU has trouble tracking long singular delays, and repeated small delays are more accurate overall.
		{
			_delay_ms(100);
		}
		PORTB = 0x00 | (1 << PB4); //Clear stepper coil states
		dly = 14.648; //Change delay so tracker rotation matches celestial rotation.
		backwards(dly, 512);
		dly = 2.441; //Speed up to quickly reverse
		forward(dly, 512);
		PORTB = 0x00 | (1 << PB4); //Clear stepper coil states again
		
	}
	return 0;
}
