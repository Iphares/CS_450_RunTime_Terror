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
		int shutdown = 0;

		while(quit != 1)	{
			memset(cmdBuffer, '\0', 100);
		  		sys_req(READ, DEFAULT_DEVICE, cmdBuffer, &bufferSize);
			char* FirstToken = strtok(cmdBuffer, "-");
   		char* SecondToken = strtok(NULL, "-");
			char* ThirdToken = strtok(NULL, "-");
			char* FourthToken = strtok(NULL, "-");
			char* FifthToken = strtok(NULL, "-");
			if(shutdown == 0){
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
				else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"suspend") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					Help("suspend");
				}
				else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"resume") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					Help("resume");
				}
				else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"setPriority") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					Help("setPriority");
				}
				else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"showPCB") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					Help("showPCB");
				}
				else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"showAll") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					Help("showAll");
				}
				else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"showReady") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					Help("showReady");
				}
				else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"showBlocked") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					Help("showBlocked");
				}
				// Temporary R2 commands
				else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"createPCB") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					Help("createPCB");
				}
				else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"deletePCB") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					Help("deletePCB");
				}
				else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"block") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					Help("block");
				}
				else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"unblock") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					Help("unblock");
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
/************************************************************************************
				R2 userfunctions
************************************************************************************/
				if(strcmp(FirstToken,"suspend") == 0 && strcmp(SecondToken,NULL) == 0) {
					Suspend();
				}
				else if(strcmp(FirstToken,"resume") == 0 && strcmp(SecondToken,NULL) == 0) {
					Resume();
				}
				else if(strcmp(FirstToken,"setPriority") == 0 && strcmp(SecondToken,NULL) == 0) {
					setPriority();
				}
				else if(strcmp(FirstToken,"showPCB") == 0 && strcmp(SecondToken,NULL) == 0) {
					Show_PCB();
				}
				else if(strcmp(FirstToken,"showAll") == 0 && strcmp(SecondToken,NULL) == 0) {
					showAll();
				}
				else if(strcmp(FirstToken,"showReady") == 0 && strcmp(SecondToken,NULL) == 0) {
					showReady();
				}
				else if(strcmp(FirstToken,"showBlocked") == 0 && strcmp(SecondToken,NULL) == 0) {
					showBlocked();
				}

/********** R2 Temp Commands **********/
				else if(strcmp(FirstToken,"createPCB") == 0 && strcmp(SecondToken,NULL) == 0) {
					Create_PCB();
				}
				else if(strcmp(FirstToken,"deletePCB") == 0 && strcmp(SecondToken,NULL) == 0) {
					Delete_PCB();
				}
				else if(strcmp(FirstToken,"block") == 0 && strcmp(SecondToken,NULL) == 0) {
					Block();
				}
				else if(strcmp(FirstToken,"unblock") == 0 && strcmp(SecondToken,NULL) == 0) {
					Unblock();
				}

				else if(strcmp(FirstToken,"shutdown") == 0 && strcmp(SecondToken,NULL) == 0){
					printf("\x1b[33m""\nAre you sure you want to shutdown? [yes/no]\n""\x1b[0m");
					shutdown = 1;
				}
				else
					printf("\x1b[31m""\nERROR: Not a valid command \n""\x1b[0m");
			}
			else{
				if(strcmp(FirstToken,"yes") == 0 && shutdown == 1)	{
					quit = 1;
				}
				else if(strcmp(FirstToken,"no") == 0){
					printf("\x1b[33m""\nShutdown Cancelled\x1b[0m");
					shutdown = 0;
				}
				else
					printf("\x1b[31m""\nERROR: Please enter \"yes\" or \"no\" \n""\x1b[0m");
			}
		}
		return 0;	//shutdown procedure
	}
