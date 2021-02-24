#include <stdint.h>
#include <string.h>

#include <core/serial.h>
#include <core/io.h>

#include "../mpx_supt.h"
#include "../R1/userFunctions.h"
#include "PCB.h"

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
	pcb->stackTop = 1024 + pcb->stack;
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
    // check for PCB Name
		if(strcmp(tempR -> Process_Name,Name) == 0)
			return tempR;
    // else if end of ReadyQueue, switch to BlockedQueue
    //else if(temp == ReadyQueue.tail)
      //temp = BlockedQueue.head;
    // else switch to next node if exists
    else if(tempR -> next != NULL)
      tempR = tempR -> next;
  }
  while(tempB != NULL )	{
    // check for PCB Name
		if(strcmp(tempB -> Process_Name,Name) == 0)
			return tempB;
    // else if end of ReadyQueue, switch to BlockedQueue
    //else if(temp == ReadyQueue.tail)
      //temp = BlockedQueue.head;
    // else switch to next node if exists
    else if(tempB -> next != NULL)
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
      while(start -> next -> Priority >= start -> Priority)
        start = start -> next;
      if(start -> next != NULL && start -> prev != NULL)  {
        pcb -> prev = start;
        pcb -> next = start -> next;
        start -> next = pcb;
        pcb -> next -> prev = pcb;
      }
      else{
        pcb -> prev = start;
        start -> next = pcb;
        ReadyQueue.tail = pcb;
      }
    }
  }
  else if(pcb -> ReadyState == BLOCKED){
    PCB* startb = BlockedQueue.head;
    if(startb == NULL) {
      ReadyQueue.head = pcb;
      ReadyQueue.tail = pcb;
    }
    else  {
      BlockedQueue.tail -> next = pcb -> prev;
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
  else{
    if(pcb -> next != NULL && pcb -> prev != NULL)  {
      pcb -> prev -> next = pcb -> next -> prev;
      pcb -> next = NULL;
      pcb -> prev = NULL;
    }
    else if(pcb -> next != NULL)  {
      queue -> tail = pcb -> prev;
      pcb -> prev = NULL;
    }
  }
}
