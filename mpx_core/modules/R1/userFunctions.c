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
		int check = 13;
		//char msg[13]="Version: R1.5";
		sys_req(WRITE, COM1, "Version: R1.5 \n", &check);
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
    int check = 1;
		if (request[0] == '\0')	{
			//char msg[100]="\n GetDate \n SetDate \n GetTime \n SetTime \n Version \n";
      check = 67;
      sys_req(WRITE, COM1, "\n to chain commands and parameters, please use \"-\" between keywords", &check);
      check = 58;
			sys_req(WRITE, COM1, "\n getDate \n setDate \n getTime \n setTime \n version \n shutdown \n\n", &check);
		}
		else if (strcmp(request, "GetDate") == 0)	{
			//char msg[100]="GetDate returns the current date that is loaded onto the operating system.";
      check = 75;
			sys_req(WRITE, COM1, "\n getDate returns the current date that is loaded onto the operating system.\n", &check);
		}
		else if (strcmp(request, "SetDate") == 0)	{
			//char msg[100]="SetDate allows the user to reset the correct date into the system, as follows Setdate (day, month, year). Date must be inputed as a two digit number, Example 02 or 12";
      check = 100;
      sys_req(WRITE, COM1, "\n setDate allows the user to reset the correct date into the system, as follows setDate-"BLU"day"RESET"-"BLU"month"RESET"-"BLU"year"RESET".\n Time must be inputed as a two digit number, Example 02 or 00", &check);
		}
		else if (strcmp(request, "GetTime") == 0)	{
			//char msg[100]="GetTime returns the current time as hours, minutes, seconds that is loaded onto the operating system.";
      check = 100;
      sys_req(WRITE, COM1,"\n getTime returns the current time as hours, minutes, seconds that is loaded onto the operating system.\n", &check);
		}
		else if (strcmp(request, "SetTime") == 0)	{
			//char msg[100]="SetTime allows the user to reset the correct time into the system, as follows SetTime (hour, minute, second). Time must be inputed as a two digit number, Example 02 or 00";
      check = 100;
      sys_req(WRITE, COM1, "\n setTime allows the user to reset the correct time into the system, as follows setTime-"BLU"hour"RESET"-"BLU"minute"RESET"-"BLU"second"RESET".\n Time must be inputed as a two digit number, Example 02 or 00", &check);
		}
		else if (strcmp(request, "Version") == 0)	{
			//char msg[100]="Version returns the current operating software version that the system is running.";
      check = 100;
      sys_req(WRITE, COM1, "\n version returns the current operating software version that the system is running.\n", &check);
		}
    else if(strcmp(request, "shutdown") == 0){
      check = 100;
      sys_req(WRITE, COM1, "\n shutdown shuts down the system.\n", &check);
    }
		else	{
			//char msg[100]=" The requested command does not exist please refer to the Help function for a full list of commands.";
      check = 104;
			sys_req(WRITE, COM1, "\x1b[31m""\nThe requested command does not exist please refer to the Help function for a full list of commands.\n""\x1b[0m", &check);
		}
	}









/*********************************************************************
R2 Functions
*********************************************************************/
void Suspend(Char *Process_Name)	{
	
}
void Resume(Char *Process_Name)	{
	
}
void Set_Priority(Char *Process_Name, int Priority)	{
	
}
void Show_PCB(Char *Process_Name)	{
	
}
void Show_All()	{
	
}
void Show_Ready()	{
	
}
void Show_Blocked()	{
	
}
void Create_PCB(char *Process_Name, int Priority, int Class )	{
	
}
void Delete_PCB(Char *Process_Name)	{
	
}
void Block(Char *Process_Name)	{
	
}
void Unblock(Char *Process_Name)	{
	
}
