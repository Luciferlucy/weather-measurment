/*
 * project.c
 *
 * Created: 11/13/2021 11:15:20 PM
 * Author : Mina
 */ 
#include "main.h"


int main(void)
{
	//_delay_ms(2000);
	DIREC();
	lcd_init();
	adc_init();
	lcd_clear();
    while (1) 
    {
		while (C4_INPUT ==1){
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

