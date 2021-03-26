




//Temporary
void Init_Heap()	{

}
//Temporary
void Alloc_Mem()	{

}
//Temporary
void Free_Mem()	{

}
//Temporary
void IsEmpty()	{

}

void ShowFree()	{
if(FreeMem()->head == NULL)	{
		 printf("\x1b[32m""\n The Free block Queue is empty \n""\x1b[0m");
	}
 else	{
   int AddressBlock, Size;
   
		  char Free[] = "\x1B[34m""Free Queue: \n""\x1b[0m";
		  char caddr[] = "Address: ";
		  char csize[] = "Size: ";
		  char line[] = "\n";
		  check = 15;
      sys_req(WRITE, COM1, free, &check );

   
   
   
   
   
   
   
		  MCB* pcb = getBlocked()->head;

		  if(pcb->next == NULL)	{
		  	class = pcb->Process_Class;
		    	strcpy(name,pcb->Process_Name);
		    	state = pcb->ReadyState;
		    	status = pcb->SuspendedState;
		    	prior = pcb->Priority;

		    	printf(cname);
		    	printf(name);
		    	printf(line);

			    printf(cclass);
			    if(pcb->Process_Class == 0)  {
			      printf("0");
			    }
			    else  {
			      sys_req(WRITE, COM1, itoa(class), &check);
			    }
			    printf(line);

			    printf(cstate);
			    if(pcb->ReadyState == 0)  {
			      printf("0");
			    }
			    else  {
			      sys_req(WRITE, COM1, itoa(state), &check);
			    }
			    printf(line);

			    printf(cstatus);
			    if(pcb->SuspendedState == 0)  {
			      printf("0");
			    }
			    else  {
			      sys_req(WRITE, COM1, itoa(status), &check);
			    }
			    printf(line);

			    printf(cprior);
			    if(pcb->Priority == 0)  {
			      printf("0");
			      printf("\n\n");
			    }
			    else  {
			      sys_req(WRITE, COM1, itoa(prior), &check);
			      printf("\n\n");
			    }
		  }
		  else	{
		  	while(pcb != NULL)	{
		  		class = pcb->Process_Class;
			    	strcpy(name,pcb->Process_Name);
			    	state = pcb->ReadyState;
			    	status = pcb->SuspendedState;
			    	prior = pcb->Priority;

			    	printf(cname);
			    	printf(name);
			    	printf(line);

				    printf(cclass);
				    if(pcb->Process_Class == 0)  {
				      printf("0");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(class), &check);
				    }
				    printf(line);

				    printf(cstate);
				    if(pcb->ReadyState == 0)  {
				      printf("0");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(state), &check);
				    }
				    printf(line);

				    printf(cstatus);
				    if(pcb->SuspendedState == 0)  {
				      printf("0");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(status), &check);
				    }
				    printf(line);

				    printf(cprior);
				    if(pcb->Priority == 0)  {
				      printf("0");
				      printf("\n\n");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(prior), &check);
				      printf("\n\n");
				    }
		  		pcb = pcb->next;
		 	}
		 }
	}
}
void ShowAlloc()	{

}
