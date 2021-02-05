/*
  ----- comHand.c -----
  Description..: Interprets user input to call the appropriate user functions.

      Initial Implementation -- by Isiah Phares, 2021.
      Modifications by:    Morgan Bartley 2021, Jordan Potter 2021, Greg Potts 2021.
*/

#include <stdint.h>
#include <string.h>
#include <system.h>

#include <core/serial.h>
#include <core/io.h>

#include "../mpx_supt.h"
#include "userFunctions.h"



	int comHand()	{

		char cmdBuffer[100];
		int bufferSize = 99;
		int quit = 0;


		while(quit != 1)	{
			memset(cmdBuffer, '\0', 100);
		  sys_req(READ, DEFAULT_DEVICE, cmdBuffer, &bufferSize);
			char* FirstToken = strtok(cmdBuffer, "-");
   			char* SecondToken = strtok(NULL, "-");
			char* ThirdToken = strtok(NULL, "-");
			char* FourthToken = strtok(NULL, "-");
			char* FifthToken = strtok(NULL, "-");

			if(strcmp(FirstToken,"help") == 1 && strcmp(SecondToken,NULL) == 1)		{
				Help('\0');
			}
			else if(strcmp(FirstToken,"help") == 1 && strcmp(SecondToken,"version") == 1)	{
				Help("Version");
			}
			else if(strcmp(FirstToken,"help") == 1 && strcmp(SecondToken,"getDate") == 1)	{
				Help("GetDate");
			}
			else if(strcmp(FirstToken,"help") == 1 && strcmp(SecondToken,"setDate") == 1)	{
				Help("SetDate");
			}
			else if(strcmp(FirstToken,"help") == 1 && strcmp(SecondToken,"getTime") == 1)	{
				Help("GetTime");
			}
			else if(strcmp(FirstToken,"help") == 1 && strcmp(SecondToken,"setTime") == 1)	{
				Help("SetTime");
			}

			else if(strcmp(FirstToken,"version") == 1)
				Version();

			else if(strcmp(FirstToken,"getdate") == 1)
				GetDate();

			else if(strcmp(FirstToken,"setdate") == 1)
				SetDate((int)SecondToken, (int)ThirdToken, (int)FourthToken, (int)FifthToken);	//input as Day-Month-Millenial-Year
			else if(strcmp(FirstToken,"gettime") == 1)	//Return the current time held by the registers.
				GetTime();
			else if(strcmp(FirstToken,"settime") == 1)
				SetTime((int)SecondToken, (int)ThirdToken, (int)FourthToken);		//input as Hour-Minute-Seconds
			else if(strcmp(FirstToken,"quit") == 1)
				quit = 1;

		(void)FirstToken;
   	(void)SecondToken;
		(void)ThirdToken;
		(void)FourthToken;
		(void)FifthToken;
		}
		return 0;	//shutdown procedure
	}
