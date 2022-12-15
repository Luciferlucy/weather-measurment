/*
 * UART.c
 *
 * Created: 11/27/2021 3:04:20 PM
 *  Author: Mina
 */ 
#include "UART.h"
#define  FREQ 16000000
#define DESIRED 9600
void UART_Init(void){
	TU32 BR_value =0;
	DIREC();
	BR_value =((FREQ) / (16 * DESIRED)) -1;
	SET_BiT(UART_UCSRB,UCSRB_RXEN);
	SET_BiT(UART_UCSRB,UCSRB_TXEN);
	#if MODE_UART == 0
	    CLR_Bit(UART_UCSRC,HC_URSEL);
	#elif MODE_UART == 1
	    SET_BiT(UART_UCSRC,HC_URSEL);
		#if OPER_MODE == ASECH
		CLR_Bit(UART_UCSRC,UCSRC_UMSEL);
		#elif OPER_MODE == SECH
		SET_BiT(UART_UCSRC,UCSRC_UMSEL);
		#endif
		#if CLOCK_MODE == RISING
		CLR_Bit(UART_UCSRC,UCSRC_UCPOL);
		#elif CLOCK_MODE == FALLING
		SET_BiT(UART_UCSRC,UCSRC_UCPOL);
		#endif
		#if PARITY_MODE == DISABLE
		CLR_Bit(UART_UCSRC,UCSRC_UPM1);
		CLR_Bit(UART_UCSRC,UCSRC_UPM0);
		#elif PARITY_MODE == RESEREVED
		CLR_Bit(UART_UCSRC,UCSRC_UPM1);
		SET_BiT(UART_UCSRC,UCSRC_UPM0);
		#elif PARITY_MODE == EVEN_PARITY
		SET_BiT(UART_UCSRC,UCSRC_UPM1);
		CLR_Bit(UART_UCSRC,UCSRC_UPM0);
		#elif PARITY_MODE == EVEN_PARITY
		SET_BiT(UART_UCSRC,UCSRC_UPM1);
		SET_BiT(UART_UCSRC,UCSRC_UPM0);
		#endif
		#if STOP_BITS == ONE_BIT
		CLR_Bit(UART_UCSRC,UCSRC_USBS);
		#elif STOP_BITS == TWO_BIT
		SET_BiT(UART_UCSRC,UCSRC_USBS);
		#endif
		#if Character_Size == FIVE_BIT
		UART_UCSRC = (UART_UCSRC & 0b11111001) | 0b00000000;
		#elif Character_Size == SIX_BIT
		UART_UCSRC = (UART_UCSRC & 0b11111001) | 0b00000010;
		#elif Character_Size == SEVEN_BIT
		UART_UCSRC = (UART_UCSRC & 0b11111001) | 0b00000100;
		#elif Character_Size == EIGHT_BIT
		UART_UCSRC = (UART_UCSRC & 0b11111001) | 0b00000110;
		#elif Character_Size == RESONE
		UART_UCSRC = (UART_UCSRC & 0b11111001) | 0b00000000;
		SET_BiT(UART_UCSRB,UCSRB_UCSZ2);
		#elif Character_Size == RESTWO
		UART_UCSRC = (UART_UCSRC & 0b11111001) | 0b00000010;
		SET_BiT(UART_UCSRB,UCSRB_UCSZ2);
		#elif Character_Size == RESTHREE
		UART_UCSRC = (UART_UCSRC & 0b11111001) | 0b00000100;
		SET_BiT(UART_UCSRB,UCSRB_UCSZ2);
		#elif Character_Size == NINE_BIT
		UART_UCSRC = (UART_UCSRC & 0b11111001) | 0b00000110;
		SET_BiT(UART_UCSRB,UCSRB_UCSZ2);
		#endif
	#endif
}
void UART_Tx(TU08 data){
	UART_UDR = data;
	while(GET_Bit(UART_UCSRA,UCSRA_UDRE)==0);
}
//when it finish receiving
TU08 UART_Rx(void){
	while(GET_Bit(UART_UCSRA,UCSRA_RXC)==0);
	return UART_UDR;
}
void UART_TXString(TU08* Str){
	TU08 i =0;
	while(Str[i] != 0){
		UART_Tx(Str[i]);
		i++;
	}
}