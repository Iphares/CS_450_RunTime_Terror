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
#include "startup-sound.mp3"


	int comHand()	{

		// Play startup sound from Windows XP
		PlaySound("startup-sound.mp3", NULL, SND_ASYNC);
		
		
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

			if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,NULL) == 0)		{
				Help("\0");
			}
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"version") == 0)	{
				Help("Version");
			}
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"getDate") == 0)	{
				Help("GetDate");
			}
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"setDate") == 0)	{
				Help("SetDate");
			}
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"getTime") == 0)	{
				Help("GetTime");
			}
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"setTime") == 0)	{
				Help("SetTime");
			}
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"shutdown") == 0)	{
				Help("shutdown");
			}

			else if(strcmp(FirstToken,"version") == 0)
				Version();

			else if(strcmp(FirstToken,"getDate") == 0)
				GetDate();

			else if(strcmp(FirstToken,"setDate") == 0)
				SetDate((int)SecondToken, (int)ThirdToken, (int)FourthToken, (int)FifthToken);	//input as Day-Month-Millenial-Year
			else if(strcmp(FirstToken,"getTime") == 0)	//Return the current time held by the registers.
				GetTime();
			else if(strcmp(FirstToken,"setTime") == 0)
				SetTime((int)SecondToken, (int)ThirdToken, (int)FourthToken);		//input as Hour-Minute-Seconds
			else if(strcmp(FirstToken,"shutdown") == 0)
				quit = 1;
			else
				printf("\x1b[31m""\nERROR: Not a valid command \n""\x1b[0m");
		}
		return 0;	//shutdown procedure
	}
