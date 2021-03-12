#include <stdint.h>
#include <string.h>

#include <core/serial.h>
#include <core/io.h>

#include "../mpx_supt.h"
#include "../R1/userFunctions.h"


Queue ReadyQueue ={
  .count = 0,
  .head = NULL,
  .tail = NULL
};

Queue BlockedQueue ={
  .count = 0,
  .head = NULL,
  .tail = NULL
};

PCB* AllocatePCB()	{
	return sys_alloc_mem(sizeof(PCB));
}

void FreePCB(PCB* pcb)	{
	if(sys_free_mem(pcb) != -1)
		printf("\nMemory release successful \n");

	// Renable in R5 when sys_free_mem actually does something.
	//else
		//printf("\nMemory cannot be released from the requested pcb->\n");
}

PCB* SetupPCB(char Name[], int Class, int Priority)	{
	PCB* pcb = AllocatePCB();
	//R2 implementations updated in R3
	//pcb->stackTop = 1024 + pcb->stack;
	//R3 implementation
	pcb->stackTop = 1024 + pcb->stack - sizeof(struct context);
	memset(pcb->stack, 0, 1024);
	pcb->prev = NULL;
	pcb->next = NULL;
	pcb->ReadyState = READY;
	pcb->SuspendedState = NO;
	pcb->Priority = Priority;
	strcpy(pcb->Process_Name,Name);
	pcb->Process_Class = Class;
	return pcb;
}

Queue* getReady() {
  return &ReadyQueue;
}

Queue* getBlocked() {
  return &BlockedQueue;
}


PCB* FindPCB(char Name[])	{
  // assign temp to start of ReadyQueue
  PCB* tempR = ReadyQueue.head;
  PCB* tempB = BlockedQueue.head;
  // while node exists
	while(tempR != NULL )	{
		if(strcmp(tempR -> Process_Name,Name) == 0)
			return tempR;

    tempR = tempR -> next;
  }
  while(tempB != NULL )	{
		if(strcmp(tempB -> Process_Name,Name) == 0)
			return tempB;

    tempB = tempB -> next;
  }
  // returns NULL if node does not exist
  return NULL;
}


void InsertPCB(PCB* pcb)	{
  if(pcb -> ReadyState == READY) {
    PCB* start = ReadyQueue.head;
    if(start == NULL) {
      ReadyQueue.head = pcb;
      ReadyQueue.tail = pcb;
    }
    else  {
      //ReadyQueue has highest priority at head
      while((start -> Priority >= pcb -> Priority) && start -> next != NULL)
        start = start -> next;

      if(start == ReadyQueue.head)	{
        if(pcb -> Priority > start -> Priority)	{
          ReadyQueue.head = pcb;
          pcb->next = start;
          start->prev = pcb;
        }
        else	{
          start->next = pcb;
          pcb->prev = start;
        }
      }
      else if(start -> Priority >= pcb -> Priority)	{
        pcb -> prev = start;
        start -> next = pcb;
        ReadyQueue.tail = pcb;
      }
      else if(start -> prev != NULL)  {
        pcb -> next = start;
        pcb -> prev = start -> prev;
        start -> prev = pcb;
        pcb -> prev -> next = pcb;
      }
    }
  }
  else if(pcb -> ReadyState == BLOCKED){
    PCB* startb = BlockedQueue.head;
    if(startb == NULL) {
      BlockedQueue.head = pcb;
      BlockedQueue.tail = pcb;
    }
    else  {
      BlockedQueue.tail -> next = pcb;
      pcb ->prev = BlockedQueue.tail;
      BlockedQueue.tail = pcb;
    }
  }
}

void RemovePCB(PCB* pcb)	{
  Queue* queue;
  if(pcb -> ReadyState == READY)
    queue = &ReadyQueue;
  else
    queue = &BlockedQueue;

  if(queue -> head == pcb)  {
    if(pcb -> next != NULL) {
      queue -> head = pcb -> next;
      pcb -> next -> prev = NULL;
      pcb -> next = NULL;
    }
    else
      queue -> head = NULL;
  }
  else if(pcb -> next != NULL && pcb -> prev != NULL)  {
    pcb -> prev -> next = pcb -> next;
    pcb -> next -> prev = pcb -> prev;
    pcb -> next = NULL;
    pcb -> prev = NULL;
  }
  else  {
    queue -> tail = pcb -> prev;
    pcb -> prev -> next = NULL;
  }
}
