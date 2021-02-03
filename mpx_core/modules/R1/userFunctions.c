/*
  ----- userFunctions.c -----
  Description..: Includes all commands the user has access to along with their supporting functions.

      Initial Implementation -- by Isiah Phares, 2021.
      Modifications by:    Morgan Bartley 2021, Jordan Potter 2021, Greg Potts 2021.
*/

#include <stdint.h>
#include <string.h>
#include <system.h>
#include <core/serial.h>

#include <core/io.h>
#include "../mpx_supt.h"


void userFunctions(void)	{
   /*
	function: itoa
	Description: An integer is taken and seperated into individual chars and then all placed into a character array. Adapted from geeksforgeeks.org.
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
		arr = (char*)malloc(count); //memory allocation

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
	
	/*
		function: BCDtoDec
		Description: Chnages binary number to decimal numbers.
	*/
	int BCDtoDec(unsigned char value)	{
		return(value-6*(value>>4));
	}

	/*
		function: DectoBCD
		Description: Changes decimal numbers to binary numbers.
	*/
	int  DectoBCD (int Decimal)	{
  		 return (((Decimal/10) << 4) | (Decimal % 10));
	}

	void printf(char msg[])	{
		sys_req(WRITE, COM1, msg, &strlen(msg));
	}


	/*
		function: SetTime
		Description: sets the time register to the new values that the user inputed, all values must be inputed
		as SetTime(Hours, Minutes, Seconds).
	*/
	void SetTime(int hours, int minutes, int seconds)	{

		cli(); //outb(device + 1, 0x00); //disable interrupts
		outb(0x70,0x04);
		outb(0x71, DectoBCD(hours));// change to bcd
		outb(0x70,0x02);
		outb(0x71, DectoBCD(minutes));
		outb(0x70,0x00);
		outb(0x71, DectoBCD(seconds));
		sti();  //outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
	}


	/*
		function: GetTime
		Description: retrieve and return the time values for hours, minutes, and seconds form the clock
		register using inb(Port,address).
	*/
	int GetTime()	{
	int hour;
	int minute;
	int second;
		unsigned char hours = inb(0x04);
		unsigned char minutes = inb(0x02);
		unsigned char seconds = inb(0x00);
		char msg1[2] = ":";
		char msg2[10] = "Time: ";
		printf(msg2);
		hour = BCDtoDec(hours);
		sys_req(WRITE, COM1, itoa(hour), 2);
		printf(msg1);
		minute = BCDtoDec(minutes);
		sys_req(WRITE, COM1, itoa(minute), 2);
		printf(msg1);
		second = BCDtoDec(seconds);
		sys_req(WRITE, COM1, itoa(second), 2);
	}


	/*
		function: SetDate
		Description:
	*/
	void Setdate(int day, int month,int millennial, int year)	{
		cli();
		outb(0x70,0x07);
		outb(0x71,DectoBCD (day));

		outb(0x70,0x08);
		outb(0x71,DectoBCD (month));

		outb(0x70,0x32);
		outb(0x71,DectoBCD (millennial));

		outb(0x70,0x09);
		outb(0x71,DectoBCD (year));
		sti();
	}

	/*
		function: GetDate
		Description: Returns the full date back to the user in decimal form.
	*/
	int GetDate()	{
		unsigned char day = BCDtoDec(inb(0x07));
		unsigned char month = BCDtoDec(inb(0x08));
		unsigned char millennial = BCDtoDec(inb(0x32));
		unsigned char year = BCDtoDec(inb(0x09));
		char msg[2] = "";
		char msg3[10] = "Date: ";
		printf(msg3);
		sys_req(WRITE, COM1, day), 2);
		printf(msg);
		sys_req(WRITE, COM1, itoa(month), 3);
		printf(msg);
		sys_req(WRITE, COM1, itoa(millennial), 2);
		sys_req(WRITE, COM1, itoa(year), 2);
	}



	/*
		function: Version
		Description: Simply returns a char containing
		"Version: R(module).(the iteration that module is currently on).
	*/
	void Version()	{
		//char msg[13]="Version: R1.1";
		sys_req(WRITE, COM1, "Version: R1.1", 13 );
	}

	/*
		function: toLowercase
		Description: If a letter is uppercase, it changes it to lowercase. (char)
	*/
	char toLowercase(char c)	{
   		if((c >= 65) && (c <= 90))	{
        		c = c + 32;
        	}
    	return c;
    	}

	/*
		function: Help
		Description: Can except a string as a pointer, if the pointer is null then the function will print a complete list of avaliable commands
		to the console. If the pointer is a avaliable commands then instructions on how to use the command will be printed.
		If the command does not exist then a message explaining that it is not a valid command will be displayed.
	*/
	void Help(char* request)	{
		if (*request == '\0')	{
			//char msg[100]="\n GetDate \n SetDate \n GetTime \n SetTime \n Version \n";
			sys_req(WRITE, COM1, "\n GetDate \n SetDate \n GetTime \n SetTime \n Version \n", 58 );
		}
		else if (strcmp(request, "GetDate") == 0)	{
			//char msg[100]="GetDate returns the current date that is loaded onto the operating system.";
			sys_req(WRITE, COM1, "GetDate returns the current date that is loaded onto the operating system.", 75 );
		}
		else if (strcmp(request, "SetDate") == 0)	{
			//char msg[100]="SetDate allows the user to reset the correct date into the system, as follows Setdate (day, month, year).";
			sys_req(WRITE, COM1, "SetDate allows the user to reset the correct date into the system, as follows Setdate (day, month, year).", 100 );
		}
		else if (strcmp(request, "GetTime") == 0)	{
			//char msg[100]="GetTime returns the current time as hours, minutes, seconds that is loaded onto the operating system.";
			sys_req(WRITE, COM1,"GetTime returns the current time as hours, minutes, seconds that is loaded onto the operating system.", 100 );
		}
		else if (strcmp(request, "SetTime") == 0)	{
			//char msg[100]="SetTime allows the user to reset the correct time into the system, as follows SetTime (hour, minute, second).";
			sys_req(WRITE, COM1, "SetDate allows the user to reset the correct time into the system, as follows SetTime (hour, minute, second).", 100 );
		}
		else if (strcmp(request, "Version") == 0)	{
			//char msg[100]="Version returns the current operating software version that the system is running.";
			sys_req(WRITE, COM1, "Version returns the current operating software version that the system is running.", 100 );
		}
		else	{
			//char msg[100]=" The requested command does not exist please refer to the Help function for a full list of commands.";
			sys_req(WRITE, COM1, "The requested command does not exist please refer to the Help function for a full list of commands.", 100 );
		}
	}
}
