/*
  ----- comHand.c -----
  Description..: Interprets user input to call the appropriate user functions.

      Initial Implementation -- by Isiah Phares, 2021.
      Modifications by:    Morgan Bartley 2021, Jordan Potter 2021, Greg Potts 2021.
*/

#include <stdint.h>
#include <string.h>
#include <system.h>

#include <core/io.h>
#include "modules/mpx_supt.h"



	int comHand()	{
		char *cmdBuffer[100];
		int bufferSize = numCharacters;
		int quit = 0;

		while(quit != 1)	{
			char* FirstToken = strtok(cmdBuffer, "-");
   			char* SecondToken = strtok(NULL, "-");
			char* ThirdToken = strtok(NULL, "-");
			char* FourthToken = strtok(NULL, "-");
			char* FifthToken = strtok(NULL, "-");

			if(FirstToken == "help" && SecondToken == NULL)		{
				Help();
			}
			else if((FirstToken == "help" && SecondToken == "version")	{
				Help(Version);
			}
			else if((FirstToken == "help" && SecondToken == "getDate")	{
				Help(GetDate);
			}
			else if((FirstToken == "help" && SecondToken == "setDate")	{
				Help(SetDate);
			}
			else if((FirstToken == "help" && SecondToken == "getTime")	{
				Help(GetTime);
			}
			else if((FirstToken == "help" && SecondToken == "setTime")	{
				Help(SetTime);
			}

			else if(FirstToken == "version")
				Version();
			else if(FirstToken == "getdate")
				GetDate();
			else if(FirstToken == "setdate")
				SetDate(SecondToken, ThirdToken, FourthToken, FifthToken);	//input as Day-Month-Millenial-Year
			else if(FirstToken == "gettime")	//Return the current time held by the registers.
				GetTime();
			else if(FirstToken == "settime")
				SetTime(SecondToken, ThirdToken, FourthToken);		//input as Hour-Minute-Seconds
			else if(FirstToken == "quit")
				quit = 1;
		}
				//shutdown procedure
	}
}
