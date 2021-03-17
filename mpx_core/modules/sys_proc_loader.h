/// @file

// Description: Includes all commands the user has access to along with their supporting functions.
//
// Functions within userFunctions:
//     itoa, BCDtoDec, DectoBCD, SetTime, GetTime, SetDate, GetDate, version, toLowercase, help
//
//
// Initial Implementation -- by Isiah Phares, 2021.
// Modifications by:    Morgan Bartley 2021, Jordan Potter 2021, Greg Potts 2021.


void sysLoader();
void loadSysProc(char* name, u32int func, int priority);
void InfiniteProc();
void AlarmProc();
