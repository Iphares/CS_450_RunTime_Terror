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
	loadSysProc("Infinite",,(u32int)Infinite,0);
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
