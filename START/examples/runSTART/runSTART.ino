#include <START.h>

START terminal;

void setup() {
}

void loop() {
  if(terminal.getUserInput()){
    if(!terminal.runCommand()) terminal.print("execution error");
  }
  else{
    terminal.print("bad input!");
  }
}

