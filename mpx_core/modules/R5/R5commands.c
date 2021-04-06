#include <stdint.h>
#include <string.h>

#include <core/serial.h>
#include <core/io.h>


#include "../mpx_supt.h"
#include "../R1/userFunctions.h"
#include "MCB.h"


//Temporary
void Init_Heap(u32int size)	{
	init_heap(size);
}
//Temporary
void Alloc_Mem(u32int size)	{
	AllocMem(size);
}
//Temporary
void Free_Mem(u32int address)	{
	FreeMem(address);
}
//Temporary
void IsEmpty()	{
	if(getMemList()->head->MEMState == 0 && getMemList()->head->next == NULL)	{
		printf("true");	
	}
	else
		printf("false");	
}

void ShowFree()	{
	if(getMemList()->head->MEMState == 0)	{
			 printf("\x1b[32m""\n All memory within the Heap is freed. \n""\x1b[0m");
		}
	 else	{
	   int AddressBlock, Size;

			  char Free[] = "\x1B[34m""Free Blocks: \n""\x1b[0m";
			  char caddr[] = "Address: ";
			  char csize[] = "Size: ";
			  char line[] = "\n";
			  
	      //sys_req(WRITE, COM1, Free, strlen(Free));

			  CMCB* block = getMemList()->head;

			  if(block->next == NULL && getMemList()->head->MEMState == 0)	{
				AddressBlock = block->address;
				Size = block->size;
				
			 	printf(Free);
				printf(caddr);
				printf(csize);
				printf(line);

				    if(block->address == 0)  {
				      printf("0");
				    }
				    else  {
				    printf(itoa(AddressBlock));
				      //sys_req(WRITE, COM1, addr, strlen(addr));
				    }
				    printf(line);


				    printf(csize);
				    if(block->size == 0)  {
				      printf("0");
				    }
				    else  {
				    	printf(itoa(Size));
				      //sys_req(WRITE, COM1, size, strlen(size);
				    }
				    printf(line);
				    printf("\n\n");

			  }
			  else	{
				while(block != NULL)	{
					if(getMemList()->head->MEMState == 0)	{
						AddressBlock = block->address;
						Size = block->size;

						printf(caddr);
						printf(csize);
						printf(line);

						    if(block->address == 0)  {
						      printf("0");
						    }
						    else  {
						    	printf(itoa(AddressBlock));	
						        //sys_req(WRITE, COM1, itoa(AddressBlock), strlen(AddressBlock));
						    }
						    printf(line);

						    printf(csize);
						    if(block->size == 0)  {
						      printf("0");
						    }
						    else  {
						    	printf(itoa(Size));
						        //sys_req(WRITE, COM1, itoa(Size), strlen(Size));
						    }
						    printf(line);
					}
					block = block->next;
				}
			 }
		}
}
void ShowAlloc()	{
	if(getMemList()->head->MEMState == 1)	{
			 printf("\x1b[32m""\n All memory within the Heap is allocated. \n""\x1b[0m");
	}
	 else	{
	   int AddressBlock, Size;

			  char Alloc[] = "\x1B[34m""Allocated Blocks: \n""\x1b[0m";
			  char caddr[] = "Address: ";
			  char csize[] = "Size: ";
			  char line[] = "\n";
		printf(Alloc);	  
	      //sys_req(WRITE, COM1, Alloc, strlen(Alloc) );

			  CMCB* block = getMemList()->head;

			  if(block->next == NULL && getMemList()->head->MEMState == 1)	{
				AddressBlock = block->address;
				Size = block->size;

				printf(caddr);
				printf(csize);
				printf(line);

				    if(block->address == 0)  {
				      printf("0");
				    }
				    else  {
				    	printf(itoa(AddressBlock));
				        //sys_req(WRITE, COM1, itoa(AddressBlock), strlen(AddressBlock));
				    }
				    printf(line);


				    printf(csize);
				    if(block->size == 0)  {
				      printf("0");
				    }
				    else  {
				    	printf(itoa(Size));
				        //sys_req(WRITE, COM1, itoa(Size), strlen(Size));
				    }
				    printf(line);
				    printf("\n\n");

			  }
			  else	{
				while(block != NULL)	{
					if(getMemList()->head->MEMState == 1)	{
						AddressBlock = block->address;
						Size = block->size;

						printf(caddr);
						printf(csize);
						printf(line);

						    if(block->address == 0)  {
						      printf("0");
						    }
						    else  {
						    	printf(itoa(AddressBlock));
						        //sys_req(WRITE, COM1, itoa(AddressBlock), strlen(AddressBlock));
						    }
						    printf(line);

						    printf(csize);
						    if(block->size == 0)  {
						      printf("0");
						    }
						    else  {
						    	printf(itoa(Size));
						        //sys_req(WRITE, COM1, itoa(Size), strlen(Size));
						    }
						    printf(line);
					}
					block = block->next;
				}
			 }
		}
}
