List CMCBList ={
  .head = NULL
};

List* AllocMem(int size){

}

List* FreeMem(u32int address){

}

CMCB* FindMCB(char Name[]){
  CMCB* start = CMCBList.head;
  // while CMCB exists
  while(start != NULL )	{
    if(strcmp(start -> mem_name,Name) == 0)
      return start;

    start = start -> next;
  }
  // returns NULL if node does not exist
  return NULL;
}
