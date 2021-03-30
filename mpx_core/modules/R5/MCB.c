#define FREE 0
#define ALLOC 1

List* AllocMem(){

}

List* FreeMem(){

}

CMCB* FindMCB(char Name[]){
  CMCB* tempB = BlockedQueue.head;
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
