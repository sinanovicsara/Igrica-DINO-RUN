/**************************************************
*STM32F103C8 -BluePill GPIO driver header file v1.0
*Autor: GrunF
*Date:17.11.2019
*Machine:Thinkpad T430
*Revision notes:29.01.2020
*Minor bugs fix
*Comment fix
****************************************************/


#ifndef stm32f103C8_h
#define stm32f103C8_h

/***************************************************
*
*GENERIC MACROS
*
****************************************************/
//-------------------MODE----------------------------
#define INPUT 0x00   // -> deklarisemo naziv i koliko sta gdje (heksa dec za 0)
#define OUTPUT 0x01  // -> bude 1 
//----------------------------------------------------

//----------------------VALUE-------------------------
#define HIGH true   // prosledujemo 
#define LOW false
//----------------------------------------------------

//-----------------Port A CRL Pinout------------------
#define A0 0x00  // 16bitni input ? -> PRIPADAJU PORTU A SVE 0-15 spram oznaka na mikrokontroleru
#define A1 0x01
#define A2 0x02
#define A3 0x03
#define A4 0x04
#define A5 0x05
#define A6 0x06
#define A7 0x07

//-------------------Port A CRH Pinout----------------

#define A8 0x08
#define A9 0x09
#define A10 0x0a
#define A11 0x0b
#define A12 0x0c
#define A13 0x0d
#define A14 0x0e
#define A15 0x0f

// ----------------------------------

#define B0  0x10
#define B1  0x11
#define B2  0x12
#define B3  0x13
#define B4  0x14
#define B5  0x15
#define B6  0x16
#define B7  0x17
#define B8  0x18
#define B9  0x19
#define B10 0x1A
#define B11 0x1B
#define B12 0x1C
#define B13 0x1D
#define B14 0x1E
#define B15 0x1F


///////////////////////////////////////

#define C13 0x20
#define C14 0x21
#define C15 0x22

//-------------------Delay----------------



#include "stm32f10x.h"  // Device header

/***************************************************
*
*API's for GPIO  -> PROTOTIPOVI FUNKCIJA
*
****************************************************/

//-------------------------------------------
//Periherial clock control
//-------------------------------------------
															
	
//-------------------------------------------
//Input Output Declaration
//-------------------------------------------

	void pinMode(uint16_t pinNumber, uint16_t Mode); // koji je pinNumber , koji je to MOD 
																																																													
//-------------------------------------------
//Port - Pin Read Write
//-------------------------------------------

	void digitalWrite(uint16_t PinNumber, bool Value);		// 2 argumenta pinNumber i vrijednost od gore HIGH LOW 															//Write to GPIO pin
	
	bool digitalRead(uint16_t pinNumber);
	
	void pinModeAnalogIn();
	
	uint16_t analogRead();
	
	
	
	void pinModeAnalogInA0();
//void pinModeAnalogInA0(void);
  void pinModeAnalogInA1(void);
	void pinModeAnalogInA2(void);
	void pinModeAnalogInA3(void);
	void pinModeAnalogInA4(void);
	void pinModeAnalogInA5(void);
	void pinModeAnalogInA6(void);
	void pinModeAnalogInA7(void);

	uint16_t analogReadA0();
	uint16_t analogReadA1();
	uint16_t analogReadA2();
	uint16_t analogReadA3();
	uint16_t analogReadA4();
	uint16_t analogReadA5();
	uint16_t analogReadA6();
	uint16_t analogReadA7();
long map(long x, long in_min, long in_max, long out_min, long out_max);

#endif
