

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







Queue AllocatePCB()	{
	sys_alloc_mem(1024);
}

 char FreePCB(*PCB)	{
	sys_free_mem(PCB);
	if(sys_free_mem(PCB) != -1)
		return printf("\nMemory release successful \n")
	else
		return printf("\nMemory cannot be released from the requested PCB\n")
}

PCB SetupPCB(char[] Name, int Class, int Level )	{
	if()
		PCB *Name;
        Name = (PCBsys_alloc_mem();
		Name.State = READY;
		Name.Priority = Level;
		Name.Process_Name = Name;
		Name.Process_Class = Class;
	return Name;
}


PCB FindPCB(char[] Name)	{
	while(stack.head != stack.tail && block.head != block.tail)	{
		
	
		if(strcmp(stack.head.name,Name) == 0)	{
			
			return printf("\n The pcb was found at ")
		}
		else	{
			return printf("\n ")
		}
	}
}
InsertPCBA(	)	{
	
}
RemovePCB( )	{
	
}
