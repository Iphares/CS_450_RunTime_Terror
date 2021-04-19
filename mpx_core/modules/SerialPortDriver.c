

void init_DCB() {
        outb(device + 2, 0x00); //interrupt ID register
        outb(device + 3, 0x00); //set line control register
       
        outb(device + 4, 0x00); //Modem Control register
        outb(device + 5, 0x30); //Line status register
        outb(device + 6, 0xC7); //Modem status register
        (void) inb(device); //read bit to reset port
	//return NO_ERROR;
}


int com_open (int *eflag_p, int baud_rate)  {
	
  if()  {
    
    return -101;
  }
  else if() {
    
    return -102;
  }
  //DCB.open 1 is open/ 0 close
  else if (DCB.open == 1)  {
    return -103;
  }
  else  {
	  
    init_DCB();  
    outb(device + 3, 0x80); //set line control register
	  
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
	else if()  {
		return -302; //invalid buffer address
	}
	else if()  {
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


