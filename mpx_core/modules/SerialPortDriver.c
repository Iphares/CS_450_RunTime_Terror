#include "DCB.h"
#include "PIC.h"
#include <core/serial.h>

// int init_DCB(int device) {
// 	outb(device + 1, 0x00); //disable interrupts
//   outb(device + 2, 0x00); //interrupt ID register
//   outb(device + 3, 0x80); //set line control register
//   outb(device + 4, 0x00); //Modem Control register
//   outb(device + 5, 0x30); //Line status register
//   outb(device + 6, 0xC7); //Modem status register
// 	outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
//   (void) inb(device); //read bit to reset port
// 	return NO_ERROR;
// }
u32int interruptAddress = NULL;

DCB	DCBlock ={
  .portFlag = P_CLOSE;
  .eventPtr = NULL;
  .status = I_STATUS; // Use I,R,W _STATUS for this variable
  .inBuffAddress = NULL;
  .inBuffCounter = 0;
  .outBufAddress = NULL;
  .outBuffCounter = 0;
  .ringBuffer = NULL;
  //These are the variables associated with the ringBuffer
  .inIndex = 0;
  .outIndex = 0;
  .rbCounter = 0;
};

int com_open(int *eflag_p, int baud_rate)  {

  if(eflag_p == NULL)  {
    return -101; //invalid (null) event flag pointer
  }
  else if(baud_rate <= 0) {
    return -102; //invalid baud rate divisor
  }
  //DCB.open 0 is open/ 1 close
  else if (DCBlock.portFlag == P_OPEN)  {
    return -103; //port already open
  }
  else  {
    // init_DCB(COM1);
    outb(COM1 + 1, 0x00); //disable interrupts
    outb(COM1 + 3, 0x80); //set line control register
		DCBlock.portFlag == P_OPEN
		DCBlock.eventPtr = eflag_p;
		interruptAddress = idt_get_gate();
		idt_set_gate(0x24, (u32int), 0x08, 0x8e);																		//COME BACK AFTER INTERRUPT HANDLER IS FINIHSED AND EDIT ADDRESS
    outb(COM1 + 0, 115200 / baud_rate); //set bsd least sig bit
    outb(COM1 + 1, (115200 / baud_rate)>>8); //brd most significant bit
		outb(COM1 + 3, 0x03); //lock
		outb(0x21, inb(0x21) & ~0x04); //Enable appropriate PIC mask level
    outb(COM1 + 4, 0x08); //enable interrupts, rts/dsr set											//STEP 9 IN DETAILED DOCUMENT
		outb(COM1 + 1, 0x01); // Enable input ready interrupts
    return 0;
  }
}

int com_close(){
	//DCB.open 1 is open/ 0 close
	if (DCBlock.portFlag == P_OPEN)  {
		return -201;// serial port not open
	}
	else  {
		DCBlock.portFlag = P_CLOSED;//clear open indicator in DCB
		outb(0x21, inb(0x21) | 0x04); //Disable appropriate level in the pic mask
		outb(COM1 + 6, 0x00); //Disable all interrupts in the ACC by loading 0 to modem status
		outb(COM1 + 1, 0x00); //^^ same with Interrupt Enable Register
		idt_set_gate(0x24, interruptAddress, 0x08, 0x8e); //restore interrupt vector address
  	return 0;
	}
}

int com_read(char* buf_p, int* count_p){
	//DCB.open 1 is open/ 0 close
	if (DCBlock.portFlag == P_CLOSED)  {
    		return -301; //serial port not open
  	}
	else if(strcmp(buf_p, NULL) == 0)  {
		return -302; //invalid buffer address
	}
	else if(count_p <= 0)  {																	//NEED TO FIX: WHAT IS COUNT ADDRESS? ADD OR CONDITION
		return -303; //invalid count address or count value
	}
	//status not idle
	else if(DCBlock.status != I_STATUS)  {
		return -304; //device busy
	}
 	else if(DCBlock.portFlag == P_OPEN && DCB.status == I_STATUS){
		int i = 0;
		DCBlock.inBuffAddress = buf_p; //Initialize buffer
		DCBlock.inBuffCounter = count_p;
		DCBlock.status = R_STATUS; // Set to read
		DCBlock.eventPtr = STARTING; // clear caller event flag		//NEED TO FIX: WHAT IS THE "CALLERS" EVENT FLAG? IS IT DIFFERENT FROM DCB EVENT FLAG?
	  outb(device + 1, 0x00); //disable interrupts
		while(DCBlock.ringBuffer[i] != '\0' || i <= count_p){
			buf_p[i] = DCBlock.ringBuffer[outIndex + i];
			DCBlock.ringBuffer[outIndex + i] = '\0';
			DCBlock.inBuffCounter = DCB.inBufferCounter + 1;
			i++;
			outIndex++;
			// *****if more characters are needed, return
		}
		outb(device + 4, 0x0B); //enable interrupts
		DCBlock.eventPtr = COMPLETE
		DCBlock.status = I_STATUS; //set to initialize
		DCBlock.rbCounter = count_p; // set buffer count to requesters count
		return 0;
	}
}


int com_write(char* buf_p, int* count_p){
	char hold;
	if (DCBlock.portFlag != P_OPEN)  {
		return -401; //serial port not open
	}
	else if(strcmp(buf_p, NULL) == 0)  {
		return -402; //invalid buffer address
	}
	else if(count_p <= 0 )  {
		return -403; //invalid count address or count value
	}
	//status not idle
	else if(DCBlock.status != I_STATUS)  {
		return -404; //device busy
	}
	else if(DCB.portFlag == P_OPEN && DCB.status == I_STATUS){
 		 DCBlock.outBuffAddress = buf_p; // set buff pointer
		 DCBlock.outBuffCounter = count_p; // set buff counter
		 DCBlock.eventPtr = NULL; // clear caller event flag ??
		 hold = buf_p[0]; // Not sure about pointer logic here
		 // first character of buffer into output register
		 enableBit(BIT2);
		 outb(COM1, hold);
		 // enable write interrupts by setting but 1 of Interrupt Enable Register
		 // set register to logical or of prev contents and 0x02
		 return 0;
  }
  else{
 		return 0;
  }
}
