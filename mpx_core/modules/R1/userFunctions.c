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
#include "../R2/PCB.h"
#include "userFunctions.h"

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

  char* itoa(int num)
	{
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

  /// Description: Compares pointer char to validate if it is a number or not.
  ///
  /// @param Compares pointer char to validate if it is a number or not.
  int EdgeCase(char* pointer)    {
    int valid = 0;
    if (strcmp(pointer, "00") == 0){
      valid = 1;
      return valid;
    }
    int i, j;
    for (i = 0; i < strlen(pointer); i++){
        valid = 0;
        for(j = 0; j <= 99; j++){
            if(strcmp(pointer,itoa(j)) == 0)
                valid = 1;
        }
        if(valid == 0){
          return valid;
        }
    }
    return valid;
  }

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
  	int check = 2;
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
		sys_req(WRITE, COM1, itoa(hour), &check);
		printf(msg1);
		minute = BCDtoDec(minutes);
		sys_req(WRITE, COM1, itoa(minute), &check);
		printf(msg1);
		second = BCDtoDec(seconds);
		sys_req(WRITE, COM1, itoa(second), &check);
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
		printf("Version: R2.0 \n");
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

  /// Brief Description: Gives helpful information for one of the functions
  ///
  /// Description: Can except a string as a pointer, if the pointer is null then the function will print a complete list of avaliable commands to the console. If the pointer is a avaliable commands then instructions on how to use the command will be printed. If the command does not exist then a message explaining that it is not a valid command will be displayed.
  ///
  /// @param request Character pointer that matches the name of the function that you need help with.
  void Help(char* request)	{
		if (request[0] == '\0')	{
      			printf("\n to chain commands and parameters, please use \"-\" between keywords \n");
			printf("\n getDate \n setDate \n getTime \n setTime \n version \n suspend \n resume \n setPriority \n showPCB \n showAll \n showReady \n showBlocked \n createPCB \n deletePCB \n block \n unblock \n shutdown \n\n");
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
    else if(strcmp(request, "shutdown") == 0)	{
      printf("\n shutdown shuts down the system.\n");
    }

/************************R2 Commands****************************************************/
    else if(strcmp(request,"suspend") == 0) {
	printf("\n Suspend takes in the name of a PCB then places it into the suspended state and reinserts it into the correct queue.\n");
    }
    else if(strcmp(request,"resume") == 0) {
	printf("\n Resume takes in the name of a PCB then removes it from the suspended state and adds it to the correct queue.\n");
    }
    else if(strcmp(request,"setPriority") == 0) {
	printf("\n SetPriority takes in the name of a PCB and the priority it needs to be set to then reinstates the specified PCB into a new location by priority.\n");
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
    else if(strcmp(request,"createPCB") == 0) {
	printf("\n  CreatePCB takes in the process_name, process_class, and process_priority. Then assigns this new process into the correct queue.\n");
    }
    else if(strcmp(request,"deletePCB") == 0) {
	printf("\n DeletePCB takes in the process_name then deletes it from the queue and free's all the memory that was previously allocated to the specified PCB.\n");
    }
    else if(strcmp(request,"block") == 0) {
	printf("\n Block takes in the process_name then sets it's state to blocked and reinserts it back into the correct queue.\n");
    }
    else if(strcmp(request,"unblock") == 0) {
	printf("\n Unblock takes in the process_name then sets it's state to ready and reinserts it back into the correct queue.\n");
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
void Suspend(char *Process_Name)	{
  // Name Error check
  // Error check (Valid Name)
  PCB* pcb = FindPCB(Process_Name);
  if (pcb == NULL)	{
    printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
  }
  else {
  	if(pcb->SuspendedState == YES)	{
  		printf("\x1b[32m""\nThis Process is already SUSPENDED \n""\x1b[0m");
  	}
  	else	{
  		pcb->SuspendedState = YES;
  	}
  }

}

/// Brief Description: Places a PCD in the not suspended state and reinserts it into the appropriate queue.
///
/// Description: Can except a string as a pointer that is the Process Name.  Places a PCB in the not suspended state and reinserts it into the appropriate queue.  An error check for valid Process Name.
///
/// @param Process_Name Character pointer that matches the name of process.
void Resume(char *Process_Name)	{
  // Name Error check
  // Error check (Valid Name)
  PCB* pcb = FindPCB(Process_Name);
  if (pcb == NULL)	{
    printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
  }
  else {
  	if(pcb->SuspendedState == NO)	{
  		printf("\x1b[32m""\nThis Process is already in the RUNNING state \n""\x1b[0m");
  	}
  	else	{
  		pcb->SuspendedState = NO;
  	}
  }
}

/// Brief Description: Sets PCB priority and reinserts the process into the correct place in the correct queue.
///
/// Description: Can except a string as a pointer that is the Process Name. Can accept and integer than is the Priority. Sets a PCB's priority and reinserts the process into the correct place in the correct queue.  An error check for valid Process Name and an error check for a valid priority 1 - 9.
///
/// @param Process_Name Character pointer that matches the name of process.
/// @param Priority integer that matches the priority number.
void Set_Priority(char *Process_Name, int Priority)	{
  PCB* pcb = FindPCB(Process_Name);
  if (pcb == NULL)    {
    printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
  } else if(Priority < 10){
        printf("\x1b[31m""\nERROR: Not a valid Priority \n""\x1b[0m");
  } else {
    RemovePCB(pcb);
    pcb->Priority = Priority;
    InsertPCB(pcb);
  }
}

/// Brief Description: Displays the process name, class, state, suspended status, and priority of a PCB.
///
/// Description: Can except a string as a pointer that is the Process Name.  The process name, claas, state, suspend status, and priority of a PCB are displayed.  An error check for a valid name occurs.
///
/// @param Process_Name Character pointer that matches the name of process
void Show_PCB(char *Process_Name)	{
  int class, check, state, prior, status;
  check = 5;
  char name[];
  char cname[] = "Name: ";
  char cclass[] = "Class: ";
  char cstate[] = "State: ";
  char cstatus[] = "Status: ";
  char cprior[] = "Priority: ";
  char line[] = "\n";
  PCB* pcb = FindPCB(Process_Name);
  class = pcb->Process_Class;
  name = pcb->Process_Name;
  state = pcb->ReadyState;
  status = pcb->SuspendedState;
  prior = pcb->Priority;
  if(name == NULL){
    printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
  } else{
    printf(cclass);
    sys_req(WRITE, COM1, itoa(class), &check);
    printf(line);

    printf(cstate);
    sys_req(WRITE, COM1, itoa(state), &check);
    printf(line);

    printf(cstatus);
    sys_req(WRITE, COM1, itoa(status), &check);
    printf(line);

    printf(cprior);
    sys_req(WRITE, COM1, itoa(prior), &check);
  }
}


/// Brief Description: Displays the process name, class, state, suspended status, and priority of all PCB in the ready and blocked queues.
///
/// Description: The process name, claas, state, suspend status, and priority of each of he PCB's in the ready and blocked queues.
void Show_All()	{
  int class, check, state, prior, status;
  char name[];
  char ready[] = "Ready Queue:\n";
  char block[] = "Blocked Queue: \n";
  char cname[] = "Name: ";
  char cclass[] = "Class: ";
  char cstate[] = "State: ";
  char cstatus[] = "Status: ";
  char cprior[] = "Priority: ";
  char line[] = "\n";
  char dline[] = "\n\n";
  check = 15;

  sys_req(WRITE, COM1, ready, &check );
  for(i = 0; i <= sizeof(ReadyQueue); i++){
    char* Process_Name = ReadyQueue[i];
    PCB* pcb = FindPCB(Process_Name);

    class = pcb->Process_Class;
    name = pcb->Process_Name;
    state = pcb->ReadyState;
    status = pcb->SuspendedState;
    prior = pcb->Priority;

    printf(cname);
    printf(name);
    printf(line);

    printf(cclass);
    sys_req(WRITE, COM1, itoa(class), &check);
    printf(line);

    printf(cstate);
    sys_req(WRITE, COM1, itoa(state), &check);
    printf(line);

    printf(cstatus);
    sys_req(WRITE, COM1, itoa(status), &check);
    printf(line);

    printf(cprior);
    sys_req(WRITE, COM1, itoa(prior), &check);
    printf(dline);
  }

  sys_req(WRITE, COM1, block, &check );
  for(j = 0; j <= sizeof(BlockedQueue); j++){
    char* Process_Name = BlockedQueue[j];
    PCB* pcb = FindPCB(Process_Name);

    class = pcb->Process_Class;
    name = pcb->Process_Name;
    state = pcb->ReadyState;
    status = pcb->SuspendedState;
    prior = pcb->Priority;

    printf(cname);
    printf(name);
    printf(line);

    printf(cclass);
    sys_req(WRITE, COM1, itoa(class), &check);
    printf(line);

    printf(cstate);
    sys_req(WRITE, COM1, itoa(state), &check);
    printf(line);

    printf(cstatus);
    sys_req(WRITE, COM1, itoa(status), &check);
    printf(line);

    printf(cprior);
    sys_req(WRITE, COM1, itoa(prior), &check);
  }
}

/// Brief Description: Displays the process name, class, state, suspended status, and priority of all PCB in the ready queue.
///
/// Description: The process name, claas, state, suspend status, and priority of each of he PCB's in the ready queue.
void Show_Ready()	{
  int class, check, state, prior, status;
  char name[];
  char ready[] = "Ready Queue:\n";
  char cname[] = "Name: ";
  char cclass[] = "Class: ";
  char cstate[] = "State: ";
  char cstatus[] = "Status: ";
  char cprior[] = "Priority: ";
  char line[] = "\n";
  check = 15;

  sys_req(WRITE, COM1, ready, &check );
  for(i = 0; i <= sizeof(ReadyQueue); i++){
    char* Process_Name = ReadyQueue[i];
    PCB* pcb = FindPCB(Process_Name);

    class = pcb->Process_Class;
    name = pcb->Process_Name;
    state = pcb->ReadyState;
    status = pcb->SuspendedState;
    prior = pcb->Priority;

    printf(cname);
    printf(name);
    printf(line);

    printf(cclass);
    sys_req(WRITE, COM1, itoa(class), &check);
    printf(line);

    printf(cstate);
    sys_req(WRITE, COM1, itoa(state), &check);
    printf(line);

    printf(cstatus);
    sys_req(WRITE, COM1, itoa(status), &check);
    printf(line);

    printf(cprior);
    sys_req(WRITE, COM1, itoa(prior), &check);
  }
}

/// Brief Description: Displays the process name, class, state, suspended status, and priority of all PCB in the blocked queue.
///
/// Description: The process name, claas, state, suspend status, and priority of each of he PCB's in the blocked queue.
void Show_Blocked()	{
  int class, check, state, prior, status;
  char name[];
  char block[] = "Blocked Queue: \n";
  char cname[] = "Name: ";
  char cclass[] = "Class: ";
  char cstate[] = "State: ";
  char cstatus[] = "Status: ";
  char cprior[] = "Priority: ";
  char line[] = "\n";
  check = 15;

  sys_req(WRITE, COM1, block, &check );
  for(j = 0; j <= sizeof(BlockedQueue); j++){
    char* Process_Name = BlockedQueue[j];
    PCB* pcb = FindPCB(Process_Name);

    class = pcb->Process_Class;
    name = pcb->Process_Name;
    state = pcb->ReadyState;
    status = pcb->SuspendedState;
    prior = pcb->Priority;

    printf(cname);
    printf(name);
    printf(line);

    printf(cclass);
    sys_req(WRITE, COM1, itoa(class), &check);
    printf(line);

    printf(cstate);
    sys_req(WRITE, COM1, itoa(state), &check);
    printf(line);

    printf(cstatus);
    sys_req(WRITE, COM1, itoa(status), &check);
    printf(line);

    printf(cprior);
    sys_req(WRITE, COM1, itoa(prior), &check);
  }
}

/// Brief Description: Calls SetupPCB() and inserts PCB into appropriate queue.
///
/// Description: Can except a string as a pointer that is the Process Name. Can accept two integers, Priority and Class. SetupPCB() will be called and the PCB will be inserted into the appropriate queue.  An error check for unique and valid Process Name, an error check for valid  process class, and an error check for process priority.
///
/// @param Process_Name Character pointer that matches the name of process.
/// @param Priority integer that matches the priority number.
/// @param Class integer that matches the class number.
void Create_PCB(char *Process_Name, int Priority, int Class )	{
  if (FindPCB(Process_Name) == NULL)	{
    if(Priority < 0 && Priority < 10){
      if(Class == 0 || Class == 1){
        PCB* pcb = SetupPCB(Process_Name, Class, Priority);
        InsertPCB(pcb);
      } else{
        printf("\x1b[31m""\nERROR: Not a valid Class \n""\x1b[0m");
      }
    } else{
      printf("\x1b[31m""\nERROR: Not a valid Priority \n""\x1b[0m");
    }
  } else{
    printf("\x1b[31m""\nERROR: Not a valid Process Name \n""\x1b[0m");
  }
}

/// Brief Description: Removes PCB from appropriate queue and frees all associated memory.
///
/// Description: Can except a string as a pointer that is the Process Name. Removes PCB from the appropriate queue and then frees all associated memory.  An error check to make sure process name is valid.
///
/// @param Process_Name Character pointer that matches the name of process.
void Delete_PCB(char *Process_Name)	{
  // Name Error check
  // Error check (Valid Name)
  if (FindPCB(Process_Name) == NULL)	{
    printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
  }
  else {
	 RemovePCB(Process_Name);
	 FreePCB(Process_Name);
  }
}

/// Brief Description: Places a PCD in the blocked state and reinserts it into the correct queue.
///
/// Description: Can except a string as a pointer that is the Process Name.  The specified PCB will be places in a blocked state and reinserted into the appropriate queue.  An error check for a valid name occurs.
///
/// @param Process_Name Character pointer that matches the name of process.
void Block(char *Process_Name)	{
  // Name Error check
  // Error check (Valid Name)
  PCB* pcb = FindPCB(Process_Name);
  if (pcb == NULL)	{
    printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
  }
  else {
    if(pcb->ReadyState == BLOCKED)	{
    	printf("\x1b[32m""\nThis Process is already BLOCKED \n""\x1b[0m");
    }
    else	{
    	pcb->ReadyState = BLOCKED;
    }
  }
}

/// Brief Description: Places a PCD in the unblocked state and reinserts it into the correct queue.
///
/// Description: Can except a string as a pointer that is the Process Name.  The specified PCB will be places in an unblocked state and reinserted into the appropriate queue.  An error check for a valid name occurs.
///
/// @param Process_Name Character pointer that matches the name of process.
void Unblock(char *Process_Name)	{
  // Name Error check
  // Error check (Valid Name)
    PCB* pcb = FindPCB(Process_Name);
  if (pcb == NULL)	{
    printf("\x1b[31m""\nERROR: Not a valid process name \n""\x1b[0m");
  }
  else {
    if(pcb->ReadyState == READY)	{
    	printf("\x1b[32m""\nThis Process is already in the READY state \n""\x1b[0m");
    }
    else	{
    	pcb->ReadyState = READY;
    }
  }
}
