
#define FREE 0
#define ALLOC 1

typedef struct MCB	{
  int size;
  struct MCB* prev;
  struct MCB* next;
  char Process_name[10];
  int Mem_block;
  int MEMState;
} MCB;

typedef struct List {
  MCB *head;
} List;

List* AllocMem();
List* FreeMem();

MCB* FindMCB(char Name[]);
