/*
 * main.h
 *
 * Created: 11/27/2021 2:57:56 PM
 *  Author: Mina
 */ 


#ifndef MAIN_H_
#define MAIN_H_
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "interrupt/External_interrupt.h"
#include "ssd/ssd.h"
#include "ADC/ADC.h"
#include "Timer/Timer.h"
#include "UART/UART.h"
#include "SPI/SPI.h"
#include "LCCD/LCD.h"
#include "I2C/I2C.h"
#include "DC Motor/DC_Motor.h"
#include "LCD_driver/LCD_driver/LCD.h"
#include "DHT/DHT.h"

#endif /* MAIN_H_ */