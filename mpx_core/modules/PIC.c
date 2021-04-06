#include "PIC.h"

void enableBit(int bit){
  //disable(); //Disables interrupts
  mask = inb(PIC_MASK);
  mask = mask & ~bit;
  outb(PIC_MASK, mask);
  //enable(); //Enables interrupts
}

void disableBit(int bit){
  //disable(); //Disables interrupts
  mask = inb(PIC_MASK);
  mask = mask | bit;
  outb(PIC_MASK, mask);
  //enable(); //Enables interrupts
}
