/// @file
#ifndef _USER_FUNCTIONS_H
#define _USER_FUNCTIONS_H


#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

typedef struct Alarm	{
	int hour;
	int minute;
	int second;
	char message[85];
	struct Alarm* next;
	struct Alarm* prev;
} Alarm;

typedef struct List	{
	Alarm *head;
	Alarm *tail;
} List;

	// Sets the time of the system
	void SetTime(int hours, int minutes, int seconds);
	// Gets the time of the system
	void GetTime();
	//
	int  DectoBCD (int Decimal);
	//
	void clear();
	//
	char* itoa(int num);
	// Sets the date of the system
	void SetDate(int day, int month, int millennium, int year);
	// Changes Binary Converted Decimal to Decimal
	int BCDtoDec(int BCD);
	// Gets the date of the system
	void GetDate();
	// States the version of the system
	void Version();
	// Gives help for another function
	void Help(char* request);
	// Prints
	void printf(char msg[]);
	// Evaluates user input for setTime and setDate
	int EdgeCase(char* pointer);
	// Changes an uppercase char to a lowercase char
	char toLowercase(char c);

	/*********************************************************************
				R2 Functions
	*********************************************************************/
	// Places PCB in suspended state and reinserts to appropriate queue
	void Suspend(char *ProcessName);
	// Places PCB in unsuspended state and reinserts to appropriate queue
	void Resume(char *ProcessName);
	// Sets PCB priority and reinserts into correct place and correct queue
	void Set_Priority(char *ProcessName, int Priority);
	// Displays information for a PCB
	void Show_PCB(char *ProcessName);
	// Displays information for each PCB in the ready and blocked queues
	void Show_All();
	// Displays information for each PCB in the ready queue
	void Show_Ready();
	// Displays information for each PCB in the blocked queue
	void Show_Blocked();
	// Sets up PCB and puts it in the appropriate queue
	void Create_PCB(char *ProcessName, int Priority, int Class );
	// Removes the PCB for the appropriate queue and frees memory
	void Delete_PCB(char *ProcessName);
	// Finds PCB sets it to blocked state and reinserts it into the appropriate queue
	void Block(char *ProcessName);
	// Finds PCB sets it to unblocked state and reinserts into the appropriate queue
	void Unblock(char *ProcessName);

	/*********************************************************************
				R3 Functions
	*********************************************************************/
	void loader();
	void loadr3(char* name, u32int func);
	void yield();

	/*********************************************************************
				R4 Functions
	*********************************************************************/
	void loaderinfinite();
	List* getList();
	void loaderalarm();

#endif
