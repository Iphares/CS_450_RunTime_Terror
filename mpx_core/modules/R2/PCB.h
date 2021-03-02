#define READY 0
#define BLOCKED 1
#define NO 0
#define YES 1
#define SYSTEM 0
#define APPLICATION 1

#define MEM1K 1024
#define MEM2K 2048
#define MEM3K 4096
#define MEM4K 8192
#define MEM5K 16384

typedef struct PCB	{
  unsigned char stack[MEM1K];
  unsigned char* stackTop;
  struct PCB* prev;
  struct PCB* next;
  char Process_Name[10];
  int Process_Class;
  int Priority;
  int ReadyState;
  int SuspendedState;
} PCB;

typedef struct Queue	{
  int count;
  PCB *head;
  PCB *tail;
} Queue;

//R3 Context switching
typede struct context {
u32int gs, fs, es, ds;
u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;
u32int eip, cs, eflags;
} context;



Queue* getReady();
Queue* getBlocked();
PCB* AllocatePCB();
void FreePCB(PCB* pcb);
PCB* SetupPCB(char Name[], int Class, int Priority);
PCB* FindPCB(char Name[]);
void InsertPCB(PCB* pcb);
void RemovePCB(PCB* pcb);
