#include <stdint.h>
#include <string.h>

#include <core/serial.h>
#include <core/io.h>

#include "../mpx_supt.h"
#include "../R1/userFunctions.h"
#include "MCB.h"

List CMCBList ={
  .head = NULL
};

CMCB* AllocMem(u32int size){
  CMCB* start = CMCBList.head;
  while(start != NULL){
    if(start -> MEM_state == FREE){
      if(start->size >= size){
        CMCB* new = start->address + start->size;
        new->size = start->size - size - sizeof(CMCB);
        new->address = start->address + start->size + sizeof(CMCB);
      	start -> size = size;
      	start -> MEM_state = ALLOC;
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
    return NULL;
  }
}

CMCB* FreeMem(u32int address){
  CMCB* start = CMCBList.head;
  while(start != NULL){
    if(start -> address == address){
      if(start == CMCBList.head){//if head of list
        if(start->next != NULL && start->next->MEM_state == FREE){//has free next block
          //Merge both blocks
          start->MEM_state = FREE
          start->size += start->next->size;
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
          start->MEM_state = FREE;
        }
      }
      else if(start->next != NULL){//if not head and has a next reference
        if(start->prev->MEM_state == FREE && start->next->MEM_state == FREE){//if prev and next are free
          //Merge all 3
          start->prev->size += start->size + start->next->size;
          if(start->next->next != NULL){
            start->next->next->prev = start->prev;
            start->prev->next = start->next->next;
          }
          else{
            start->prev->next = NULL;
          }
        }
        else if(start->prev->MEM_state == FREE){//else if just prev is free
          //Merge both blocks
          start->prev->size += start->size;
          start->next->prev = start->prev;
          start->prev->next = start->next;
        }
        else if(start->next->MEM_state == FREE){//else if just next is free
          //Merge both blocks
          start->MEM_state = FREE
          start->size += start->next->size;
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
          start->MEM_state = FREE;
        }
      }
      else{
        if(start->prev->MEM_state == FREE){//if prev is free
          //Merge both blocks
          start->prev->size += start->size;
          start->next->prev = start->prev;
          start->prev->next = start->next;
        }
        else{
          //Free this block only
          start->MEM_state = FREE;
        }
      }
    }
    //address did not match; go to next reference
    start->start->next;
  }
  //no matching address
  return -1;
}

List* getList() {
  return &CMCBList;
}
