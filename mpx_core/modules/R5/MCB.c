#include <stdint.h>
#include <string.h>

#include <core/serial.h>
#include <core/io.h>
#include <mem/heap.h>

#include "../mpx_supt.h"
#include "MCB.h"
#include "../R1/userFunctions.h"


MemList CMCBList ={
  .head = NULL
};

u32int AllocMem(u32int size){
  CMCB* start = CMCBList.head;
  while(start != NULL){
    if(start -> MEMState == FREE){
      if(start->size >= size + sizeof(CMCB)){
        CMCB* new = (CMCB*) start->address + size;
        new->size = start->size - size - sizeof(CMCB);
        new->address = start->address + size + sizeof(CMCB);
        new->prev = start;
        new->MEMState = FREE;
      	start -> size = size;
      	start -> MEMState = ALLOC;
        if(start->next != NULL){
          new->next = start->next;
        }
        else{
          new->next = NULL;
        }
        start->next = new;
        return (u32int)start->address;
      }
      else{
        //moves to next MCB
        start = start -> next;
      }
    }
    else{
      //moves to next MCB
      start = start -> next;
    }
    //return null if memory is full/doesn't have enough space
  }
  return NULL;
}

int FreeMem(void *address){
  CMCB* start = CMCBList.head;
  while(start != NULL){
    if(start -> address == (u32int)address){
      if(start == CMCBList.head){//if head of list
        if(start->next != NULL && start->next->MEMState == FREE){//has free next block
          //Merge both blocks
          start->MEMState = FREE;
          start->size += start->next->size + sizeof(CMCB);
          if(start->next->next != NULL){
            start->next->next->prev = start;
            start->next = start->next->next;
          }
          else{
            start->next = NULL;
          }
        }
        else{
          //Free this block only
          start->MEMState = FREE;
        }
        return 0;
      }
      else if(start->next != NULL){//if not head and has a next reference
        if(start->prev->MEMState == FREE && start->next->MEMState == FREE){//if prev and next are free
          //Merge all 3
          start->prev->size += start->size + start->next->size + 2*sizeof(CMCB);
          if(start->next->next != NULL){
            start->next->next->prev = start->prev;
            start->prev->next = start->next->next;
          }
          else{
            start->prev->next = NULL;
          }
        }
        else if(start->prev->MEMState == FREE){//else if just prev is free
          //Merge both blocks
          start->prev->size += start->size + sizeof(CMCB);
          start->next->prev = start->prev;
          start->prev->next = start->next;
        }
        else if(start->next->MEMState == FREE){//else if just next is free
          //Merge both blocks
          start->MEMState = FREE;
          start->size += start->next->size + sizeof(CMCB);
          if(start->next->next != NULL){
            start->next->next->prev = start;
            start->next = start->next->next;
          }
          else{
            start->next = NULL;
          }
        }
        else{
          //Free this block only
          start->MEMState = FREE;
        }
        return 0;
      }
      else{
        if(start->prev->MEMState == FREE){//if prev is free
          //Merge both blocks
          start->prev->size += start->size + sizeof(CMCB);
          start->next->prev = start->prev;
          start->prev->next = start->next;
        }
        else{
          //Free this block only
          start->MEMState = FREE;
        }
        return 0;
      }
    }
    //address did not match; go to next reference
    start = start->next;
  }
  //did not match any address
  return 1;
}

MemList* getMemList() {
  return &CMCBList;
}


void init_heap(u32int size){
	//UPDATE TO KMALLOC AFTER TESTING

	CMCB* cmcb = (CMCB*) kmalloc(sizeof(CMCB) + size);
	cmcb -> size = size;
	cmcb -> prev = NULL;
	cmcb -> next = NULL;
	cmcb -> address = (u32int) cmcb + sizeof(CMCB);
	cmcb -> MEMState = FREE;
	// set list head
	CMCBList.head = cmcb;
  // printf(itoa(size));
}
