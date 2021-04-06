/// @file

// Description: Includes all commands the user has access to along with their supporting functions.
//
// Functions within userFunctions:
//     itoa, BCDtoDec, DectoBCD, SetTime, GetTime, SetDate, GetDate, version, toLowercase, help
//
//
// Initial Implementation -- by Isiah Phares, 2021.
// Modifications by:    Morgan Bartley 2021, Jordan Potter 2021, Greg Potts 2021.

#include <stdint.h>
#include <string.h>
#include <system.h>
#include <core/serial.h>

#include <core/io.h>
#include "../mpx_supt.h"
#include "userFunctions.h"
#include "../procsr3.h"
#include "../sys_proc_loader.h"


/********************************************************************************************************
				Bonus functions
********************************************************************************************************/



	void clear()	{
		printf("\033c");
		Help("");
	}




  /// Description: An integer is taken and seperated into individual chars and then all placed into a character array. Adapted from geeksforgeeks.org.
  ///
  /// @param num integer to be put into array
  ///

/**
    Title: itoa
    Author: Neha Mahajan
    Date: 29 May, 2017
    Availability: https://www.geeksforgeeks.org/implement-itoa/
*/

char* itoa(int num){

	int i,j,k,count;
	i = num;
	j = 0;
	count = 0;
	while(i){ // count number of digits
		count++;
		i /= 10;
	}

	char* arr1;
	char arr2[count];
	arr1 = (char*)sys_alloc_mem(count); //memory allocation

	while(num){ // seperate last digit from number and add ASCII
		arr2[++j] = num%10 + '0';
		num /= 10;
	}

	for(k = 0; k < j; k++){ // reverse array results
		arr1[k] = arr2[j-k];
	}
	arr1[k] = '\0';

	return(char*)arr1;
}

/// Description: Changes binary number to decimal numbers.
///
/// @param value Binary number to be changed to decimal
int BCDtoDec(int BCD)	{
	return (((BCD>>4)*10) + (BCD & 0xF));
}

/// Description: Changes decimal numbers to binary numbers.
///
/// @param Decimal Decimal number to be changed to binary
int  DectoBCD (int Decimal)	{
	return (((Decimal/10) << 4) | (Decimal % 10));
}

void printf(char msg[])	{
  int check =strlen(msg);
	sys_req(WRITE, COM1, msg, &check);
}






/********************************************************************************************************
				EdgeCase functions
********************************************************************************************************/

/// Description: Compares pointer char to validate if it is a number or not.
///
/// @param Compares pointer char to validate if it is a number or not.
int EdgeCase(char* pointer)    {
  int valid = 0;
  if (strcmp(pointer, "00") == 0) {
    valid = 1;
    return valid;
  }
  else if (strcmp(pointer, "0") == 0) {
    valid = 1;
    return valid;
  }
  else  {
  	int j;
    valid = 0;
    for(j = 0; j <= 99; j++)  {
      if(strcmp(pointer,itoa(j)) == 0)
        valid = 1;
    }
    if(valid == 0)  {
      return valid;
    }
  }
  return valid;
}










/********************************************************************************************************
				R1 functions
********************************************************************************************************/

/// Description: sets the time register to the new values that the user inputed, all values must be inputed as SetTime(Hours, Minutes, Seconds).
///
/// @param hours Integer to be set in the Hour position
/// @param minutes Integer to be set in the Minutes position
/// @param seconds Integer to be set in the Seconds position
void SetTime(int hours, int minutes, int seconds)	{
  outb(0x70,0x04);
  unsigned char tempHours = BCDtoDec(inb(0x71));
  outb(0x70,0x02);
  unsigned char tempMinutes = BCDtoDec(inb(0x71));
  outb(0x70,0x00);
  unsigned char tempSeconds = BCDtoDec(inb(0x71));
	cli(); //outb(device + 1, 0x00); //disable interrupts
	outb(0x70,0x04);
	outb(0x71, DectoBCD(hours));// change to bcd
	outb(0x70,0x02);
	outb(0x71, DectoBCD(minutes));
	outb(0x70,0x00);
	outb(0x71, DectoBCD(seconds));
	sti();  //outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
  outb(0x70,0x04);
  unsigned char newHours = BCDtoDec(inb(0x71));
  outb(0x70,0x02);
  unsigned char newMinutes = BCDtoDec(inb(0x71));
  outb(0x70,0x00);
  unsigned char newSeconds = BCDtoDec(inb(0x71));
  if(newHours != hours || newMinutes != minutes || newSeconds != seconds){
    printf("Your input was invalid\n");
    cli(); //outb(device + 1, 0x00); //disable interrupts
		outb(0x70,0x04);
		outb(0x71, DectoBCD(tempHours));// change to bcd
		outb(0x70,0x02);
		outb(0x71, DectoBCD(tempMinutes));
		outb(0x70,0x00);
		outb(0x71, DectoBCD(tempSeconds));
		sti();  //outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
  }
  else
    printf("Time Set\n");
}

/// Description: retrieve and return the time values for hours, minutes, and seconds form the clock register using inb(Port,address).
///
/// No parameters.
void GetTime()	{
	
	int hour;
	int minute;
	int second;
	outb(0x70,0x04);
	unsigned char hours = inb(0x71);
	outb(0x70,0x02);
	unsigned char minutes = inb(0x71);
	outb(0x70,0x00);
	unsigned char seconds = inb(0x71);
	char msg1[2] = ":";
	char msg2[10] = "Time: ";
	printf(msg2);
	hour = BCDtoDec(hours);
	printf(itoa(hour));
	//sys_req(WRITE, COM1, itoa(hour), &check);
	printf(msg1);
	minute = BCDtoDec(minutes);
	printf(itoa(minute));
	//sys_req(WRITE, COM1, itoa(minute), &check);
	printf(msg1);
	second = BCDtoDec(seconds);
	printf(itoa(second));
	//sys_req(WRITE, COM1, itoa(second), &check);
  printf("\n");
}

/// Description: Sets the date register to the new values that the user inputed, all values must be inputed as SetDime(day, month, millenial, year).
///
/// @param day Integer to be set in the Day position
/// @param month Integer to be set in the Month position
/// @param millenial Integer to be set in the Millenial position
/// @param year Integer to be set in the Year position
void SetDate(int day, int month, int millennium, int year)	{
  outb(0x70,0x07);
  int tempDay = BCDtoDec(inb(0x71));
  outb(0x70,0x08);
  int tempMonth = BCDtoDec(inb(0x71));
  outb(0x70,0x32);
  int tempMillennium = BCDtoDec(inb(0x71));
  outb(0x70,0x09);
  int tempYear = BCDtoDec(inb(0x71));
  cli();
	outb(0x70,0x07);
	outb(0x71,DectoBCD (day));
	outb(0x70,0x08);
	outb(0x71,DectoBCD (month));
	outb(0x70,0x32);
	outb(0x71,DectoBCD (millennium));
	outb(0x70,0x09);
	outb(0x71,DectoBCD (year));
	sti();
  outb(0x70,0x07);
  unsigned char newDay = BCDtoDec(inb(0x71));
  outb(0x70,0x08);
  unsigned char newMonth = BCDtoDec(inb(0x71));
  outb(0x70,0x32);
  unsigned char newMillennium = BCDtoDec(inb(0x71));
  outb(0x70,0x09);
  unsigned char newYear = BCDtoDec(inb(0x71));
  if(newDay != day || newMonth != month || newMillennium != millennium || newYear != year){
    printf("Your input was invalid\n");
    cli();
		outb(0x70,0x07);
		outb(0x71,DectoBCD (tempDay));
		outb(0x70,0x08);
		outb(0x71,DectoBCD (tempMonth));
		outb(0x70,0x32);
		outb(0x71,DectoBCD (tempMillennium));
		outb(0x70,0x09);
		outb(0x71,DectoBCD (tempYear));
		sti();
  }
  else
    printf("Date Set\n");
}

/// Description: Returns the full date back to the user in decimal form.
///
/// No parameters.
void GetDate()	{
  int check = 2;
  outb(0x70,0x07);
	unsigned char day = BCDtoDec(inb(0x71));
	outb(0x70,0x08);
	unsigned char month = BCDtoDec(inb(0x71));
	outb(0x70,0x32);
	unsigned char millennium = BCDtoDec(inb(0x71));
	char msg[2] = "-";
	char msg3[10] = "Date: ";
	printf(msg3);
	sys_req(WRITE, COM1, itoa(day), &check);
	printf(msg);
	sys_req(WRITE, COM1, itoa(month), &check);
	printf(msg);
	sys_req(WRITE, COM1, itoa(millennium), &check);
  outb(0x70,0x09);
  if(BCDtoDec(inb(0x71)) == 0){
    sys_req(WRITE, COM1, "00", &check);
  }
  else {
		unsigned char year = BCDtoDec(inb(0x71));
		sys_req(WRITE, COM1, itoa(year), &check);
  }
  	printf("\n");
}

/// Description: Simply returns a char containing "Version: R(module).(the iteration that module is currently on).
///
/// No parameters.
void Version()	{
	printf("Version: R4.6 \n");
}

/// Description: If a letter is uppercase, it changes it to lowercase. (char)
///
/// @param c Character that is to be changed to its lowercase equivalent
char toLowercase(char c)	{
	if((c >= 65) && (c <= 90))	{
		c = c + 32;
	}
	return c;
}


/********************************************************************************************************
				Help function
********************************************************************************************************/

/// Brief Description: Gives helpful information for one of the functions
///
/// Description: Can except a string as a pointer, if the pointer is null then the function will print a complete list of avaliable commands to the console. If the pointer is a avaliable commands then instructions on how to use the command will be printed. If the command does not exist then a message explaining that it is not a valid command will be displayed.
///
/// @param request Character pointer that matches the name of the function that you need help with.
void Help(char* request)	{
	if (request[0] == '\0')	{
		//removed for R3/R4 from active command list
		//\n createPCB \n block \n unblock
		printf("\n to chain commands and parameters, please use \"-\" between keywords \n");
		printf("\n getDate      setDate \n getTime      setTime \n version      suspend \n resume       setPriority \n showPCB      showAll \n showReady    showBlocked  \n deletePCB    shutdown \n alarm        clear \n loadr3       infinte \n heap         alloc \n free         empty \n showFree     showAlloc \n\n");
	}
	else if (strcmp(request, "GetDate") == 0)	{
		printf("\n getDate returns the current date that is loaded onto the operating system.\n");
	}
	else if (strcmp(request, "SetDate") == 0)	{
		printf("\n setDate allows the user to reset the correct date into the system, as follows setDate-"BLU"day"RESET"-"BLU"month"RESET"-"BLU"year"RESET".\n Time must be inputed as a two digit number, Example 02 or 00");
	}
	else if (strcmp(request, "GetTime") == 0)	{
		printf("\n getTime returns the current time as hours, minutes, seconds that is loaded onto the operating system.\n");
	}
	else if (strcmp(request, "SetTime") == 0)	{
		printf("\n setTime allows the user to reset the correct time into the system, as follows setTime-"BLU"hour"RESET"-"BLU"minute"RESET"-"BLU"second"RESET".\n Time must be inputed as a two digit number, Example 02 or 00");
	}
	else if (strcmp(request, "Version") == 0)	{
		printf("\n version returns the current operating software version that the system is running.\n");
	}
	else if (strcmp(request, "infinte") == 0)	{
		printf("\n infinite Loads the infinite process into the ready queue.\n");
	}
	else if (strcmp(request, "loadr3") == 0)	{
		printf("\n loadr3 Loads in all five of the R3 test processes in a suspended state into the queue.\n");
	}
	else if (strcmp(request, "alarm") == 0)		{
		printf("\n alarm creates a user specified alarm with a user set message and time alarm-MSG-hour-minute-second.\n");
	}
	else if (strcmp(request, "clear") == 0)		{
		printf("\n clear erases the console of all typed commands and refreshes it with just the command list.\n");
	}

  else if(strcmp(request, "shutdown") == 0)	{
    printf("\n shutdown shuts down the system.\n");
  }


/********************************************************************************************************
			R2 Commands
********************************************************************************************************/
  else if(strcmp(request,"suspend") == 0) {
		printf("\n Suspend takes in the name of a PCB (suspend-NAME) then places it into the suspended state and reinserts it into the correct queue.\n");
  }
  else if(strcmp(request,"resume") == 0) {
		printf("\n Resume takes in the name of a PCB (resume-NAME) then removes it from the suspended state and adds it to the correct queue.\n");
  }
  else if(strcmp(request,"setPriority") == 0) {
		printf("\n SetPriority takes in the name of a PCB and the priority (setPrioriry-NAME-PRIORITY) it needs to be set to then reinstates the specified PCB into a new location by priority.\n");
  }
  else if(strcmp(request,"showPCB") == 0) {
		printf("\n ShowPCB takes in the name of a PCB and returns all the associated attributes to the user.\n");
  }
  else if(strcmp(request,"showAll") == 0) {
		printf("\n ShowAll takes no parameters but returns all PCB's that are currently in any of the queues.\n");
  }
  else if(strcmp(request,"showReady") == 0) {
		printf("\n ShowReady takes in no parameters but returns all PCB's and there attributes that currently are in the ready state.\n");
  }
  else if(strcmp(request,"showBlocked") == 0) {
		printf("\n ShowBlocked takes in no parameters but returns all PCB's and there attributes that currently are in the blocked state.\n");
  }

/********************************* R2 Temp Commands *********************************************************/
  else if(strcmp(request,"deletePCB") == 0) {
		printf("\n DeletePCB takes in the process_name (deletePCB-NAME) then deletes it from the queue and free's all the memory that was previously allocated to the specified PCB.\n");
  }
  //removed for R3/R4 from active command list
  /*
  else if(strcmp(request,"createPCB") == 0) {
		printf("\n CreatePCB takes in the process_name, process_class, and process_priority.(createPCB-NAME-PRIORITY-CLASS) Then assigns this new process into the correct queue.\n");
  }
  else if(strcmp(request,"block") == 0) {
		printf("\n Block takes in the process_name (block-NAME) then sets it's state to blocked and reinserts it back into the correct queue.\n");
  }
  else if(strcmp(request,"unblock") == 0) {
		printf("\n Unblock takes in the process_name (unblock-NAME) then sets it's state to ready and reinserts it back into the correct queue.\n");
  }
  */
	
	
/********************************* R5 Temp Commands *********************************************************/
  else if(strcmp(request,"heap") == 0) {
		printf("\n heap initializes the memory heap for the entire system.\n");
  }
  else if(strcmp(request,"alloc") == 0) {
		printf("\n alloc allocates the specified amount of memory to the specific process (alloc-process_name-size).\n");
  }
  else if(strcmp(request,"free") == 0) {
		printf("\n free frees the specified memory at the address given (free-address).\n");
  }
  else if(strcmp(request,"empty") == 0) {
		printf("\n isempty returns true or false depending on if the heap has allocated memory.\n");
  }
/********************************* R5 Commands *********************************************************/
  else if(strcmp(request,"showFree") == 0) {
		printf("\n showfree shows all the free blocks avaliable within the heap list.\n");
  }
  else if(strcmp(request,"showAlloc") == 0) {
		printf("\n showAlloc shows all the allocated blocks within the heap list.\n");
  }	
	
	
  else	{
		printf("\x1b[31m""\nThe requested command does not exist please refer to the Help function for a full list of commands.\n""\x1b[0m");
  }	
}








/*********************************************************************
			R2 Functions
*********************************************************************/
/// Brief Description: Places a PCD in the suspended state and reinserts it into the appropriate queue.
///
/// Description: Can except a string as a pointer that is the Process Name.  Places a PCB in the suspended state and reinserts it into the appropriate queue.  An error check for valid Process Name.
///
/// @param Process_Name Character pointer that matches the name of process.
void Suspend(char *ProcessName)	{
	PCB* pcb = FindPCB(ProcessName);
	if (pcb == NULL)	{
	  printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
	}
	else {
		if(pcb->SuspendedState == YES)	{
			printf("\x1b[32m""\nThis Process is already SUSPENDED \n""\x1b[0m");
		}
		else if(pcb -> Process_Class == APPLICATION)	{
			pcb->SuspendedState = YES;
		}
		else
			printf("\x1b[31m""\nERROR: Cannot Alter System Process \n""\x1b[0m");
	}
}





/// Brief Description: Places a PCD in the not suspended state and reinserts it into the appropriate queue.
///
/// Description: Can except a string as a pointer that is the Process Name.  Places a PCB in the not suspended state and reinserts it into the appropriate queue.  An error check for valid Process Name.
///
/// @param Process_Name Character pointer that matches the name of process.
void Resume(char *ProcessName)	{
	PCB* pcb = FindPCB(ProcessName);
	if (pcb == NULL)	{
	  printf(RED"\nERROR: Not a valid process name \n"RESET);
	}
	else {
		if(pcb->SuspendedState == NO)	{
			printf(GRN"\nThis Process is already in the NONSUSPENDED state \n"RESET);
		}
		else if(pcb -> Process_Class == APPLICATION)	{
			pcb->SuspendedState = NO;
		}
		else
			printf("\x1b[31m""\nERROR: Cannot Alter System Process \n""\x1b[0m");
	}
}





/// Brief Description: Sets PCB priority and reinserts the process into the correct place in the correct queue.
///
/// Description: Can except a string as a pointer that is the Process Name. Can accept and integer than is the Priority. Sets a PCB's priority and reinserts the process into the correct place in the correct queue.  An error check for valid Process Name and an error check for a valid priority 1 - 9.
///
/// @param Process_Name Character pointer that matches the name of process.
/// @param Priority integer that matches the priority number.
void Set_Priority(char *ProcessName, int Priority)	{
	PCB* pcb = FindPCB(ProcessName);
	if (pcb == NULL)    {
	 	printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
	}
	else if(Priority >= 10){
		printf("\x1b[31m""\nERROR: Not a valid Priority \n""\x1b[0m");
	}
	else if(pcb -> Process_Class == APPLICATION) {
		RemovePCB(pcb);
		pcb->Priority = Priority;
		InsertPCB(pcb);
	}
	else
		printf("\x1b[31m""\nERROR: Cannot Alter System Process \n""\x1b[0m");
}




/// Brief Description: Displays the process name, class, state, suspended status, and priority of a PCB.
///
/// Description: Can except a string as a pointer that is the Process Name.  The process name, claas, state, suspend status, and priority of a PCB are displayed.  An error check for a valid name occurs.
///
/// @param Process_Name Character pointer that matches the name of process
void Show_PCB(char *ProcessName)	{
	if (FindPCB(ProcessName) == NULL)	{
		printf("\x1b[31m""\nERROR: PCB does not exist \n""\x1b[0m");
	}
	else	{
		int check = 5;
		char name[10];
		char cname[] = "Name: ";
		char cclass[] = "Class: ";
		char cstate[] = "State: ";
		char cstatus[] = "Status: ";
		char cprior[] = "Priority: ";
		char line[] = "\n";
		PCB* pcb = FindPCB(ProcessName);
		strcpy(name,pcb->Process_Name);
		int class = pcb->Process_Class;
		int state = pcb->ReadyState;
		int status = pcb->SuspendedState;
		int prior = pcb->Priority;

		if(name == NULL){
			printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
		}
		else	{
			printf(cname);
			printf(ProcessName);
			printf(line);
			printf(cclass);
			if(pcb->Process_Class == 0)  {
				printf("0");
			}
			else  {
				sys_req(WRITE, COM1, itoa(class), &check);
			}
			printf(line);
			printf(cstate);
			if(pcb->ReadyState == 0)  {
				printf("0");
			}
			else  {
				sys_req(WRITE, COM1, itoa(state), &check);
			}
			printf(line);
			printf(cstatus);
			if(pcb->SuspendedState == 0)  {
				printf("0");
			}
			else  {
				sys_req(WRITE, COM1, itoa(status), &check);
			}
			printf(line);
			printf(cprior);
			if(pcb->Priority == 0)  {
				printf("0");
				printf("\n\n");
			}
			else  {
				sys_req(WRITE, COM1, itoa(prior), &check);
				printf("\n\n");
			}
		}
	}
}





/// Brief Description: Displays the process name, class, state, suspended status, and priority of all PCB in the ready and blocked queues.
///
/// Description: The process name, claas, state, suspend status, and priority of each of he PCB's in the ready and blocked queues.
void Show_All()	{
	Show_Ready();
	Show_Blocked();
}





/// Brief Description: Displays the process name, class, state, suspended status, and priority of all PCB in the ready queue.
///
/// Description: The process name, claas, state, suspend status, and priority of each of he PCB's in the ready queue.
void Show_Ready()	{
	if(getReady()->head == NULL)	{
		 printf("\x1b[32m""\n The Ready Queue is empty \n""\x1b[0m");
	}
	else	{
		int class, check, state, prior, status;
	  char name[10];
	  char ready[] = "\x1B[34m""\nReady Queue:\n""\x1B[0m";
	  char cname[] = "Name: ";
	  char cclass[] = "Class: ";
	  char cstate[] = "State: ";
	  char cstatus[] = "Status: ";
	  char cprior[] = "Priority: ";
	  char line[] = "\n";
	  check = 5;

	  sys_req(WRITE, COM1, ready, &check );

	  PCB* pcb = getReady()->head;

		if(pcb->next == NULL)	{
			class = pcb->Process_Class;
			strcpy(name,pcb->Process_Name);
			state = pcb->ReadyState;
			status = pcb->SuspendedState;
			prior = pcb->Priority;

			printf(cname);
			printf(name);
			printf(line);

			printf(cclass);
			if(pcb->Process_Class == 0)  {
			  printf("0");
			}
			else  {
			  sys_req(WRITE, COM1, itoa(class), &check);
			}
			printf(line);

			printf(cstate);
			if(pcb->ReadyState == 0)  {
			  printf("0");
			}
			else  {
			  sys_req(WRITE, COM1, itoa(state), &check);
			}
			printf(line);

			printf(cstatus);
			if(pcb->SuspendedState == 0)  {
			  printf("0");
			}
			else  {
			  sys_req(WRITE, COM1, itoa(status), &check);
			}
			printf(line);

			printf(cprior);
			if(pcb->Priority == 0)  {
			  printf("0");
			  printf("\n\n");
			}
			else  {
			  sys_req(WRITE, COM1, itoa(prior), &check);
			  printf("\n\n");
			}
	  }
	  else	{
	  	while(pcb != NULL)	{
				class = pcb->Process_Class;
				strcpy(name,pcb->Process_Name);
				state = pcb->ReadyState;
				status = pcb->SuspendedState;
				prior = pcb->Priority;

				printf(cname);
				printf(name);
				printf(line);

				printf(cclass);
				if(pcb->Process_Class == 0)  {
				  printf("0");
				}
				else  {
				  sys_req(WRITE, COM1, itoa(class), &check);
				}
				printf(line);

				printf(cstate);
				if(pcb->ReadyState == 0)  {
				  printf("0");
				}
				else  {
				  sys_req(WRITE, COM1, itoa(state), &check);
				}
				printf(line);

				printf(cstatus);
				if(pcb->SuspendedState == 0)  {
				  printf("0");
				}
				else  {
				  sys_req(WRITE, COM1, itoa(status), &check);
				}
				printf(line);

				printf(cprior);
				if(pcb->Priority == 0)  {
				  printf("0");
				  printf("\n\n");
				}
				else  {
				  sys_req(WRITE, COM1, itoa(prior), &check);
				  printf("\n\n");
				}
				pcb = pcb->next;
			}
		}
	}
}





/// Brief Description: Displays the process name, class, state, suspended status, and priority of all PCB in the blocked queue.
///
/// Description: The process name, claas, state, suspend status, and priority of each of he PCB's in the blocked queue.
void Show_Blocked()	{
	if(getBlocked()->head == NULL)	{
		 printf("\x1b[32m""\n The Blocked Queue is empty \n""\x1b[0m");
	}
	else	{
		  int class, check, state, prior, status;
		  char name[20];
		  char block[] = "\x1B[34m""Blocked Queue: \n""\x1b[0m";
		  char cname[] = "Name: ";
		  char cclass[] = "Class: ";
		  char cstate[] = "State: ";
		  char cstatus[] = "Status: ";
		  char cprior[] = "Priority: ";
		  char line[] = "\n";
		  check = 15;

		  sys_req(WRITE, COM1, block, &check );

		  PCB* pcb = getBlocked()->head;

		  if(pcb->next == NULL)	{
		  	class = pcb->Process_Class;
		    	strcpy(name,pcb->Process_Name);
		    	state = pcb->ReadyState;
		    	status = pcb->SuspendedState;
		    	prior = pcb->Priority;

		    	printf(cname);
		    	printf(name);
		    	printf(line);

			    printf(cclass);
			    if(pcb->Process_Class == 0)  {
			      printf("0");
			    }
			    else  {
			      sys_req(WRITE, COM1, itoa(class), &check);
			    }
			    printf(line);

			    printf(cstate);
			    if(pcb->ReadyState == 0)  {
			      printf("0");
			    }
			    else  {
			      sys_req(WRITE, COM1, itoa(state), &check);
			    }
			    printf(line);

			    printf(cstatus);
			    if(pcb->SuspendedState == 0)  {
			      printf("0");
			    }
			    else  {
			      sys_req(WRITE, COM1, itoa(status), &check);
			    }
			    printf(line);

			    printf(cprior);
			    if(pcb->Priority == 0)  {
			      printf("0");
			      printf("\n\n");
			    }
			    else  {
			      sys_req(WRITE, COM1, itoa(prior), &check);
			      printf("\n\n");
			    }
		  }
		  else	{
		  	while(pcb != NULL)	{
		  		class = pcb->Process_Class;
			    	strcpy(name,pcb->Process_Name);
			    	state = pcb->ReadyState;
			    	status = pcb->SuspendedState;
			    	prior = pcb->Priority;

			    	printf(cname);
			    	printf(name);
			    	printf(line);

				    printf(cclass);
				    if(pcb->Process_Class == 0)  {
				      printf("0");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(class), &check);
				    }
				    printf(line);

				    printf(cstate);
				    if(pcb->ReadyState == 0)  {
				      printf("0");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(state), &check);
				    }
				    printf(line);

				    printf(cstatus);
				    if(pcb->SuspendedState == 0)  {
				      printf("0");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(status), &check);
				    }
				    printf(line);

				    printf(cprior);
				    if(pcb->Priority == 0)  {
				      printf("0");
				      printf("\n\n");
				    }
				    else  {
				      sys_req(WRITE, COM1, itoa(prior), &check);
				      printf("\n\n");
				    }
		  		pcb = pcb->next;
		 	}
		 }
	}
}





/// Brief Description: Calls SetupPCB() and inserts PCB into appropriate queue.
///
/// Description: Can except a string as a pointer that is the Process Name. Can accept two integers, Priority and Class. SetupPCB() will be called and the PCB will be inserted into the appropriate queue.  An error check for unique and valid Process Name, an error check for valid  process class, and an error check for process priority.
///
/// @param Process_Name Character pointer that matches the name of process.
/// @param Priority integer that matches the priority number.
/// @param Class integer that matches the class number.
void Create_PCB(char *ProcessName, int Priority, int Class )	{
  if (FindPCB(ProcessName) == NULL)	{
    if(Priority >= 0 && Priority < 10){
      if(Class == 0 || Class == 1){
        PCB* pcb = SetupPCB(ProcessName, Class, Priority);
        InsertPCB(pcb);
      } else{
        printf("\x1b[31m""\nERROR: Not a valid Class \n""\x1b[0m");
      }
    } else{
      printf("\x1b[31m""\nERROR: Not a valid Priority \n""\x1b[0m");
    }
  } else{
    printf("\x1b[31m""\nERROR: This Process Name already exists \n""\x1b[0m");
  }
}





/// Brief Description: Removes PCB from appropriate queue and frees all associated memory.
///
/// Description: Can except a string as a pointer that is the Process Name. Removes PCB from the appropriate queue and then frees all associated memory.  An error check to make sure process name is valid.
///
/// @param Process_Name Character pointer that matches the name of process.
void Delete_PCB(char *ProcessName)	{
  PCB* pcb = FindPCB(ProcessName);
  if (pcb == NULL)	{
    printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
  }
  else if(strcmp(pcb->Process_Name,"InfProc") == 0)	{
		if(pcb->SuspendedState == YES)	{
			RemovePCB(pcb);
		 	FreePCB(pcb);
		}
		else
			printf("\x1b[31m""\nERROR:This process cannot be deleted unless it is in the suspended state\n""\x1b[0m");
  }
  else if(pcb -> Process_Class == SYSTEM)	{
	  printf("\x1b[31m""\nERROR: System Processes cannot be deleted from the system. \n""\x1b[0m");
  }
	else {
		RemovePCB(pcb);
		FreePCB(pcb);
	}
}





/// Brief Description: Places a PCD in the blocked state and reinserts it into the correct queue.
///
/// Description: Can except a string as a pointer that is the Process Name.  The specified PCB will be places in a blocked state and reinserted into the appropriate queue.  An error check for a valid name occurs.
///
/// @param Process_Name Character pointer that matches the name of process.
void Block(char *ProcessName)	{
  PCB* pcb = FindPCB(ProcessName);
  if (pcb == NULL)	{
    printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
  }
  else {
    if(pcb->ReadyState == BLOCKED)	{
    	printf("\x1b[32m""\nThis Process is already BLOCKED \n""\x1b[0m");
    }
    else	{
      RemovePCB(pcb);
      pcb->ReadyState = BLOCKED;
      InsertPCB(pcb);
    }
  }
}





/// Brief Description: Places a PCD in the unblocked state and reinserts it into the correct queue.
///
/// Description: Can except a string as a pointer that is the Process Name.  The specified PCB will be places in an unblocked state and reinserted into the appropriate queue.  An error check for a valid name occurs.
///
/// @param Process_Name Character pointer that matches the name of process.
void Unblock(char *ProcessName)	{
  PCB* pcb = FindPCB(ProcessName);
  if (pcb == NULL)	{
    printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
  }
  else {
    if(pcb->ReadyState == READY)	{
    	printf("\x1b[32m""\nThis Process is already in the READY state \n""\x1b[0m");
    }
    else	{
      RemovePCB(pcb);
      pcb->ReadyState = READY;
      InsertPCB(pcb);
    }
  }
}




/********************************************************************************************************
				R3 Commands
********************************************************************************************************/

void loader()	{
	loadr3("test1",(u32int)proc1);
	loadr3("test2",(u32int)proc2);
	loadr3("test3",(u32int)proc3);
	loadr3("test4",(u32int)proc4);
	loadr3("test5",(u32int)proc5);
}

void loadr3(char* name, u32int func)	{
	PCB* new_pcb = SetupPCB(name, APPLICATION, 1);
	new_pcb->SuspendedState = YES;
	//pcb * new_pcb = create_pcb ( name , 1 , 1 , 1 , stack_size );
	context* cp = (context*)(new_pcb->stackTop);
	memset(cp, 0, sizeof(context));
	cp->fs = 0x10;
	cp->gs = 0x10;
	cp->ds = 0x10;
	cp->es = 0x10;
	cp->cs = 0x8;
	cp->ebp = (u32int)(new_pcb->stack);
	cp->esp = (u32int)(new_pcb->stackTop);
	cp->eip = (u32int) func;// The function correlating to the process , ie. Proc1
	cp->eflags = 0x202 ;
	InsertPCB(new_pcb);
}

void yield()	{
	asm volatile ("int $60");
}

/********************************************************************************************************
				R4 Commands
********************************************************************************************************/
void loaderinfinite()	{
	loadr3("InfProc",(u32int)InfiniteProc);
	Resume("InfProc");
}

List AlarmList ={
  .head = NULL,
  .tail = NULL
};

List* getList() {
  return &AlarmList;
}

void loaderalarm(char text[], int hours, int minutes, int seconds) {
	//creates pcb if it does not exist
	if(FindPCB("AlarmProc") == NULL){
		loadr3("AlarmProc",(u32int)AlarmProc);
		Resume("AlarmProc");
	}
	//load message and time into list
	Alarm* alarm = sys_alloc_mem(sizeof(Alarm));
	alarm -> hour = hours;
	alarm -> minute = minutes;
	alarm -> second = seconds;
	strcpy(alarm -> message, text);

	//Add alarm to list
	Alarm* start = AlarmList.head;
	if(start == NULL) {
		AlarmList.head = alarm;
		AlarmList.tail = alarm;
	}
	else  {
		while(start -> next != NULL)
			start = start -> next;
		start->next = alarm;
		alarm->prev = start;
		AlarmList.tail = start;
	}
}
