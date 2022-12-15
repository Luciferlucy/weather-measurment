/*
 * project.c
 *
 * Created: 11/13/2021 11:15:20 PM
 * Author : Mina
 */ 
#include "main.h"
#include "string.h"
TU08 c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

//*****DHT***********//
void Requestt()
{
	SET_BiT(DIO_DDRB,4);
	B4_CLEAR;	/* set to low pin */
	_delay_ms(20);			/* wait for 20ms */
	B4_OUTPUT;
}
void Responsee()
{
	CLR_Bit(DIO_DDRB,4);
	while(B4_INPUT);
	while(B4_INPUT==0);
	while(B4_INPUT);
}
TU08 Receive_dataa()			/* receive data */
{
	for (int q=0; q<8; q++)
	{
		while(B4_INPUT == 0);  /* check received bit 0 or 1 */
		_delay_us(30);
		if(B4_INPUT)/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		c = (c<<1);
		while(B4_INPUT);
	}
	return c;
}
void int_Dhtt (){
	char data[5];
	lcd_goto_xy(0,0);
	lcd_write_word("Humidity =");
	lcd_goto_xy(1,0);
	lcd_write_word("Temp = ");
	Requestt();		/* send start pulse */
	Responsee();		/* receive response */
	I_RH=Receive_dataa();	/* store first eight bit in I_RH */
	D_RH=Receive_dataa();	/* store next eight bit in D_RH */
	I_Temp=Receive_dataa();	/* store next eight bit in I_Temp */
	D_Temp=Receive_dataa();	/* store next eight bit in D_Temp */
	CheckSum=Receive_dataa();/* store next eight bit in CheckSum */
	if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
	{
		lcd_goto_xy(0,0);
		lcd_write_word("Error");
	}
	
	else
	{
		itoa(I_RH,data,10);
		lcd_goto_xy(0,11);
		lcd_write_word(data);
		lcd_write_word(".");
		
		itoa(D_RH,data,10);
		lcd_write_word(data);
		lcd_write_word("%");

		itoa(I_Temp,data,10);
		lcd_goto_xy(1,7);
		lcd_write_word(data);
		lcd_write_word(".");
		
		itoa(D_Temp,data,10);
		lcd_write_word(data);
		lcd_write_word("C ");
		lcd_set_courser(1,12);
	}
}
///////////////////////////////////////////////////////////////
//////////**********soil*************/////////////
void soil(){
	TU16 adc_value;
	float moisture;
	char array[10];
	adc_value = ADC_READ(1);
	moisture = 100-(adc_value*100.00)/1023.00;
	lcd_goto_xy(0,0);
	lcd_write_word("Moisture:");
	dtostrf(moisture,3,2,array);
	strcat(array,"%   ");
	lcd_goto_xy(0,10);
	lcd_write_word(array);
	memset(array,0,10);
}
///////////////////////////////////////////////////////////////
////////////**************Rain**************///////////////////
void rain(){
	lcd_goto_xy(1,0);
	lcd_write_word("Rain:");
	if (GET_Bit(DIO_PINC,0)==1){
		lcd_goto_xy(1,6);
		lcd_write_word("Raining");
		}else{
		lcd_goto_xy(1,6);
		lcd_write_word("No Rain");
	}
}
/////////////////////////////////////////////////////////////
int main(void)
{
	DIREC();
	lcd_init();
	adc_init();
	lcd_clear();
    while (1) 
    {
		while (C1_INPUT ==1){
		    int_Dhtt();
		}
		lcd_clear();
		while (C2_INPUT ==1){
				soil();
				rain();
		}
		lcd_clear();
		
	}

}

