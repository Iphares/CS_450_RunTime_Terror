#define BIT0 1   // 0 0 0 0 0 0 0 1
#define BIT1 2   // 0 0 0 0 0 0 1 0
#define BIT2 4   // 0 0 0 0 0 1 0 0
#define BIT3 8   // 0 0 0 0 1 0 0 0
#define BIT4 16  // 0 0 0 1 0 0 0 0
#define BIT5 32  // 0 0 1 0 0 0 0 0
#define BIT6 64  // 0 1 0 0 0 0 0 0
#define BIT7 128 // 1 0 0 0 0 0 0 0

//enableBit would "& bit"
//disableBit would "| bit"

void enableBit(int bit);
void disableBit(int bit);


    // ...                                         |
    // int mask;                                   | defines temp mask variable
    // ...                                         |
    // disable();                                  | Disables interrupts
    // mask = inb(PIC_MASK);                       | uses temp mask variable space to save current mask
    // mask = mask & ~0x80; //10000000 -> 01111111 | performs bitwise operation
    // outb(PIC_MASK, mask);                       | pushes new mask to the current mask register
    // enable();                                   | Enables interrupts
