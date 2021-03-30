List CMCBList ={
  .head = NULL
};

CMCB* AllocMem(int size){
  CMCB* start = CMCBList.head;
  while(start != NULL){
    if(start -> MEM_state == FREE){

    }
    else{
      start = start -> next;
    }
    return NULL;
  }
}

CMCB* FreeMem(u32int address){

}

List* getList() {
  return &CMCBList;
}
