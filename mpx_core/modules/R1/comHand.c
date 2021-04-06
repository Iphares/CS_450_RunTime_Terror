// @file

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
#include "../R5/R5commands.h"

/// Description: Interprets user input to call the appropriate user functions.
///

	int comHand()	{

		Help("\0");

		char cmdBuffer[100];
		int bufferSize = 99;
		int quit = 0;
		int shutdown = 0;
/************************************************************************************
				Aliasing
************************************************************************************/
		//aliasing initialization
		char Aliasing[20][20];
		char Aliased[20][20];
		// for(int alias_init = 0; alias_init < 19; alias_init++)	{
		// 	Aliasing[alias_init][0]	= NULL;
		// }
/************************************************************************************

************************************************************************************/


		while(quit != 1)	{
			memset(cmdBuffer, '\0', 100);
		  sys_req(READ, DEFAULT_DEVICE, cmdBuffer, &bufferSize);
			char* FirstToken = strtok(cmdBuffer, "-");
   			char* SecondToken = strtok(NULL, "-");
			char* ThirdToken = strtok(NULL, "-");
			char* FourthToken = strtok(NULL, "-");
			char* FifthToken = strtok(NULL, "-");
			if(shutdown == 0)	{


/************************************************************************************
				Aliasing
************************************************************************************/
	if(strcmp(FirstToken,"alias") == 0 && strcmp(FourthToken,NULL) == 0)		{
		for(int i=0; i<20; i++){
			if(aliasing[0][i] != NULL){
				strcpy(aliasing[0]*, ThirdToken); //New Token
				strcpy(aliased[0]*, SecondToken); //Original Token
				break;
			}
		}
	}
/************************************************************************************

************************************************************************************/













				label: aliasing;
/************************************************************************************
				R1 comHand
************************************************************************************/
					else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,NULL) == 0)		{
						Help("\0");
					}
					//R1 Commands
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
					// R2 Commands
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
					// else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"createPCB") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					// 	Help("createPCB");
					// }
					else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"deletePCB") == 0 && strcmp(ThirdToken,NULL) == 0)	{
						Help("deletePCB");
					}
					// else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"block") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					// 	Help("block");
					// }
					// else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"unblock") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					// 	Help("unblock");
					// }
					else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"shutdown") == 0 && strcmp(ThirdToken,NULL) == 0)	{
						Help("shutdown");
					}
					else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"infinite") == 0 && strcmp(ThirdToken,NULL) == 0)	{
						Help("infinte");
					}
					// R4 Commands
					else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"loadr3") == 0 && strcmp(ThirdToken,NULL) == 0)	{
						Help("loadr3");
					}
					else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"alarm") == 0 && strcmp(ThirdToken,NULL) == 0)	{
						Help("alarm");
					}
					// Bonus Command
					else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"clear") == 0 && strcmp(ThirdToken,NULL) == 0)	{
						Help("clear");
					}
					// Temporary R5 Commands
					// else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"clear") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					// 	Help("heap");
					// }
					// else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"clear") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					// 	Help("alloc");
					// }
					// else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"clear") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					// 	Help("free");
					// }
					// else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"clear") == 0 && strcmp(ThirdToken,NULL) == 0)	{
					// 	Help("empty");
					// }
					// R5 Commands
					else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"clear") == 0 && strcmp(ThirdToken,NULL) == 0)	{
						Help("showFree");
					}
					else if(strcmp(FirstToken,"help") == 0 && strcmp(SecondToken,"clear") == 0 && strcmp(ThirdToken,NULL) == 0)	{
						Help("showAlloc");
					}






					else if(strcmp(FirstToken,"version") == 0 && strcmp(SecondToken,NULL) == 0)
						Version();
					else if(strcmp(FirstToken,"clear") == 0 && strcmp(SecondToken,NULL) == 0)
						clear();

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
					R2 comHand
	************************************************************************************/
					else if(strcmp(FirstToken,"suspend") == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						Suspend(SecondToken);
					}
					else if(strcmp(FirstToken,"resume") == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						Resume(SecondToken);
					}
					else if(strcmp(FirstToken,"setPriority") == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						if(EdgeCase(ThirdToken) == 1)	{
							Set_Priority(SecondToken, atoi(ThirdToken));	//input as setPriority-Process_Name-Priority
						}
						else
							printf("\x1b[31m""\nERROR: Invalid parameters for setPriority, priority must be entered as a integer. \n""\x1b[0m");
					}
					else if(strcmp(FirstToken,"showPCB") == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						Show_PCB(SecondToken);
						printf("\n");
					}
					else if(strcmp(FirstToken,"showAll") == 0 && strcmp(SecondToken,NULL) == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						Show_All();
						printf("\n");
					}
					else if(strcmp(FirstToken,"showReady") == 0 && strcmp(SecondToken,NULL) == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						Show_Ready();
						printf("\n");
					}
					else if(strcmp(FirstToken,"showBlocked") == 0 && strcmp(SecondToken,NULL) == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						Show_Blocked();
						printf("\n");
					}



					/********** R2 Temp Commands **********/
					//Removed from active for R3/R4
					/*
					else if(strcmp(FirstToken,"createPCB") == 0) {
						if( strlen(SecondToken) < 11)	{
								Create_PCB(SecondToken, atoi(ThirdToken), atoi(FourthToken));		//input as Process_Name-Priority-Class
						}
						else
							printf("\x1b[31m""\nERROR: Invalid parameters for createPCB, Process_name must only contain 10 or fewer characters. \n""\x1b[0m");
					}
					*/
					else if(strcmp(FirstToken,"deletePCB") == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						Delete_PCB(SecondToken);
					}



					//Removed from active for R3/R4
					/*
					else if(strcmp(FirstToken,"block") == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						Block(SecondToken);
					}
					else if(strcmp(FirstToken,"unblock") == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						Unblock(SecondToken);
					}
					*/
	/************************************************************************************
					R3 comHand
	************************************************************************************/
					//Removed for R4
					/*
					else if(strcmp(FirstToken,"yield") == 0 && strcmp(SecondToken,NULL) == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						yield();
						printf("\n");
					}
					else if(strcmp(FirstToken,"loadr3") == 0 && strcmp(SecondToken,NULL) == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						loader();
						printf("\n");
					}
					*/
	/************************************************************************************
					R4 comHand
	************************************************************************************/
					else if(strcmp(FirstToken,"alarm") == 0) {
						if (EdgeCase(ThirdToken) == 1 && EdgeCase(FourthToken) == 1 && EdgeCase(FifthToken) == 1)    {
							if (atoi(ThirdToken) < 24 && atoi(FourthToken) < 60 && atoi(FifthToken) < 60)    {
								loaderalarm(SecondToken, atoi(ThirdToken), atoi(FourthToken), atoi(FifthToken));
								printf("\n");	//input as Message-Hour-Minute-Seconds
							}
							else
							printf("\x1b[31m""\nERROR: Invalid parameters for alarm, must be a valid time \n""\x1b[0m");
						}
						else
							printf("\x1b[31m""\nERROR: Invalid parameters for alarm \n""\x1b[0m");

					}
					else if(strcmp(FirstToken,"loadr3") == 0 && strcmp(SecondToken,NULL) == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						loader();
						printf("\n");
					}
					else if(strcmp(FirstToken,"infinite") == 0 && strcmp(SecondToken,NULL) == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						loaderinfinite();
						printf("\n");
					}

	/************************************************************************************
					R5 comHand
	************************************************************************************/
					// else if(strcmp(FirstToken,"heap") == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
					// 	Init_Heap(atoi(SecondToken));
					// }
					// else if(strcmp(FirstToken,"alloc") == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
 					// 	Alloc_Mem(atoi(SecondToken));
					// }
					// else if(strcmp(FirstToken,"free") == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
					// 	Free_Mem(atoi(SecondToken));
					// }
					// else if(strcmp(FirstToken,"empty") == 0 && strcmp(SecondToken,NULL) == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
					// 	IsEmpty();
					// }
					else if(strcmp(FirstToken,"showFree") == 0 && strcmp(SecondToken,NULL) == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
 						ShowFree();
					}
					else if(strcmp(FirstToken,"showAlloc") == 0 && strcmp(SecondToken,NULL) == 0 && strcmp(ThirdToken,NULL) == 0 && strcmp(FourthToken,NULL) == 0 && strcmp(FifthToken,NULL) == 0) {
						ShowAlloc();
					}

	/************************************************************************************
					shutdown comHand
	************************************************************************************/
					else if(strcmp(FirstToken,"shutdown") == 0 && strcmp(SecondToken,NULL) == 0){
						printf("\x1b[33m""\nAre you sure you want to shutdown? [yes/no]\n""\x1b[0m");
						shutdown = 1;
					}
					else	{
						/************************************************************************************
										Aliasing
						************************************************************************************/
						for(int alias_init = 0; alias_init < 19; alias_init++)	{
							if(strcmp(Aliasing[i]*, FirstToken) == 0)	{

								//some how jump back to the top of this code and use as the firstToken to then check through the if conditions
								char* aliastoken = Aliased[i]*;
								goto aliasing;
							}
						}

						/************************************************************************************

						************************************************************************************/

						printf("\x1b[31m""\nERROR: Not a valid command \n""\x1b[0m");
					}
				}
				else{
					if(strcmp(FirstToken,"yes") == 0 && shutdown == 1)	{
						quit = 1;
					}
					else if(strcmp(FirstToken,"no") == 0){
						printf("\x1b[33m""\nShutdown Cancelled\x1b[0m \n");
						shutdown = 0;
					}
					else
						printf("\x1b[31m""\nERROR: Please enter \"yes\" or \"no\" \n""\x1b[0m");
				}
				sys_req(IDLE, DEFAULT_DEVICE, NULL, NULL);
		}
		getReady() -> head = NULL;
		sys_req(EXIT, DEFAULT_DEVICE, NULL, NULL);
		return 0;	//shutdown procedure
	}
