
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void Timer1_Init_CTC_Mode()
{
	TCNT1 = 0;
	// Set Timer initial value to 0
	OCR1A  = 977; // For 1 sec
	TCCR1B = (1 << WGM12) | (1<<CS10) | (1<<CS12);  //pre scaler 1024
	TIMSK |=(1<<OCIE1A);
	SREG |=(1<<7);
}

unsigned char sec1_num = 0;
unsigned char min1_num = 0;
unsigned char hour1_num = 0;

ISR(TIMER1_COMPA_vect)
{

	if(sec1_num %10 == 9 && sec2_num!=5)
	{
		sec1_num = 0;
		sec2_num++;
	}
	else if(sec1_num != 9)
	{
		sec1_num++;
	}
	else if(sec2_num==5 && sec1_num == 9 && min1_num != 9)
	{
		sec1_num=0;
		sec2_num=0;
		min1_num++;
	}
	else if(min1_num == 9 && min2_num!=5)
	{
		min2_num++;
		min1_num = 0;
		sec1_num=0;
		sec2_num=0;
	}
	else if(hour1_num!=9 && min2_num==5 && min1_num == 9 && sec2_num==5 && sec1_num == 9)
	{
		sec1_num=0;
		sec2_num=0;
		min1_num=0;
		min2_num=0;
		hour1_num++;
	}
	else if(hour1_num==9 && min2_num==5 && min1_num == 9 && sec2_num==5 && sec1_num == 9)
	{
		sec1_num=0;
		sec2_num=0;
		min1_num=0;
		min2_num=0;
		hour1_num=0;
		hour2_num++;
	}
}

void int0_init()
{
	DDRD  &= ~(1<<PD2); //input pin
	PORTD |= (1<<PD2);  //ACTIVE INTERNAL PULL UP RESISTOR
	MCUCR |=(1<<ISC01); //falling edge
	GICR |=(1<<INT0); // interrupt0 enable
	SREG |=(1<<7); // I-bit

}

ISR(INT0_vect)
{
	sec1_num = 0;
	sec2_num = 0;
	min1_num = 0;
	min2_num = 0;
	hour1_num = 0;
	hour2_num = 0;
	TCNT1 = 0;
}

void int1_init()
{
	DDRD &= ~(1<<PD3);
	MCUCR |=(1<<ISC11) |(1<<ISC10);
	GICR |= (1<<INT1);
	SREG |= (1<<7);
}

ISR(INT1_vect)
{
	TCCR1B &= ~(1<<CS10) & ~(1<<CS12);
	_delay_ms(1);
}

void int2_init()
{
	DDRB &= ~(1<<PB2);
	PORTB |=(1<<PB2);
	MCUCSR |=(1<<ISC2) ;
	GICR |= (1<<INT2);
	SREG |= (1<<7);
}

ISR(INT2_vect)
{
	if((PINB & (1<<PB2)))
	{
		TCCR1B |= (1<<CS10) | (1<<CS12);
		_delay_ms(1);
	}

}


int main(void)
{

	//7seg
	DDRD  &= ~(1<<PD3); // configure pin 4 in PORTD as input pin
	DDRA  |= (1<<0);
	DDRA  |= (1<<1);
	DDRC |= 0x0F; // configure first four pins of PORTC as output pins

	// initialize the 7-segment with value 0 by clear the first four bits in PORTC
	PORTC &= 0xF0;
	Timer1_Init_CTC_Mode();
	int0_init();
	int1_init();
	int2_init();
    while(1)
    {
    	/*****  first 7 segment *****/
    	PORTA &=0xc0;
    	PORTA |=(1<<0);
    	PORTC = (PORTC & 0xF0) | (sec1_num & 0x0F);
    	_delay_ms(1);

    	PORTA &=0xc0;
    	PORTA |=(1<<1);
    	PORTC = (PORTC & 0xF0) | (sec2_num & 0x0F);
    	_delay_ms(1);

    	PORTA &=0xc0;
    	PORTA |=(1<<2);
    	PORTC = (PORTC & 0xF0) | (min1_num & 0x0F);
    	_delay_ms(1);

    	PORTA &=0xc0;
    	PORTA |=(1<<3);
    	PORTC = (PORTC & 0xF0) | (min2_num & 0x0F);
    	_delay_ms(1);

    	PORTA &=0xc0;
    	PORTA |=(1<<4);
    	PORTC = (PORTC & 0xF0) | (hour1_num & 0x0F);
    	_delay_ms(1);

    	PORTA &=0xc0;
    	PORTA |=(1<<5);
    	PORTC = (PORTC & 0xF0) | (hour2_num & 0x0F);
    	_delay_ms(1);

    	if(!(PIND & (1<<PD2)))
    	{
    		PORTC &= 0xF0;
    	}
    }











/*

 unsigned char sec1_num = 0;
unsigned char sec2_num = 0;
unsigned char min1_num = 0;
unsigned char min2_num = 0;
unsigned char hour1_num = 0;
unsigned char hour2_num = 0;

ISR(TIMER1_COMPA_vect)
{

	if(sec1_num == 9 && sec2_num!=5)
	{
		sec1_num = 0;
		sec2_num++;
	}
	else if(sec1_num != 9)
	{
		sec1_num++;
	}
	else if(sec2_num==5 && sec1_num == 9 && min1_num != 9)
	{
		sec1_num=0;
		sec2_num=0;
		min1_num++;
	}
	else if(min1_num == 9 && min2_num!=5)
	{
		min2_num++;
		min1_num = 0;
		sec1_num=0;
		sec2_num=0;
	}
	else if(hour1_num!=9 && min2_num==5 && min1_num == 9 && sec2_num==5 && sec1_num == 9)
	{
		sec1_num=0;
		sec2_num=0;
		min1_num=0;
		min2_num=0;
		hour1_num++;
	}
	else if(hour1_num==9 && min2_num==5 && min1_num == 9 && sec2_num==5 && sec1_num == 9)
	{
		sec1_num=0;
		sec2_num=0;
		min1_num=0;
		min2_num=0;
		hour1_num=0;
		hour2_num++;
	}
}

 */









}
