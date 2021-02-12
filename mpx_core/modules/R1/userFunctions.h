/// @file
#ifndef _USER_FUNCTIONS_H
#define _USER_FUNCTIONS_H


#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

	// Sets the time of the system
	void SetTime(int hours, int minutes, int seconds);
	// Gets the time of the system
	void GetTime();
	//
	int  DectoBCD (int Decimal);
	//
	char* itoa(int num);
	// Sets the date of the system
	void SetDate(int day, int month, int millennium, int year);
	// Changes Binary Converted Decimal to Decimal
	int BCDtoDec(int BCD);
	// Gets the date of the system
	void GetDate();
	// States the version of the system
	void Version();
	// Gives help for another function
	void Help(char* request);
	// Prints
	void printf(char msg[]);
	// Changes an uppercase char to a lowercase char
	char toLowercase(char c);
#endif
