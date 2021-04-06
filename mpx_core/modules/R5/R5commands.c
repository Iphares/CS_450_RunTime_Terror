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
	FreeMem((void *)address);
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
	int AddressBlock, Size;

	char Free[] = "\x1B[34m""Free Blocks: \n""\x1b[0m";
	char caddr[] = "Address: ";
	char csize[] = "Size: ";

	printf(Free);
	//sys_req(WRITE, COM1, Free, strlen(Free));

	CMCB* block = getMemList()->head;

	while(block != NULL)	{
		if(block->MEMState == 0)	{
			AddressBlock = block->address;
			Size = block->size;

			printf(caddr);
			if(block->address == 0)  {
				printf("0");
			}
			else  {
				printf(itoa(AddressBlock));
			  //sys_req(WRITE, COM1, itoa(AddressBlock), strlen(AddressBlock));
			}
			printf("\n");

			printf(csize);
			if(block->size == 0)  {
				printf("0");
			}
			else  {
				printf(itoa(Size));
			  //sys_req(WRITE, COM1, itoa(Size), strlen(Size));
			}
			printf("\n\n");
		}
		block = block->next;
	}
	printf("\n");
}


void ShowAlloc()	{
	int AddressBlock, Size;

	char Alloc[] = "\x1B[34m""Allocated Blocks: \n""\x1b[0m";
	char caddr[] = "Address: ";
	char csize[] = "Size: ";
	printf(Alloc);
	//sys_req(WRITE, COM1, Alloc, strlen(Alloc) );

	CMCB* block = getMemList()->head;

	while(block != NULL)	{
		if(block->MEMState == 1)	{
			AddressBlock = block->address;
			Size = block->size;

			printf(caddr);
			if(block->address == 0)  {
				printf("0");
			}
			else  {
				printf(itoa(AddressBlock));
				//sys_req(WRITE, COM1, itoa(AddressBlock), strlen(AddressBlock));
			}
			printf("\n");

			printf(csize);
			if(block->size == 0)  {
				printf("0");
			}
			else  {
				printf(itoa(Size));
				//sys_req(WRITE, COM1, itoa(Size), strlen(Size));
			}
			printf("\n\n");
		}
		block = block->next;
	}
	printf("\n");
}
