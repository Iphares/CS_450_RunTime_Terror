#define FREE 0
#define ALLOC 1

typedef struct CMCB	{
  int size;
  struct CMCB* prev;
  struct CMCB* next;
  char Process_name[10];
  int32int address;
  int MEMState;
} CMCB;

typedef struct LMCB	{
  int size;
  int MEMState;
} LMCB;

typedef struct List {
  CMCB *head;
} List;

List* AllocMem();
List* FreeMem();

CMCB* FindMCB(char Name[]);
