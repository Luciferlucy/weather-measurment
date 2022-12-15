/*
 * DHT_Program.c
 *
 * Created: 12/14/2022 11:13:03 PM
 *  Author: Mina
 */ 

#include "DHT.h"
void Request()
{
	SET_BiT(DIO_DDRB,4);
	B4_CLEAR;	/* set to low pin */
	_delay_ms(20);			/* wait for 20ms */
	B4_OUTPUT;
}

void Response()
{
	CLR_Bit(DIO_DDRB,4);
	while(B4_INPUT);
	while(B4_INPUT==0);
	while(B4_INPUT);
}
TU08 Receive_data()			/* receive data */
{
	TU08 d=0;
	for (int q=0; q<8; q++)
	{
		while(B4_INPUT == 0);  /* check received bit 0 or 1 */
		_delay_us(30);
		if(B4_INPUT)/* if high pulse is greater than 30ms */
		d = (d<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		d = (d<<1);
		while(B4_INPUT);
	}
	return d;
}
void int_Dht (){
	TU08 I_RH,D_RH,I_Temp,D_Temp,CheckSum;
	char data[5];
	lcd_goto_xy(0,0);
	lcd_write_word("Humidity =");
	lcd_goto_xy(1,0);
	lcd_write_word("Temp = ");
	Request();		/* send start pulse */
	Response();		/* receive response */
	I_RH=Receive_data();	/* store first eight bit in I_RH */
	D_RH=Receive_data();	/* store next eight bit in D_RH */
	I_Temp=Receive_data();	/* store next eight bit in I_Temp */
	D_Temp=Receive_data();	/* store next eight bit in D_Temp */
	CheckSum=Receive_data();/* store next eight bit in CheckSum */
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
		
		itoa(CheckSum,data,10);
		lcd_write_word(data);
		lcd_write_word(" ");
		lcd_set_courser(1,16);
	}
}


