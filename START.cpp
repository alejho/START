#include "START.h"

char START::userInputBuffer[MAX_INPUT_LENGTH];
uint8_t START::cursorX;
uint8_t START::cursorY;
char START::screen[SCREEN_ROWS][SCREEN_COLS];
U8GLIB_ST7920_128X64* START::u8g;

START::START(){
	
	START::u8g = new U8GLIB_ST7920_128X64(MONITOR_PIN_3, MONITOR_PIN_1, MONITOR_PIN_2, U8G_PIN_NONE);
	START::u8g->setFont(u8g_font_4x6);
	START::u8g->setRot180();
	START::cursorX = 0;
	START::cursorY = 0;
	memset(START::screen, 0, sizeof(START::screen[0][0]) * SCREEN_ROWS * SCREEN_COLS);
	START::keyboard.begin(KEYBOARD_DATA_PIN, KEYBOARD_IRQ_PIN);

}

/*void START::print(const __FlashStringHelper* msg){
	
	#ifdef UOUT_SERIAL
	Serial.print(msg);
	#else
	#endif
}*/

void START::print(int num){
	
	#ifdef UOUT_SERIAL
	Serial.print(num);
	#else
	#endif
	
	uint8_t l_length = 1;
	int l_temp = num;
	while(l_temp /= 10){
		l_length++;
	}
	char l_sNum[l_length+1];
	sprintf(l_sNum, "%d", num);
	START::writeOnScreen(l_sNum);
	START::drawScreen();
}

void START::println(int num){
	
	START::print(num);
	START::ln();
}

/*void START::print(char* msg, size_t len){
	
	#ifdef UOUT_SERIAL
	Serial.print(msg);
	#else
	#endif
}*/

void START::print(String msg){

	#ifdef UOUT_SERIAL
	Serial.print(msg);
	#else
	#endif
	char l_msg[SCREEN_COLS+1];
	msg.toCharArray(l_msg, SCREEN_COLS+1); 
	START::writeOnScreen(l_msg);
	START::drawScreen();
}

void START::println(String msg){
	START::print(msg);
	START::ln();
}

void START::print(char c){
	
	#ifdef UOUT_SERIAL
	Serial.print(c);
	#else
	#endif
	START::writeOnScreen(c);
	START::drawScreen();
}
/*static void START::print(float f){
	
	#ifdef UOUT_SERIAL
	Serial.print(f);
	#else
	#endif
	
	uint8_t l_length = 1;
	int l_intPart = (int)floorf(f);
	while(l_intPart /= 10){
		l_length++;
	}
	char l_sFloat[l_length+2+1];
	sprintf(l_sFloat, "%.2f", f);
	START::writeOnScreen(l_sFloat);
	START::drawScreen();
}*/

/*static void START::println(float f){
	START::print(f);
	START::ln();
}*/

bool START::getUserInput(){
	
	//get user input from serial line or keyboard and place it in the userInputBuffer
	
	//be sure userInputBuffer is empty
	memset(START::userInputBuffer, 0, MAX_INPUT_LENGTH);
	
	//draw prompt
	if(START::cursorY != 0){
		START::ln();
	}
	START::print(">");
	
	
	char rc='\0';
	uint8_t i = 0;       
	while(true){
		#ifdef UIN_SERIAL
		if(Serial.available() > 0){
			rc = Serial.read();
		#else
		if (keyboard.available()) {
			rc = keyboard.read();	
		#endif
			if(rc>0){
				if (rc != '\r' && rc != '\n' && rc != BACKSPACE_KEY){
					//echo
					START::print(rc);
					START::userInputBuffer[i] = rc;
					i++;
				}
				else if(rc=='\r' && i>0){
					START::userInputBuffer[i] = '\0'; // terminate the string
					return true;
				}
				else if(rc == BACKSPACE_KEY && i>0){
					//backspace(remove the last character from the input, clear the line and re-echo it!)
					START::print('\r');
					for (uint8_t j = 0; j <= i+1; ++j) {
						START::print(" ");
					}
					START::cursorX = 0;
					START::print('\r');
					START::print(">");
					i--;
					START::userInputBuffer[i] = '\0';
					START::print(START::userInputBuffer);
				}
				if(i >= MAX_INPUT_LENGTH){
					START::ln();
					START::print("input buffer overflow");
					return false;
				}
			}	
		}
		else{
			rc=0;
		}
	}
}

bool START::runCommand(){
	
	//for command I mean program name + arguments
	char *l_prgName;
	uint8_t l_prgNameLen = 0;
	
	//the program name is the first token (counting from zero)
	getCmdToken(0, l_prgName, l_prgNameLen);
	
    sysPrograms_t SysProgram;
    
    for(uint8_t i = 0; i<ARRAYSIZE(systemProgams)-1; i++){
        PROGMEM_get(&systemProgams[i], SysProgram);
        if (strncmp(l_prgName, SysProgram.name, l_prgNameLen) == 0 && strlen(SysProgram.name) == l_prgNameLen){
			START::ln();
            return SysProgram.pFunc();
        }
    }
    //no programs found!
    START::ln();
    START::println("program not found");
    return false;
}

void START::drawScreen(){
	
	START::u8g->firstPage();  
	do {
		for (uint8_t i = 0; i < SCREEN_ROWS ; i++)
		{
			START::u8g->drawStr( 0, (i*FONT_SIZE)+FONT_SIZE, &START::screen[i][0]);	
		}
	} while( START::u8g->nextPage() );
}

void START::ln(){
	
	#ifdef UOUT_SERIAL
	Serial.print("\n\r");
	#else
	#endif
	START::cursorX = 0;
	if (START::cursorY >= SCREEN_ROWS - 1){
		START::shiftScreen();
	}
	else{
		START::cursorY++;
	}
}
void START::shiftScreen(){
	
	//shift up the screen one row
	for (uint8_t i = 1; i < SCREEN_ROWS; i++){	
		strlcpy(&screen[i-1][0], &screen[i][0], SCREEN_COLS);
	}
	memset(&START::screen[SCREEN_ROWS-1][0], 0, sizeof(START::screen[SCREEN_ROWS-1][0]) * 1 * SCREEN_COLS);
}

void START::writeOnScreen(char* msg){

	uint8_t l_res = strlcpy(&START::screen[START::cursorY][START::cursorX], msg, SCREEN_COLS - START::cursorX);
	if(l_res >= SCREEN_COLS - START::cursorX){
		//truncated	
		START::cursorX = 0;
		START::ln();
	}
	else{
		START::cursorX = START::cursorX + l_res;
	}
}


void START::writeOnScreen(char c){
	if (c == '\r'){
		START::cursorX = 0;
		return;
	}
	if (START::cursorX >= SCREEN_COLS || c == '\n'){
		START::ln();
	} 
	START::screen[START::cursorY][START::cursorX] = c;
	START::cursorX++;
}
