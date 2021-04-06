#include "DCB.h"
#include "PIC.h"
#include <core/serial.h>

int init_DCB(int device) {
	outb(device + 1, 0x00); //disable interrupts
  outb(device + 2, 0x00); //interrupt ID register
  outb(device + 3, 0x00); //set line control register
  outb(device + 4, 0x00); //Modem Control register
  outb(device + 5, 0x30); //Line status register
  outb(device + 6, 0xC7); //Modem status register
	outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
  (void) inb(device); //read bit to reset port
	//return NO_ERROR;
}

int com_open (int *eflag_p, int baud_rate)  {

  if(eflag_p == NULL)  {
    return -101; //invalid (null) event flag pointer
  }
  else if(baud_rate <= 0) {
    return -102; //invalid baud rate divisor
  }
  //DCB.open 0 is open/ 1 close
  else if (DCB.portFlag == P_OPEN)  {
    return -103; //port already open
  }
  else  {

    init_DCB(COM1);
    outb(device + 1, 0x00); //disable interrupts
    outb(device + 3, 0x80); //set line control register
		DCB.eventPtr = eflag_p;
    outb(device + 0, 115200 / baud_rate); //set bsd least sig bit
    outb(device + 1, 0x00); //brd most significant bit
    outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
    return 0;
  }
}

int com_close (void){
	//DCB.open 1 is open/ 0 close
	if (DCB.portFlag == P_OPEN)  {
		return -201;// serial port not open
	}
	else  {
		DCB.portFlag = NULL;//clear open indicator in DCB
		//Disable appropriate level in the pic mask

  	//load 0 to Modem register and interrupt enable register
		outb(device + 4, 0x00); //Modem Control register
		outb(device + 4, 0x00); //enable interrupts
  	//restore interrupt vector address

  	return 0;
	}
}

int com_read (char* buf_p, int* count_p){
	//DCB.open 1 is open/ 0 close
	if (DCB.portFlag == P_CLOSED)  {
    		return -301; //serial port not open
  	}
	else if(strcmp(buf_p, NULL) == 0)  {
		return -302; //invalid buffer address
	}
	else if(count_p <= 0 )  {
		return -303; //invalid count address or count value
	}
	//status idle 0 or busy 1
	else if(DCB.status != I_STATUS)  {
		return -304; //device busy
	}
 	else if(DCB.portFlag == P_OPEN && DCB.status == I_STATUS){
			int i = 0;
			DCB.inBuffAddress = buf_p; //Initualize buffer ??
			DCB.status = R_STATUS; // Set to read
			DCB.eventPtr = NULL; // clear caller event flag
			DCB.inBuffCounter = 0; //this is probs wrong too
	    outb(device + 1, 0x00); //disable interrupts
			while(DCB.ringBuffer[0] != '\0' || DCB.inBuffCounter <= count_p){ //this could be really wrong
				*buf_p = DCB.ringBuffer[i];
				DCB.ringBuffer[i] = '\0';
				DCB.inBuffCounter = DCB.inBufferCounter + 1;
				i++;

				// *****if more characters are needed, return
			}
			outb(device + 4, 0x0B); //enable interrupts
			DCB.portFlag = P_CLOSE; //close portFlag *** Not sure if its supposed to be open or closed
			DCB.status = I_STATUS; //set to initilaise
			count_p = inBuffCounter; // set buffer count to requesters count
			return 0;
	}
}


int com_write (char* buf_p, int* count_p){
	char hold;
	if (DCB.portFlag == P_OPEN)  {
    		return -401; //serial port not open
  	}
	else if(strcmp(buf_p, NULL) == 0)  {
		return -402; //invalid buffer address
	}
	else if(count_p <= 0 )  {
		return -403; //invalid count address or count value
	}
	//status idle 0 or busy 1
	else if(DCB.status == I_STATUS)  {
		return -404; //device busy
	}
	else if(DCB.portFlag == P_OPEN && DCB.status == I_STATUS){
 		 DCB.inBuffAddress = buf_p; // set buff pointer??
		 DCB.outBuffCounter = count_p; // set buff counter
		 DCB.eventPtr = NULL; // clear caller event flag ??
		 hold = buf_p[0]; // Not sure about pointer logic here
		 // first character of buffer into output register
		 // outb(output, hold)

		 // enable write interrupts by setting but 1 of Interrupt Enable Register
		 // set register to logical or of prev contents and 0x02



  }
  else{
 	 return 0;
  }
}
