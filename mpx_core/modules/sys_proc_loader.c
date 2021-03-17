/// @file

// Description: Includes all commands the user has access to along with their supporting functions.
//
// Functions within userFunctions:
//     itoa, BCDtoDec, DectoBCD, SetTime, GetTime, SetDate, GetDate, version, toLowercase, help
//
//
// Initial Implementation -- by Isiah Phares, 2021.
// Modifications by:    Morgan Bartley 2021, Jordan Potter 2021, Greg Potts 2021.
#include <stdint.h>
#include <string.h>
#include <system.h>
#include <core/serial.h>

#include <core/io.h>
#include "mpx_supt.h"
#include "R1/userFunctions.h"
#include "procsr3.h"
#include "R1/comHand.h"

#include "sys_proc_loader.h"

void sysLoader()	{
	loadSysProc("comhand",(u32int)comHand,9);
	loadSysProc("idle",(u32int)idle,0);
}

void loadSysProc(char* name, u32int func, int priority)	{
	PCB* new_pcb = SetupPCB(name, SYSTEM, priority);
	context* cp = (context*)(new_pcb->stackTop);
	memset(cp, 0, sizeof(context));
	cp->fs = 0x10;
	cp->gs = 0x10;
	cp->ds = 0x10;
	cp->es = 0x10;
	cp->cs = 0x8;
	cp->ebp = (u32int)(new_pcb->stack);
	cp->esp = (u32int)(new_pcb->stackTop);
	cp->eip = (u32int) func;// The function correlating to the process , ie. Proc1
	cp->eflags = 0x202 ;
	InsertPCB(new_pcb);
}

void Infinite()	{
	while(1)	{
		sys_req(IDLE, DEFAULT_DEVICE, NULL, NULL);
	}
}

void Alarm()	{
	while(1)	{
		int hour;
    int minute;
    int second;
    outb(0x70,0x04);
    unsigned char hours = inb(0x71);
    outb(0x70,0x02);
    unsigned char minutes = inb(0x71);
    outb(0x70,0x00);
    unsigned char seconds = inb(0x71);
    hour = BCDtoDec(hours);
    minute = BCDtoDec(minutes);
    second = BCDtoDec(seconds);

		List* list = getList()
		Alarm* alarm = list -> head;
		while(alarm != NULL){
			if(hour > alarm -> hour || (hour == alarm -> hour && minute > alarm -> minute) ||
			(hour == alarm -> hour && minute == alarm -> minute && second > alarm -> second))	{
				printf(alarm -> message);

				//removes alarm from list and frees memory
				if(list -> head == alarm)  {
			    if(alarm -> next != NULL) {
			      list -> head = alarm -> next;
			      alarm -> next -> prev = NULL;
			    }
			    else
			      list -> head = NULL;
			  }
			  else if(alarm -> next != NULL && alarm -> prev != NULL)  {
			    alarm -> prev -> next = alarm -> next;
			    alarm -> next -> prev = alarm -> prev;
			  }
			  else
			    list -> tail = alarm -> prev;
				sys_free_mem(alarm);
			}
			else
				sys_req(IDLE, DEFAULT_DEVICE, NULL, NULL);

			alarm = alarm -> next;
		}
		if(FindPCB("Alarm") != NULL)
			deletePCB("Alarm");
	}
}
