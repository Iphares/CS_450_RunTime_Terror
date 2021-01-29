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



	int comHand(char letter)	{
		char cmdBuffer[100];
		int bufferSize;
		int quit = 0;
	
		while(quit != 1)	{
		
			else {
				for(int index_handler =0; index_handler < 99; index_handler++)	{
					cmdBuffer[index_handler] = letter;
					if(bufferSize == '\0')	{
						bufferSize = 1;
					}
					else bufferSize++;
				}
			}
		}
	}
}