
/// Description: Includes all commands the user has access to along with their supporting functions.
///
/// Functions within userFunctions:
///     itoa, BCDtoDec, DectoBCD, SetTime, GetTime, SetDate, GetDate, version, toLowercase, help
///
///
/// Initial Implementation -- by Isiah Phares, 2021.
/// Modifications by:    Morgan Bartley 2021, Jordan Potter 2021, Greg Potts 2021.

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
	int BCDtoDec(unsigned char value)	{
		return(value-6*(value>>4));
	}

  /// Description: Changes decimal numbers to binary numbers.
  ///
  /// @param Decimal Decimal number to be changed to binary
	int  DectoBCD (int Decimal)	{
  		 return (((Decimal/10) << 4) | (Decimal % 10));
	}

  void printf(char msg[])	{
		sys_req(WRITE, COM1, msg, (int*)strlen(msg));
	}

  /// Description: sets the time register to the new values that the user inputed, all values must be inputed as SetTime(Hours, Minutes, Seconds).
  ///
  /// @param hours Integer to be set in the Hour position
  /// @param minutes Integer to be set in the Minutes position
  /// @param seconds Integer to be set in the Seconds position
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

  /// Description: retrieve and return the time values for hours, minutes, and seconds form the clock register using inb(Port,address).
  ///
  /// No parameters.
  void GetTime()	{
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
		sys_req(WRITE, COM1, itoa(hour), (int*)2);
		printf(msg1);
		minute = BCDtoDec(minutes);
		sys_req(WRITE, COM1, itoa(minute), (int*)2);
		printf(msg1);
		second = BCDtoDec(seconds);
		sys_req(WRITE, COM1, itoa(second), (int*)2);
	}

  /// Description: Sets the date register to the new values that the user inputed, all values must be inputed as SetDime(day, month, millenial, year).
  ///
  /// @param day Integer to be set in the Day position
  /// @param month Integer to be set in the Month position
  /// @param millenial Integer to be set in the Millenial position
  /// @param year Integer to be set in the Year position
  void SetDate(int day, int month, int millennial, int year)	{
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

  /// Description: Returns the full date back to the user in decimal form.
  ///
  /// No parameters.
  void GetDate()	{
		unsigned char day = BCDtoDec(inb(0x07));
		unsigned char month = BCDtoDec(inb(0x08));
		unsigned char millennial = BCDtoDec(inb(0x32));
		unsigned char year = BCDtoDec(inb(0x09));
		char msg[2] = "";
		char msg3[10] = "Date: ";
		printf(msg3);
		sys_req(WRITE, COM1, itoa(day), (int*)2);
		printf(msg);
		sys_req(WRITE, COM1, itoa(month), (int*)3);
		printf(msg);
		sys_req(WRITE, COM1, itoa(millennial), (int*)2);
		sys_req(WRITE, COM1, itoa(year), (int*)2);
	}

  /// Description: Simply returns a char containing "Version: R(module).(the iteration that module is currently on).
  ///
  /// No parameters.
	void Version()	{
		//char msg[13]="Version: R1.1";
		sys_req(WRITE, COM1, "Version: R1.1", (int*)13 );
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
		if (*request == '\0')	{
			//char msg[100]="\n GetDate \n SetDate \n GetTime \n SetTime \n Version \n";
			sys_req(WRITE, COM1, "\n GetDate \n SetDate \n GetTime \n SetTime \n Version \n", (int*)58 );
		}
		else if (strcmp(request, "GetDate") == 0)	{
			//char msg[100]="GetDate returns the current date that is loaded onto the operating system.";
			sys_req(WRITE, COM1, "GetDate returns the current date that is loaded onto the operating system.", (int*)75 );
		}
		else if (strcmp(request, "SetDate") == 0)	{
			//char msg[100]="SetDate allows the user to reset the correct date into the system, as follows Setdate (day, month, year).";
			sys_req(WRITE, COM1, "SetDate allows the user to reset the correct date into the system, as follows Setdate (day, month, year).", (int*)100 );
		}
		else if (strcmp(request, "GetTime") == 0)	{
			//char msg[100]="GetTime returns the current time as hours, minutes, seconds that is loaded onto the operating system.";
			sys_req(WRITE, COM1,"GetTime returns the current time as hours, minutes, seconds that is loaded onto the operating system.", (int*)100 );
		}
		else if (strcmp(request, "SetTime") == 0)	{
			//char msg[100]="SetTime allows the user to reset the correct time into the system, as follows SetTime (hour, minute, second).";
			sys_req(WRITE, COM1, "SetDate allows the user to reset the correct time into the system, as follows SetTime (hour, minute, second).", (int*)100 );
		}
		else if (strcmp(request, "Version") == 0)	{
			//char msg[100]="Version returns the current operating software version that the system is running.";
			sys_req(WRITE, COM1, "Version returns the current operating software version that the system is running.", (int*)100 );
		}
		else	{
			//char msg[100]=" The requested command does not exist please refer to the Help function for a full list of commands.";
			sys_req(WRITE, COM1, "\x1b[31m""The requested command does not exist please refer to the Help function for a full list of commands.""\x1b[0m", (int*)100 );
		}
	}
