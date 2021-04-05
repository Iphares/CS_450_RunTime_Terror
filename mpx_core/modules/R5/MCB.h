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

typedef struct List {
  CMCB *head;
} List;

CMCB* AllocMem(u32int size);
CMCB* FreeMem(u32int address);
List* getList();
