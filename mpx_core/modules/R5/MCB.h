#define FREE 0
#define ALLOC 1

typedef struct CMCB	{
  int size;
  struct CMCB* prev;
  struct CMCB* next;
  char mem_name[10];
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

List* AllocMem(int size);
List* FreeMem(u32int address);

CMCB* FindMCB(char Name[]);
