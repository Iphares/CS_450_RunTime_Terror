#DEFINE 1KMEM 1024;
#DEFINE 2KMEM 2048;
#DEFINE 3KMEM 4096;
#DEFINE 4KMEM 8192;
#DEFINE 5KMEM 16384;

typedef struct Queue	{
  int count;
  PCB *head;
  PCB *tail;
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
}

PCB* AllocatePCB()	{
	return sys_alloc_mem(sizeof(PCB));
}

char FreePCB(*PCB)	{
	if(sys_free_mem(PCB) != -1)
		return printf("\nMemory release successful \n");
	else
		return printf("\nMemory cannot be released from the requested pcb->\n");
}

PCB* SetupPCB(char[] Name, int Class, int Level )	{
		PCB* pcb-> = AllocatePCB();
		pcb->stackTop = 1024 + pcb->stack;
		memset(pcb->stack, 0, 1024);
		pcb->prev = NULL;
		pcb->next = NULL;
		pcb->ReadyState = READY;
		pcb->SuspendedState = NULL;
		pcb->Priority = Level;
		strcpy(pcb->Process_Name,Name);
		pcb->Process_Class = Class;
	return Name;
}


PCB FindPCB(char[] Name)	{
	while(stack->head != stack->tail && block->head != block->tail)	{
		if(strcmp(stack->head->name,Name) == 0)
			return printf("\n The pcb-> was found at ");
		else
			return printf("\n ");
	}
}

void InsertPCB(PCB** head)	{
	PCB*
}

void RemovePCB( )	{
	//if the Ready queue is empty->
  if(Ready->count==0)	{
          printf("Queue is Empty\n");
          return;
  }
  //otherwise we can remove the specific pcb-> from the queue->
  else	{
    Ready->count--;
    Q->front++;
    if(Q->front==Q->capacity)	{
      Q->front=0;
    }
  }
}
