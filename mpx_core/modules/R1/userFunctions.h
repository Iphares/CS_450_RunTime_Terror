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

	// Sets the time of the system
	void SetTime(int hours, int minutes, int seconds);
	// Gets the time of the system
	void GetTime();
	//
	int  DectoBCD (int Decimal);
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
	void Suspend(Char *Process_Name);
	// Places PCB in unsuspended state and reinserts to appropriate queue
	void Resume(Char *Process_Name);
	// Sets PCB priority and reinserts into correct place and correct queue
	void Set_Priority(Char *Process_Name, int Priority);
	// Displays information for a PCB
	void Show_PCB(Char *Process_Name);
	// Displays information for each PCB in the ready and blocked queues
	void Show_All();
	// Displays information for each PCB in the ready queue
	void Show_Ready();
	// Displays information for each PCB in the blocked queue
	void Show_Blocked();
	// Sets up PCB and puts it in the appropriate queue
	void Create_PCB(char *Process_Name, int Priority, int Class );
	// Removes the PCB for the appropriate queue and frees memory
	void Delete_PCB(Char *Process_Name);
	// Finds PCB sets it to blocked state and reinserts it into the appropriate queue
	void Block(Char *Process_Name);
	// Finds PCB sets it to unblocked state and reinserts into the appropriate queue
	void Unblock(Char *Process_Name);


#endif
