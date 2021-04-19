

void init_DCB() {
  DCB* dcb = (DCB*) kmalloc(sizeof(DCB));
  //registers
  
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
    
    return 0;
  }
    


}

int com_close (void){
  


}

int com_read (char* buf_p, int* count_p){
  
}


int com_write (char* buf_p, int* count_p){
  
}


