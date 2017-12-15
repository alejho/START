#include "utils.h"

bool getStrArgument(uint8_t index, char* arg, uint8_t argBuffLen){
	//try to get the index_th arguments from userInputBuffer as string
	
	//the argument's index must be >0 
	//if(index==0){
		//return false;
	//}
	
	uint8_t tokenLen = 0;
	char* l_ptrTokenBegin;
	
	if (!getCmdToken(index, l_ptrTokenBegin, tokenLen) || tokenLen > MAX_ARG_LENGTH+1){
		return false;
	}
	strlcpy(arg, l_ptrTokenBegin, tokenLen+1);
	return true;
}

bool getIntArgument(uint8_t index, int &arg){
	//try to get the index_th arguments from userInputBuffer as integer
	
	//the argument's index must be >0 
	//if(index==0){
		//return false;
	//}
	
	char* l_ptrArgBegin;
	uint8_t len;
	
	if (!getCmdToken(index, l_ptrArgBegin, len)){
		return false;
	}
	char l_sToInt[len+1];
	strlcpy(l_sToInt, l_ptrArgBegin, len+1);
	//check if it's an integer
	for (uint8_t i = 0; i < len; i++){
		if(!isdigit(l_sToInt[i])) return false;
	}
	arg = atoi(l_sToInt);
	return true;
	
}

bool getFloatArgument(uint8_t index, float &arg){
	//try to get the index_th arguments from userInputBuffer as float
	
	//the argument's index must be >0 
	//if(index==0){
		//return false;
	//}
	
	char* l_ptrArgBegin;
	uint8_t len;
	
	if (!getCmdToken(index, l_ptrArgBegin, len)){
		return false;
	}
	char l_sToFloat[len+1];
	strlcpy(l_sToFloat, l_ptrArgBegin, len+1);
	//check it's a float
	for (uint8_t i = 0; i < len; i++){
		if((!isdigit(l_sToFloat[i]) && l_sToFloat[i]!='.')) return false;
	}
	arg = atof(l_sToFloat);
	return true;
}

void inputBufferTokenEnd(char* &cmdPtrCurrent){
	//skip the current token in the userInputBuffer and return the pointer to its end
	//find the token's end
	while(*cmdPtrCurrent != ' ' && *cmdPtrCurrent != '\0') {
		++cmdPtrCurrent;
    } 
}

void inputBufferNextToken(char* &cmdPtrCurrent){
	//skip to the next token's begin in the userInputBuffer 
	
	while(*cmdPtrCurrent == ' ' || *cmdPtrCurrent == '\t') {
		++cmdPtrCurrent;
    }
}

bool getCmdToken(uint8_t index, char* &ptrTokenBegin, uint8_t &len){
	
	//return the pointer to the begin of the index_nth token of the command present in the 
	//userInputBuffer of the START and its length
	ptrTokenBegin = START::userInputBuffer;
	
	for (uint8_t i = 0; i < index; i++){
		inputBufferTokenEnd(ptrTokenBegin);
		inputBufferNextToken(ptrTokenBegin);
	}
	
	char* l_ArgumentEnd = ptrTokenBegin;
	
	inputBufferTokenEnd(l_ArgumentEnd);
	len = l_ArgumentEnd - ptrTokenBegin;
	return len>0 && len<=MAX_ARG_LENGTH ? true : false;
}

bool isInput(uint8_t pinNumber){
	
	uint8_t bit = digitalPinToBitMask(pinNumber);
    uint8_t port = digitalPinToPort(pinNumber);
    volatile uint8_t *reg = portModeRegister(port);

    if (*reg & bit) {
        // It's an output
        return false;
    }
    else {
        // It's an input
        return true;
    }
}
