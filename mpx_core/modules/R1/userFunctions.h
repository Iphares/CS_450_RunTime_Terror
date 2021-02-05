/// @file
#ifndef _USER_FUNCTIONS_H
#define _USER_FUNCTIONS_H
	//! Sets the time of the system
	void SetTime(int hours, int minutes, int seconds);
	//! Gets the time of the system
	void GetTime();
	//
	int  DectoBCD (int Decimal);
	//
	char* itoa(int num);
	//! Sets the date of the system
	void SetDate(int day, int month, int millennial, int year);
	//! Changes Binary Converted Decimal to Decimal
	int BCDtoDec(unsigned char value);
	//! Gets the date of the system
	void GetDate();
	//! States the version of the system
	void Version();
	//! Gives help for another function
	void Help(char* request);
	//! Prints
	void printf(char msg[]);
	//! Changes an uppercase char to a lowercase char
	char toLowercase(char c);
#endif
