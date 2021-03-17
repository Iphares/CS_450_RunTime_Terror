
#define FREE 0
#define ALLOC 1

typedef struct MCB	{
  int size;
  struct MCB* prev;
  struct MCB* next;
  char Mem_block[10];
  int MEMState;
} MCB;

typedef struct List {
  MCB *head;
} List;

List* AllocMem();
List* FreeMem();

MCB* FindMCB(char Name[]);
