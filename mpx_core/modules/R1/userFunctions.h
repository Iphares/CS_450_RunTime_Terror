
	//! Sets the time of the system
	void SetTime(int hours, int minutes, int seconds);
	//! Gets the time of the system
	int GetTime();
	//! Sets the date of the system
	void Setdate(int day, int month, int year);
	//! Changes Binary Converted Decimal to Decimal
	int BCDtoDec(unsigned char value);
	//! Gets the date of the system
	int GetDate();
	//! States the version of the system
	void Version();
	//! Gives help for another function
	void Help(char* request);
	//! Prints
	void printf(char msg[]);
	//! Changes an uppercase char to a lowercase char
	char toLowercase(char c);
