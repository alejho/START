#ifndef TERMINAL_H
#define TERMINAL_H

#include <avr/pgmspace.h>
#include <Arduino.h>
#include "programs.h"
#include "U8glib.h"
#include <PS2Keyboard.h>
#include <Ethernet.h>

#define DEBUG 
//#define UOUT_SERIAL 
//#define UIN_SERIAL  
#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

const uint8_t MAX_INPUT_LENGTH = 32;
const uint8_t MAX_ARG_LENGTH = 16;
const uint8_t SCREEN_ROWS = 10;
const uint8_t SCREEN_COLS = 32;
const uint8_t BACKSPACE_KEY = 127;
const uint8_t FONT_SIZE = 6;
const uint8_t MONITOR_PIN_1 = 5;
const uint8_t MONITOR_PIN_2 = 6;
const uint8_t MONITOR_PIN_3 = 7;
const uint8_t KEYBOARD_DATA_PIN = 8;
const uint8_t KEYBOARD_IRQ_PIN =  2;
const uint8_t CHIP_SELECT_ETH = 10;
const uint8_t ETH_SHIELD_PIN_1 = 11;
const uint8_t ETH_SHIELD_PIN_2 = 12;
const uint8_t ETH_SHIELD_PIN_3 = 13;
		

template <typename T> T PROGMEM_get (const T * sce, T& dest){
	memcpy_P (&dest, sce, sizeof (T));
}


class START{
	
	public:
	
		static char userInputBuffer[MAX_INPUT_LENGTH];
	
		START();
		//static void print(const __FlashStringHelper* msg);
		static void print(int num);
		static void println(int num);
		//static void print(char* msg, size_t len);
		static void print(String msg);
		static void println(String msg);
		static void print(char c);
		static void ln();
		static void writeOnScreen(char* msg);
		static void writeOnScreen(char c);
		static void drawScreen();
		//static void print(float f);
		//static void println(float f);
		static bool getUserInput();
		static bool runCommand();
		
	
	private:
		
		static U8GLIB_ST7920_128X64* u8g;
		static PS2Keyboard keyboard;
		
		static uint8_t cursorX;
		static uint8_t cursorY;
		static char screen[SCREEN_ROWS][SCREEN_COLS];
		static void shiftScreen();

};

#endif
