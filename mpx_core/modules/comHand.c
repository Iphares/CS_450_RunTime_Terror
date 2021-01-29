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



	int comHand(char *cmdBuffer)	{
		int bufferSize = strlen(*cmdBuffer);
		int quit = 0;
	
		while(quit != 1)	{
		
			
			if(cmdBuffer == "help")
				if(
				Help();
			else if(cmdBuffer == "version")
				Version();
			else if(cmdBuffer == "getdate")
				GetDate();
			else if(cmdBuffer == "setdate")
				SetDate();
			else if(cmdBuffer == "gettime")
				SetTime();
		}
	}
}
