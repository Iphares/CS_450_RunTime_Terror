#DEFINE 1KMEM 1024;
#DEFINE 2KMEM 2048;
#DEFINE 3KMEM 4096;
#DEFINE 4KMEM 8192;
#DEFINE 5KMEM 16384;

typedef struct Queue	{
  int count;
  PCB *head;
  PCB *tail;
};

static struct Queue ReadyQueue {
  sys_alloc_mem(sizeof(Queue));
  ReadyQueue->count = 0;
  ReadyQueue->head = NULL;
  ReadyQueue->tail = NULL;
}

static struct Queue BlockedQueue {
  sys_alloc_mem(sizeof(Queue));
  BlockedQueue->count = 0;
  BlockedQueue->head = NULL;
  BlockedQueue->tail = NULL;
}

typedef struct PCB	{
	unsigned char stack[1KMEM];
	unsigned char* stackTop;
	struct PCB* prev;
	struct PCB* next;
	char Process_Name[10];
	int Process_Class;
  int Priority;
  int ReadyState;
	int SuspendedState;
};

PCB* AllocatePCB()	{
	return sys_alloc_mem(sizeof(PCB));
}

void FreePCB(*PCB)	{
	if(sys_free_mem(PCB) != -1)
		printf("\nMemory release successful \n");
	else
		printf("\nMemory cannot be released from the requested pcb->\n");
}

PCB* SetupPCB(char[] Name, int Class, int Priority)	{
	PCB* pcb-> = AllocatePCB();
	pcb->stackTop = 1024 + pcb->stack;
	memset(pcb->stack, 0, 1024);
	pcb->prev = NULL;
	pcb->next = NULL;
	pcb->ReadyState = READY;
	pcb->SuspendedState = RUNNING;
	pcb->Priority = Level;
	strcpy(pcb->Process_Name,Name);
	pcb->Process_Class = Class;
	return Name;
}


PCB* FindPCB(char[] Name)	{
  // assign temp to start of ReadyQueue
  PCB* temp = ReadyQueue -> head;
  // while node exists
	while(temp != NULL)	{
    // check for PCB Name
		if(strcmp(temp -> name,Name) == 0)
			return &temp;
    // else if end of ReadyQueue, switch to BlockedQueue
    else if(temp == ReadyQueue -> tail)
      temp = BlockedQueue -> head;
    // else switch to next node if exists
    else if(temp -> next != NULL)
      temp = temp -> next;
  }
  // returns NULL if node does not exist
  return NULL;
}

void InsertPCB(PCB* pcb)	{
	if(pcb -> ReadyState == READY){
    PCB* start = ReadyQueue -> head;
    if(start == NULL){
      ReadyQueue -> head = pcb;
      ReadyQueue -> tail = pcb;
    }
    else{
      //ReadyQueue has highest priority at head
      for(start; start -> next -> Priority >= start -> Priority; start = start -> next);
      if(start -> next != NULL && start -> prev != NULL){
        pcb -> prev = start;
        pcb -> next = start -> next;
        start -> next = pcb;
        pcb -> next -> prev = pcb;
      }
      else{
        pcb -> prev = start;
        start -> next = pcb;
        ReadyQueue -> tail = pcb;
      }
    }
  }
  else{
    BlockedQueue -> tail -> next = pcb -> prev;
    BlockedQueue -> tail = pcb;
  }
}

void RemovePCB(PCB* pcb)	{
  Queue* queue;
  if(pcb -> ReadyState == READY)
    queue = ReadyQueue;
  else
    queue = BlockedQueue;
  
  if(queue -> head == pcb){
    if(pcb -> next != NULL){
      queue -> head == pcb -> next;
      pcb -> next -> prev == NULL;
      pcb -> next == NULL;
    }
    else
      queue -> head == NULL;
  }
  else{
    if(pcb -> next != NULL && pcb -> prev != NULL){
      pcb -> prev -> next = pcb -> next -> prev;
      pcb -> next = NULL;
      pcb -> prev = NULL;
    }
    else if(pcb -> next != NULL){
      queue -> tail = pcb -> prev;
      pcb -> prev = NULL;
    }
  }
}
