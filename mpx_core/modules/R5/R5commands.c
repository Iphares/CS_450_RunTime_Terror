




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
	if(CMCBList()->head.MEMState == 0 && CMCBList()->head->next == null)	{
		printf("true");	
	}
	else
		printf("false");	
}

void ShowFree()	{
	if(CMCBList()->head.MEMState == 0)	{
			 printf("\x1b[32m""\n All memory within the Heap is freed. \n""\x1b[0m");
		}
	 else	{
	   int AddressBlock, Size;

			  char Free[] = "\x1B[34m""Free Blocks: \n""\x1b[0m";
			  char caddr[] = "Address: ";
			  char csize[] = "Size: ";
			  char line[] = "\n";
			  check = 64;
	      sys_req(WRITE, COM1, free, &check );

			  CMCB* block = CMCBList()->head;

			  if(block->next == NULL && CMCBList()->head.MEMState == 0)	{
				AddressBlock = block->address;
				Size = block->size;

				printf(caddr);
				printf(csize);
				printf(line);

				    printf(caddr
				    if(block->address == 0)  {
				      printf("0");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(AddressBlock), &check);
				    }
				    printf(line);


				    printf(csize);
				    if(block->size == 0)  {
				      printf("0");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(size), &check);
				    }
				    printf(line);
				    printf("\n\n");

			  }
			  else	{
				while(block != NULL)	{
					if(CMCBList()->head.MEMState == 0)	{
						AddressBlock = block->address;
						Size = block->size;

						printf(caddr);
						printf(csize);
						printf(line);

						    printf(caddr
						    if(block->address == 0)  {
						      printf("0");
						    }
						    else  {
						      sys_req(WRITE, COM1, itoa(AddressBlock), &check);
						    }
						    printf(line);

						    printf(csize);
						    if(block->size == 0)  {
						      printf("0");
						    }
						    else  {
						      sys_req(WRITE, COM1, itoa(size), &check);
						    }
						    printf(line);
					}
					block = block->next;
				}
			 }
		}
}
void ShowAlloc()	{
	if(CMCBList()->head.MEMState == 1)	{
			 printf("\x1b[32m""\n All memory within the Heap is allocated. \n""\x1b[0m");
	}
	 else	{
	   int AddressBlock, Size;

			  char Free[] = "\x1B[34m""Free Blocks: \n""\x1b[0m";
			  char caddr[] = "Address: ";
			  char csize[] = "Size: ";
			  char line[] = "\n";
			  check = 64;
	      sys_req(WRITE, COM1, free, &check );

			  CMCB* block = CMCBList()->head;

			  if(block->next == NULL && CMCBList()->head.MEMState == 1)	{
				AddressBlock = block->address;
				Size = block->size;

				printf(caddr);
				printf(csize);
				printf(line);

				    printf(caddr
				    if(block->address == 0)  {
				      printf("0");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(AddressBlock), &check);
				    }
				    printf(line);


				    printf(csize);
				    if(block->size == 0)  {
				      printf("0");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(size), &check);
				    }
				    printf(line);
				    printf("\n\n");

			  }
			  else	{
				while(block != NULL)	{
					if(CMCBList()->head.MEMState == 1)	{
						AddressBlock = block->address;
						Size = block->size;

						printf(caddr);
						printf(csize);
						printf(line);

						    printf(caddr
						    if(block->address == 0)  {
						      printf("0");
						    }
						    else  {
						      sys_req(WRITE, COM1, itoa(AddressBlock), &check);
						    }
						    printf(line);

						    printf(csize);
						    if(block->size == 0)  {
						      printf("0");
						    }
						    else  {
						      sys_req(WRITE, COM1, itoa(size), &check);
						    }
						    printf(line);
					}
					block = block->next;
				}
			 }
		}
}
