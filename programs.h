#ifndef PROGRAMS_H
#define PROGRAMS_H

#include <avr/pgmspace.h>
#include <Arduino.h>
#include "START.h"
#include "utils.h"
#include "telnet.h"
#include "network.h"

typedef struct sysProgramsStruct{
    const char* name;
    bool (*pFunc)();
}sysPrograms_t;

bool free();
bool setPinMode();
bool setPinStatus();
bool getPinStatus();
bool getPinMode();
bool helloWorld();
bool telnet();
bool serialTerminal();


const sysPrograms_t systemProgams[] PROGMEM = {

    {"free", &free},
    {"setPM", &setPinMode},
    {"getPM", &getPinMode},
    {"dioW", &setPinStatus},
    {"dioR", &getPinStatus},
    //{"hello", &helloWorld},
    {"telnet", &telnet},
    {"st", &serialTerminal},
    
    {NULL, NULL}
};

#endif
