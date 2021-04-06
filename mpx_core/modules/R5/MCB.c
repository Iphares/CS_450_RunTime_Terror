List CMCBList ={
  .head = NULL
};

CMCB* AllocMem(u32int size){
  if(CMCBList.head == NULL){//heap is not initialized
    //????????????????????
  }
  else{//heap is initialized
    CMCB* start = CMCBList.head;
    while(start != NULL){
      if(start -> MEM_state == FREE){
        if(start->size >= size){
          //Split and Allocate memory
          CMCB* new = malloc(sizeof(CMCB) + size);
        	new -> size = sizeof(CMCB) + size;
        	new -> prev = NULL;
        	new -> next = NULL;
        	new -> Process_name[10];
        	new -> address = (u32int) cmcb;
        	new -> MEMState = ALLOC;
          //Moving start address and size
          start->size = start->size-size;
          start->address += new->size
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
}

CMCB* FreeMem(u32int address){
  CMCB* start = CMCBList.head;
  while(start != NULL){
    if(start -> address == address){
      if(start == CMCBList.head){//if head of list
        if(start->next != NULL && start->next->MEMEState == FREE){//has free next block
          //Merge both blocks
          start->MEMState = FREE
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
          start->MEMState = FREE;
        }
      }
      else if(start->next != NULL){//if not head and has a next reference
        if(start->prev->MEMState == FREE && start->next->MEMState == FREE){//if prev and next are free
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
        else if(start->prev->MEMState == FREE){//else if just prev is free
          //Merge both blocks
          start->prev->size += start->size;
          start->next->prev = start->prev;
          start->prev->next = start->next;
        }
        else if(start->next->MEMEState == FREE){//else if just next is free
          //Merge both blocks
          start->MEMState = FREE
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
          start->MEMState = FREE;
        }
      }
      else{
        if(start->prev->MEMState == FREE){//if prev is free
          //Merge both blocks
          start->prev->size += start->size;
          start->next->prev = start->prev;
          start->prev->next = start->next;
        }
        else{
          //Free this block only
          start->MEMState = FREE;
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
