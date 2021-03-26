
#define FREE 0
#define ALLOC 1

typedef struct MCB	{
  unsigned char stack[MEM1K];
  unsigned char* stackTop;
  struct MCB* prev;
  struct MCB* next;
  char Mem_block[10];
  int MEMState;
  
} PCB;

struct Queue{
  int count;
  MCB *head;
  MCB *tail

}typedef Queue;

Queue* AllocMem();
Queue* FreeMem();

MCB* FindMCB(char Name[]);