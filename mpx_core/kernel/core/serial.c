/*
  ----- serial.c -----

  Description..: Contains methods and variables used for
    serial input and output.
*/

#include <stdint.h>
#include <string.h>

#include <core/io.h>
#include <core/serial.h>

#define NO_ERROR 0

// Active devices used for serial I/O
int serial_port_out = 0;
int serial_port_in = 0;

/*
  Procedure..: init_serial
  Description..: Initializes devices for user interaction, logging, ...
*/
int init_serial(int device)
{
  outb(device + 1, 0x00); //disable interrupts
  outb(device + 3, 0x80); //set line control register
  outb(device + 0, 115200/9600); //set bsd least sig bit
  outb(device + 1, 0x00); //brd most significant bit
  outb(device + 3, 0x03); //lock divisor; 8bits, no parity, one stop
  outb(device + 2, 0xC7); //enable fifo, clear, 14byte threshold
  outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
  (void)inb(device);      //read bit to reset port
  return NO_ERROR;
}

/*
  Procedure..: serial_println
  Description..: Writes a message to the active serial output device.
    Appends a newline character.
*/
int serial_println(const char *msg)
{
  int i;
  for(i=0; *(i+msg)!='\0'; i++){
    outb(serial_port_out,*(i+msg));
  }
  outb(serial_port_out,'\r');
  outb(serial_port_out,'\n');
  return NO_ERROR;
}

/*
  Procedure..: serial_print
  Description..: Writes a message to the active serial output device.
*/
int serial_print(const char *msg)
{
  int i;
  for(i=0; *(i+msg)!='\0'; i++){
    outb(serial_port_out,*(i+msg));
  }
  if (*msg == '\r') outb(serial_port_out,'\n');
  return NO_ERROR;
}

/*int (*student_read)(char *buffer, int *count);
  Procedure..: set_serial_out
  Description..: Sets serial_port_out to the given device address.
    All serial output, such as that from serial_println, will be
    directed to this device.
*/
int set_serial_out(int device)
{
  serial_port_out = device;
  return NO_ERROR;
}

/*
  Procedure..: set_serial_in
  Description..: Sets serial_port_in to the given device address.
    All serial input, such as console input via a virtual machine,
    QEMU/Bochs/etc, will be directed to this device.
*/
int set_serial_in(int device)
{
  serial_port_in = device;
  return NO_ERROR;
}

/*
  Procedure..: Polling
  Description..: Polls COM1+5 to see if there is any data from the keyboard, if there is then it runs the necessary condition checks to determine
  if the input is a special character or not. It then passes the input to the command handler.
*/
int *polling(char *cmdBuffer, int *count){
	int pointerLoc = 0;
	int numCharacters = 0;

  serial_print("Hello");

	while (1)	{ // Run continuously
		char letter = NULL;

		if(inb(COM1+5)&1)	{ // Is a character available?
			letter = inb(COM1); //Get the character

		//Special Cases

		//Enter Case
		if (letter == 13){
			cmdBuffer[pointerLoc] = '\0';
			break;
		}

		//Delete Case
		else if (letter == 46){
			if (pointerLoc <= numCharacters)	{
				int bufIndex = NULL;
				for (bufIndex = pointerLoc; pointerLoc < *count; bufIndex++)	{
					cmdBuffer[bufIndex] = cmdBuffer[bufIndex + 1];
				}
				numCharacters--;
				serial_print("\033[1D");
				inb(COM1);
			}
		}

		//Left Arrow Case
		else if (letter == 37){
			if (pointerLoc < numCharacters)	{
				pointerLoc--;
				serial_print("\033[1D");
			}
		}

		//Right Arrow Case
		else if (letter == 39){
			if (pointerLoc < numCharacters)	{
				pointerLoc++;
				serial_print("\033[1C");
			}
		}

		//Up Arrow Case
		else if (letter == 38){

		}

		//Down Arrow Case
		else if (letter == 40){

		}

		//Backspace Case
		else if (letter == 8){


			int bufIndex = NULL;
			for (bufIndex = pointerLoc; pointerLoc < *count; bufIndex++)	{
				cmdBuffer[bufIndex] = cmdBuffer[bufIndex + 1];	//replaces the last typed character with null.
			}
			numCharacters--;
			serial_print("\033[1D");
			inb(COM1);
			}
		}
		//passes any other characters 0-9,a-z, upper and lower case to the command handler to be dealt with.
		else {
			if(numCharacters < *count)	{
				cmdBuffer[pointerLoc] = letter;
				serial_print(&cmdBuffer[pointerLoc]);
				pointerLoc++;	//increments the pointer location per input.
				numCharacters++;	//increments the total number of characters passed in so far.
			}

		}

	}
	return 0;
}
