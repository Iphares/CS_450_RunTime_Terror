

void init_DCB() {
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
	
  if(strcmp(eflag_p, NULL) == 0)  { 
    return -101; //invalid (null) event flag pointer
  }
  else if(baud_rate <= 0) {    
    return -102; //invalid baud rate divisor
  }
  //DCB.open 1 is open/ 0 close
  else if (DCB.open == 1)  {
    return -103; //port already open
  }
  else  {
	  
    init_DCB(); 
    outb(device + 1, 0x00); //disable interrupts
    outb(device + 3, 0x80); //set line control register
    outb(device + 0, 115200 / baud_rate); //set bsd least sig bit
    outb(device + 1, 0x00); //brd most significant bit	
    outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
    return 0;
  }
}

int com_close (void){
	//DCB.open 1 is open/ 0 close
	if (DCB.open == 0)  {
		return -201;// serial port not open
	}
	else  {
		dcb.open = NULL;//clear open indicator in DCB
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
	if (DCB.open == 0)  {
    		return -301; //serial port not open
  	}
	else if(strcmp(buf_p, NULL) == 0)  {
		return -302; //invalid buffer address
	}
	else if(count_p <= 0 )  {
		return -303; //invalid count address or count value
	}
	//status idle 0 or busy 1
	else if(DCB.status == 1)  {
		return -304; //device busy
	}
 	else  {
		//set status register to busy
		
	
		return 0;
	}
}


int com_write (char* buf_p, int* count_p){
  
}


