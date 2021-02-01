	/*
  ----- userFunctions.c -----
  Description..: Includes all commands the user has access to along with their supporting functions.
      
      Initial Implementation -- by Isiah Phares, 2021. 
      Modifications by:    Morgan Bartley 2021, Jordan Potter 2021, Greg Potts 2021.
*/

#include <stdint.h>
#include <string.h>
#include <system.h>

#include <core/io.h>
#include "modules/mpx_supt.h"


void userFunctions(void)	{
	
	/*
		function: SetTime
		Description: sets the time register to the new values that the user inputed, all values must be inputed
		as SetTime(Hours, Minutes, Seconds).
	*/
	void SetTime(int hours, int minutes, int seconds)	{
		cli(); //outb(device + 1, 0x00); //disable interrupts
		outb(0x70,0x04);
		outb(0x71, DectoBCD (hours));// change to bcd
		outb(0x70,0x02);
		outb(0x71, DectoBCD (minutes));
		outb(0x70,0x00);
		outb(0x71, DectoBCD (seconds));
		sti();  //outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
	}
	
	
	/*
		function: GetTime
		Description: retrieve and return the time values for hours, minutes, and seconds form the clock 
		register using inb(Port,address).
	*/
	int GetTime()	{
		unsigned char hours = outb(0x70,0x04);
		unsigned char minutes = outb(0x70,0x02);
		unsigned char seconds = outb(0x70,0x00);
		return( BCDtoDec(hours),  BCDtoDec(minutes),  BCDtoDec(seconds));
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
		unsigned char day = BCDtoDec(inb(0x70,0x07));
		unsigned char month = BCDtoDec(inb(0x70,0x08));
		unsigned char year = BCDtoDec(inb(0x70,0x09));
		int msg[30] = ""
	}
	
	/*
		function: BCDtoDec
		Description: 
	*/
	int BCDtoDec(unsigned char value)	{
		return(value-6*(value>>4));
	}
	
	/*
		function: DectoBCD
		Description: 
	*/
	int  DectoBCD (int Decimal)	{
  		 return (((Decimal/10) << 4) | (Decimal % 10));
	}
	
	/*
		function: Version
		Description: Simply returns a char containing 
		"Version: R(module).(the iteration that module is currently on). 
	*/
	void Version()	{
		//char msg[13]="Version: R1.1";
		sys_req(WRITE, device_id, "Version: R1.1", 13 );
	}
	
	/*
		function: toLowercase
		Description:  
	*/
	toLowercase(c)	{ 
   		if((c >= 65) && (c <= 90))	{ 
        		c = c + 32; 
        	}
    	return c;
    	}
	
	/*
		function: toLowercase
		Description:  
	*/
	toLowercase(str)  {
	    int i;
   	    for(i = 0; i <= strlen(str); i++)	{
        	if(str[i] >= 65 && str[i] <= 90)  {
            		str[i] = str[i] + 32;
            	}
            }
            return str;
        }
	
	/*
		function: Help 
		Description: Can except a string as a pointer, if the pointer is null then the function will print a complete list of avaliable commands
		to the console. If the pointer is a avaliable commands then instructions on how to use the command will be printed.
		If the command does not exist then a message explaining that it is not a valid command will be displayed.
	*/
	void Help(char* request)	{
		if (*request == '\0')	{
			char msg[100]=	 "\n GetDate \n SetDate \n GetTime \n SetTime \n Version \n";
			sys_req(WRITE, device_id, msg, 100 );
		}
		else if (strcmp(request, "GetDate") == 0)	{
			char msg[100]="GetDate returns the current date that is loaded onto the operating system.";
			sys_req(WRITE, device_id, msg, 100 );
		}
		else if (strcmp(request, "SetDate") == 0)	{
			char msg[100]="SetDate allows the user to reset the correct date into the system, as follows Setdate (day, month, year).";
			sys_req(WRITE, device_id, msg, 100 );
		}
		else if (strcmp(request, "GetTime") == 0)	{
			char msg[100]="GetTime returns the current time as hours, minutes, seconds that is loaded onto the operating system.";
			sys_req(WRITE, device_id, msg, 100 );
		}
		else if (strcmp(request, "SetTime") == 0)	{
			char msg[100]="SetDate allows the user to reset the correct time into the system, as follows SetTime (hour, minute, second).";
			sys_req(WRITE, device_id, msg, 100 );
		}
		else if (strcmp(request, "Version") == 0)	{
			char msg[100]="GetTime returns the current operating software version that the system is running.";
			sys_req(WRITE, device_id, msg, 100 );
		}
		else	{
			char msg[100]=" The requested command does not exist please refer to the Help function for a full list of commands.";
			sys_req(WRITE, device_id, msg, 100 );
		}
	}
	
	printf(char msg[])	{
		sys_req(WRITE, device_id, msg, strlen(msg[]);
	}
}
