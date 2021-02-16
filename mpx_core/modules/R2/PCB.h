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
        PCB *head
        PCB *tail
}
typedef struct PCB	{
	char[1KMEM] stack;
	char[10] Process_Name;
	int Process_Class;
        int Priority;
        int State;
        int Process_Stack;
        int *PCB_Pointer;
}







Queue AllocatePCB();
char FreePCB(*PCB);
PCB SetupPCB(char[] Name, int Class, int Level );
PCB FindPCB(char[] Name);
InsertPCBA(	);
RemovePCB( );
