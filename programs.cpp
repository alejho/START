#include "programs.h"


bool free(){
	
	//free memory in bytes
	
	extern int __heap_start, *__brkval;
    int v;
    START::print("free memory: ");
    START::print((int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval));
    START::print(" bytes");
    return true;
}

bool setPinMode(){
	
	//set pin mode according to the arguments 1(int-pin number) and 2(str-pin mode)

    int l_nArg1;
    char l_sArg2[MAX_ARG_LENGTH+1];

	//check if the arguments exists
    if(!getIntArgument(1, l_nArg1) || !getStrArgument(2, l_sArg2, MAX_ARG_LENGTH+1)){
		START::print("usage: setPM pin_number INPUT/OUTPUT");
		return false;
	}
	//is a reserved pins?
	//if(l_nArg1 == CHIP_SELECT_ETH || l_nArg1 == SCK || l_nArg1 == MISO || l_nArg1 == MOSI){
	if(l_nArg1 == CHIP_SELECT_ETH || l_nArg1 == MONITOR_PIN_1 || l_nArg1 == MONITOR_PIN_2 || l_nArg1 == MONITOR_PIN_3
		|| l_nArg1 == KEYBOARD_DATA_PIN || l_nArg1 == KEYBOARD_IRQ_PIN || l_nArg1 == ETH_SHIELD_PIN_1 || l_nArg1 == ETH_SHIELD_PIN_2 || l_nArg1 == ETH_SHIELD_PIN_3){
		START::print("setPM: this pin is reserved!");
        return false;
    }
    if(strncmp(l_sArg2, "INPUT", strlen("INPUT")) == 0){
        pinMode(l_nArg1, INPUT);
        return true;
	}
	else if(strncmp(l_sArg2, "OUTPUT", strlen("OUTPUT")) == 0){
		pinMode(l_nArg1, OUTPUT);
		return true;
	}
	else{
		START::print("wrong argument (must be INPUT or OUTPUT)");
		return false;
	}
}

bool setPinStatus(){
	
	//set pin status according to the arguments 1(int-pin number) and 2(str-pin value)
	int l_nArg1;
	char l_sArg2[MAX_ARG_LENGTH+1];
	
    //check if the arguments exists
    if(!getIntArgument(1, l_nArg1) || !getStrArgument(2, l_sArg2, MAX_ARG_LENGTH+1)){
		START::print("usage: dioW pin_number true/false");
		return false;
	}
	//is a reserved pins?
	if(l_nArg1 == CHIP_SELECT_ETH || l_nArg1 == MONITOR_PIN_1 || l_nArg1 == MONITOR_PIN_2 || l_nArg1 == MONITOR_PIN_3
		|| l_nArg1 == KEYBOARD_DATA_PIN || l_nArg1 == KEYBOARD_IRQ_PIN || l_nArg1 == ETH_SHIELD_PIN_1 || l_nArg1 == ETH_SHIELD_PIN_2 || l_nArg1 == ETH_SHIELD_PIN_3){
		START::print("dioW: this pin is reserved!");
        return false;
    }
    //is an input?
    if(isInput(l_nArg1)){
		START::print("dioW: can't set the value of an input!");
        return false;
    }
	if(strncmp(l_sArg2, "HIGH", strlen("true")) == 0){
		digitalWrite(l_nArg1, HIGH);
	}
	else if(strncmp(l_sArg2, "LOW", strlen("false")) == 0){
		digitalWrite(l_nArg1, LOW);
	}
	return true;
}

bool getPinStatus(){
	
	//return the current pinStatus of the arg1 pin
    int l_nArg1;

	if(!getIntArgument(1, l_nArg1)){
		START::print("usage: dioR pin_number");
		return false;
	}
	
	if(digitalRead(l_nArg1) == HIGH){
		START::print("HIGH");
	}
	else{
		START::print("LOW");
	}
	
	return true;
}

bool getPinMode(){
	
	//return the current pinMode of the arg1 pin
    int l_nArg1;
    
    if(!getIntArgument(1, l_nArg1)){
		START::print("usage: getPM pin_number");
		return false;
	}
	if(isInput(l_nArg1)){
		START::print("INPUT");
	}
	else{
		START::print("OUTPUT");
	}
	return true;
}

/*bool helloWorld(){
	
	//just a test program...remove it!
	
	int l_nArg1 = 0;
	if(!getIntArgument(1, l_nArg1)){
		START::print("error retrieving argument");
		return false;
	}
	
	char l_sArg2[MAX_ARG_LENGTH+1];
	if(!getStrArgument(2, l_sArg2, MAX_ARG_LENGTH+1)){
		START::print("error retrieving argument");
		return false;
	}
	
	float l_fArg3 = 0.0;
	if(!getFloatArgument(3, l_fArg3)){
		START::print("error retrieving argument");
		return false;
	}
	
	START::print("hello world! ");
	START::print("first Argument: ");
	START::print(l_nArg1);
	
	START::print(" | second Argument: ");
	START::print(l_sArg2);
	
	START::print(" | third Argument: ");
	START::print(l_fArg3);
	
	return true;
}*/

bool telnet(){

	EthernetClient client;                                   
	byte clientMAC[] = { MAC_byte_1, MAC_byte_2, MAC_byte_3, MAC_byte_4, MAC_byte_5, MAC_byte_6}; 
	IPAddress clientIp (IP_www, IP_xxx, IP_yyy, IP_zzz); 
	IPAddress clientDns (DNS_www, DNS_xxx, DNS_yyy, DNS_zzz); 
	IPAddress clientGw (GW_www, GW_xxx, GW_yyy, GW_zzz); 
	IPAddress clientSbn (SBN_www, SBN_xxx, SBN_yyy, SBN_zzz); 
	
	Ethernet.begin(clientMAC, clientIp, clientDns, clientGw, clientSbn);   
	
	//get server ip
	char l_sBuf[MAX_ARG_LENGTH+1];
	if(!getStrArgument(1, l_sBuf, MAX_ARG_LENGTH+1)){
		START::print("missing ip");
		return false;
	}
	uint8_t Parts[4] = {0,0,0,0};
	uint8_t Part = 0;
	for ( uint8_t i=0; i<strlen(l_sBuf); i++ ){
		char c = l_sBuf[i];
		if ( c == '.' ){
			Part++;
			continue;
		}
		Parts[Part] *= 10;
		Parts[Part] += c - '0';
	}
	
	IPAddress serverIp(Parts[0], Parts[1], Parts[2], Parts[3]);
	telnetClient tc(client); 
	//username
	START::print("login: ");
	if(START::getUserInput()){
		if(!getStrArgument(0, l_sBuf, MAX_ARG_LENGTH+1)){
			START::ln();
			START::println("bad login");
			return false;
		}	
	}
	else{
		START::ln();
		START::println("bad input!");
		return false;
	}
	//password
	START::ln();
	START::print("password: ");
	char l_sBuf2[MAX_ARG_LENGTH+1];
	if(START::getUserInput()){
		if(!getStrArgument(0, l_sBuf2, MAX_ARG_LENGTH+1)){
			START::println("bad password");
			return false;
		}	
	}
	else{
		START::println("bad input!");
		return false;
	}
	START::ln();
	//try to login!
	if(!tc.login(serverIp, l_sBuf, l_sBuf2)){
		START::ln();
		START::println("login failed!");
		tc.disconnect();
		return false;
	}   
	
	while(strcmp(START::userInputBuffer, "exit") != 0 && client.connected()){
		//get command to send
		if(START::getUserInput()){
			START::ln();
			tc.sendCommand(START::userInputBuffer);	
		}
		else{
			START::print("bad input!");
			return false;
		}
	}
	tc.disconnect();
	START::println("logout");
	return true;	
}

bool serialTerminal(){
	
	START::println("serial terminal begin");
	while(strcmp(START::userInputBuffer, "exit") != 0){
		
		//be sure userInputBuffer is empty
		memset(START::userInputBuffer, 0, MAX_INPUT_LENGTH);
		//draw prompt
		START::ln();
		START::print(">");
		
		//get command to send
		if(START::getUserInput()){
			if (strcmp(START::userInputBuffer, "exit") == 0) continue;
			START::ln();
			Serial.println(START::userInputBuffer);	
			//wait for a response
			bool l_bListen = true;
			char rc='\0';
			while (l_bListen){
				if(Serial.available() > 0){
					rc = Serial.read();
					if (rc != '\r' && rc != '\n' && rc != BACKSPACE_KEY){
						START::print(rc);
					}
					else if(rc == '\r' || rc == '\n'){
						l_bListen = false;
					}
				}
			}
		}	
		else{
			START::print("bad input!");
			return false;
		}
	}
	START::println("serial terminal end");
}

