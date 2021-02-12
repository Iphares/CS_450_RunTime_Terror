/// @file

/*
  ----- comHand.c -----
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

/// Description: Interprets user input to call the appropriate user functions.
///

	int comHand()	{
		
		Help("\0");

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
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"version") == 0 && strcmp(ThirdToken,NULL) == 0)	{
				Help("Version");
			}
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"getDate") == 0 && strcmp(ThirdToken,NULL) == 0)	{
				Help("GetDate");
			}
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"setDate") == 0 && strcmp(ThirdToken,NULL) == 0)	{
				Help("SetDate");
			}
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"getTime") == 0 && strcmp(ThirdToken,NULL) == 0)	{
				Help("GetTime");
			}
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"setTime") == 0 && strcmp(ThirdToken,NULL) == 0)	{
				Help("SetTime");
			}
			else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"shutdown") == 0 && strcmp(ThirdToken,NULL) == 0)	{
				Help("shutdown");
			}

			else if(strcmp(FirstToken,"version") == 0 && strcmp(SecondToken,NULL) == 0)
				Version();

			else if(strcmp(FirstToken,"getDate") == 0 && strcmp(SecondToken,NULL) == 0)
				GetDate();

			else if(strcmp(FirstToken,"setDate") == 0){
				if (EdgeCase(SecondToken) == 1 && EdgeCase(ThirdToken) == 1 && EdgeCase(FourthToken) == 1 && EdgeCase(FifthToken) == 1)    {
				    SetDate(atoi(SecondToken), atoi(ThirdToken), atoi(FourthToken), atoi(FifthToken));
				}
				else
					printf("\x1b[31m""\nERROR: Invalid parameters for setDate \n""\x1b[0m");
			}
			else if(strcmp(FirstToken,"getTime") == 0 && strcmp(SecondToken,NULL) == 0)	//Return the current time held by the registers.
				GetTime();
			else if(strcmp(FirstToken,"setTime") == 0 && strcmp(FifthToken,NULL) == 0){
				if (EdgeCase(SecondToken) == 1 && EdgeCase(ThirdToken) == 1 && EdgeCase(FourthToken) == 1)    {
						SetTime(atoi(SecondToken), atoi(ThirdToken), atoi(FourthToken));		//input as Hour-Minute-Seconds
				}
				else
					printf("\x1b[31m""\nERROR: Invalid parameters for setTime \n""\x1b[0m");
				}
			else if(strcmp(FirstToken,"shutdown") == 0 && strcmp(SecondToken,NULL) == 0)
				printf("\x1b[33m""\n Are you sure you want to shutdwon? \n""\x1b[0m");
					if(strcmp(FirstToken,"yes") == 0)	{
						quit = 1;
					}
					else 
						break;
			else
				printf("\x1b[31m""\nERROR: Not a valid command \n""\x1b[0m");
		}
		return 0;	//shutdown procedure
	}
