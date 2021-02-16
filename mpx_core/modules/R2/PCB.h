#DEFINE READY 0;
#DEFINE BLOCKED 1;
#DEFINE RUNNING 0;
#DEFINE SUSPENDED 1;

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


PCB* AllocatePCB();
void FreePCB(*PCB);
PCB* SetupPCB(char[] Name, int Class, int Priority);
PCB* FindPCB(char[] Name);
void InsertPCB(PCB*);
void RemovePCB(PCB*);
