#ifndef UTILS_H
#define UTILS_H

#include "START.h"
#include "string.h"

bool getStrArgument(uint8_t index, char* arg, uint8_t argBuffLen);
bool getIntArgument(uint8_t index, int &arg);
bool getFloatArgument(uint8_t index, float &arg);
void inputBufferTokenEnd(char* &cmdPtrCurrent);
void inputBufferNextToken(char* &cmdPtrCurrent);
bool getCmdToken(uint8_t index, char* &ptrTokenBegin, uint8_t &len);
bool isInput(uint8_t pinNumber);

#endif
