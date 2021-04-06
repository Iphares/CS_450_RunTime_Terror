#include "PIC.h"

void enableBit(int bit){
  //disable(); //Disables interrupts
  mask = inb(COM1 + 1);
  mask = mask | bit;
  outb(COM1 + 1, mask);
  //enable(); //Enables interrupts
}

void disableBit(int bit){
  //disable(); //Disables interrupts
  mask = inb(COM1 + 1);
  mask = mask & ~bit;
  outb(COM1 + 1, mask);
  //enable(); //Enables interrupts
}
