#define FREE 0
#define ALLOC 1

typedef struct CMCB	{
  u32int size;
  struct CMCB* prev;
  struct CMCB* next;
  char Process_name[10];
  u32int address;
  int MEMState;
} CMCB;

// typedef struct LMCB	{
//   int size;
//   int MEMState;
// } LMCB;

typedef struct MemList {
  CMCB *head;
} MemList;

void* AllocMem(u32int size);
void FreeMem(u32int address);
MemList* getMemList();

void init_heap(u32int size);
