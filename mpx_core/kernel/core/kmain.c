/// @file

/*
  ----- kmain.c -----

  Description..: Kernel main. The first function called after
      the bootloader. Initialization of hardware, system
      structures, devices, and initial processes happens here.

      Initial Kernel -- by Forrest Desjardin, 2013,
      Modifications by:    Andrew Duncan 2014,  John Jacko 2017
      				Ben Smith 2018, and Alex Wilson 2019
*/
#include <stdint.h>
#include <string.h>
#include <system.h>

#include <core/io.h>
#include <core/serial.h>
#include <core/tables.h>
#include <core/interrupts.h>
#include <mem/heap.h>
#include <mem/paging.h>

#include <modules/mpx_supt.h>
#include "modules/R1/comHand.h"
#include "modules/sys_proc_loader.h"
#include "modules/R1/userFunctions.h"
#include "modules/R5/R5commands.h"
#include "modules/R5/MCB.h"

void kmain(void)
{
   extern uint32_t magic;
   // Uncomment if you want to access the multiboot header
   // extern void *mbd;
   // char *boot_loader_name = (char*)((long*)mbd)[16];


   // 0) Initialize Serial I/O
   // functions to initialize serial I/O can be found in serial.c
   // there are 3 functions to call
   init_serial(COM1);
   set_serial_in(COM1);
   set_serial_out(COM1);


   klogv("Starting MPX boot sequence...");
   klogv("Initialized serial I/O on COM1 device...");
	
     //Custom StartUp Screen
  printf("\n");
  // 1
  printf("\e[0;35m""(((((");
  printf("\e[0;34m""##################%%#####################################");
  printf("\e[0;35m""(((");
  printf("\e[0;34m""##%##%%%%%#%%%%%%%%#####%%%%%%%%%%% \n");
  // 2
  printf("\e[0;35m""(((((((");
  printf("\e[0;34m""#############%%#######################################");
  printf("\e[0;35m""(((((");
  printf("\e[0;34m""#%%%%%%%%%%%%%%%##########%%%%%%%% \n");
  // 3
  printf("\e[0;35m""(((((((((");
  printf("\e[0;34m""###########/#");
  printf("\e[0;32m""(((");
  printf("\e[0;34m""#%################################");
  printf("\e[0;35m""(((((((");
  printf("\e[0;34m""#%%%%%%%%%%%%#######%%%########### \n");
  // 4
  printf("\e[0;35m""(((((((((((");
  printf("\e[0;34m""########%");
  printf("\e[0;32m""(((((((((");
  printf("\e[0;34m""%########%");
  printf("\e[0;32m""((");
  printf("\e[0;34m""######%#########");
  printf("\e[0;35m""((((((((((((");
  printf("\e[0;34m""#%%%%%#%##%%#%%%%%%%%%%%%%%#### \n");
  // 5
  printf("\e[0;35m""((((((((((((((");
  printf("\e[0;34m""#####%/");
  printf("\e[0;32m""((((((((((");
  printf("\e[0;34m""####%");
  printf("\e[0;32m""((((((");
  printf("\e[0;34m""%#####/######");
  printf("\e[0;35m""((((((((((((((");
  printf("\e[0;34m""#########%%#%%%%%%%%%%%%%%%%%## \n");
  // 6
  printf("\e[0;35m""((((((((((((((((((");
  printf("\e[0;34m""##/");
  printf("\e[0;32m""((((((((((");
  printf("\e[0;34m""%#%");
  printf("\e[0;32m""(((((((((");
  printf("\e[0;34m""###%,  #");
  printf("\e[0;35m""(((((((((((((((((((");
  printf("\e[0;34m""#######%%%%%%%%%%%%%%%%%%%%%%# \n");
  // 7
  printf("\e[0;35m""((((((((((((((");
  printf("\e[0;95m""/////");
  printf("\e[0;32m""((((((((((((");
  printf("\e[0;34m""#%");
  printf("\e[0;32m""((((((((((");
  printf("\e[0;34m""##");
  printf("\e[0;95m""(////////////");
  printf("\e[0;35m""((((((((((((");
  printf("\e[0;34m""######%%%%%%%%%%%%%%%%%##%%%%% \n");
  //8
  printf("\e[0;35m""(((((((((((((((");
  printf("\e[0;95m""//");
  printf("\e[0;35m""((((((");
  printf("\e[0;34m""#");
  printf("\e[0;32m""(((((((((");
  printf("\e[0;34m""#");
  printf("\e[0;32m""(((((((");
  printf("\e[0;95m""(///////////////////");
  printf("\e[0;35m""(((((((((");
  printf("\e[0;34m""######%%%%%%%%%%%%%%##%%%%%%%% \n");
  // 9
  printf("\e[0;35m""(((((((((((((((((((((((((((((((((((((((");
  printf("\e[0;95m""(//////////////////////");
  printf("\e[0;35m""((#");
  printf("\e[0;35m""((((((");
  printf("\e[0;34m""#####%%%%%%%%%%%%%##%%%%%%%%% \n");
  // 10
  printf("\e[0;35m""(((((((((((((((((((((((((/((");
  printf("\e[0;95m""(/////");
  printf("\e[0;35m""(((((");
  printf("\e[0;95m""(///////////////////////");
  printf("\e[0;35m""(((((((((");
  printf("\e[0;34m""######%%%%%%%%%%%#%%%%%%%%## \n");
  // 11
  printf("\e[0;35m""(((((((((((((((((((((");
  printf("\e[0;95m""(///////////////");
  printf("\e[0;35m""(");
  printf("\e[0;95m""(/////////////////////////");
  printf("\e[0;35m""(((((((((");
  printf("\e[0;34m""#########%%%%%%%%%%%%%%#### \n");
  // 12
  printf("\e[0;34m""############");
  printf("\e[0;35m""(((((((");
  printf("\e[0;95m""(/////////////////");
  printf("\e[0;35m""(");
  printf("\e[0;95m""(/////////////////////////");
  printf("\e[0;35m""(");
  printf("\e[0;95m""(/////");
  printf("\e[0;35m""(((");
  printf("\e[0;34m""##########%%%%%%%%%####### \n");
  // 13
  printf("\e[0;34m""###############");
  printf("\e[0;35m""(((");
  printf("\e[0;95m""(///////////////////");
  printf("\e[0;35m""(");
  printf("\e[0;95m""(///////////////////////");
  printf("\e[0;35m""(((");
  printf("\e[0;95m""(///");
  printf("\e[0;35m""(((((");
  printf("\e[0;34m""######################### \n");
  // 14
  printf("\e[0;34m""##################");
  printf("\e[0;95m""(////////////////////");
  printf("\e[0;35m""(");
  printf("\e[0;95m""(////////////////////");
  printf("\e[0;35m""((((((((((((((((");
  printf("\e[0;34m""####################### \n");
  // 15
  printf("\e[0;34m""##################");
  printf("\e[0;95m""(/////////////////////");
  printf("\e[0;35m""(");
  printf("\e[0;34m""##");
  printf("\e[0;95m""(///////////////");
  printf("\e[0;34m""###");
  printf("\e[0;95m""(////////");
  printf("\e[0;35m""((((((((");
  printf("\e[0;34m""##################### \n");
  // 16
  printf("\e[0;34m""######");
  printf("\e[0;95m""(//////");
  printf("\e[0;35m""(");
  printf("\e[0;34m""#####");
  printf("\e[0;95m""(/////////////////////");
  printf("\e[0;35m""((");
  printf("\e[0;34m""######");
  printf("\e[0;35m""(((((");
  printf("\e[0;34m""######");
  printf("\e[0;95m""///,      *//");
  printf("\e[0;35m""((((((,   ");
  printf("\e[0;34m""#################  \n");
  // 17
  printf("\e[0;35m""((((");
  printf("\e[0;95m""(//////////");
  printf("\e[0;35m""((((");
  printf("\e[0;95m""(////////////////");
  printf("\e[0;34m""##%#");
  printf("\e[0;95m""(///");
  printf("\e[0;35m""(");
  printf("\e[0;95m""(/. /");
  printf("\e[0;34m""####");
  printf("\e[0;95m""(//////////     *////");
  printf("\e[0;35m""(((((,  (");
  printf("\e[0;34m""#%#####%########  \n");
  // 18
  printf("\e[0;35m""((((");
  printf("\e[0;95m""(//////////");
  printf("\e[0;35m""(((((((");
  printf("\e[0;95m""(/////*/**");
  printf("\e[0;35m""((");
  printf("\e[0;34m""##");
  printf("\e[0;95m""(/////*      (///");
  printf("\e[0;35m""(");
  printf("\e[0;34m""##");
  printf("\e[0;95m""////////,    ");
  printf("\e[0;35m""(*(,    .(( /((        (");
  printf("\e[0;34m""#######  \n");
  // 19
  printf("\e[0;35m""(#    ...,,,(((((.   #((((((    ");
  printf("\e[0;34m""##");
  printf("\e[0;95m""(////////(     //////*       /(,     ./.     ");
  printf("\e[0;34m""#");
  printf("\e[0;35m""/((    .(((, *");
  printf("\e[0;34m""######  \n");
  // 20
  printf("\e[0;35m""((((,     .(((((#");
  printf("\e[0;95m""    .////(   ,/");
  printf("\e[0;34m""#");
  printf("\e[0;95m""(//(***//(/     ///(.   *(//  //,    ,//");
  printf("\e[0;35m""(     (((");
  printf("\e[0;34m""#      ");
  printf("\e[0;35m""((((((((");
  printf("\e[0;34m""### \n");
  // 21
  printf("\e[0;35m""(((((*     (((((      ");
  printf("\e[0;95m""*///.  *//");
  printf("\e[0;34m""#");
  printf("\e[0;95m"".   *,   /(     //(     ");
  printf("\e[0;34m""##");
  printf("\e[0;95m""//*(//,    *//");
  printf("\e[0;34m""#     ");
  printf("\e[0;35m""(((((/       /((((((( \n");
  // 22
  printf("\e[0;34m""######.     ###/       ");
  printf("\e[0;95m""///  ,/(    ////   /(     //.    ,");
  printf("\e[0;34m""##");
  printf("\e[0;95m""//////,    /");
  printf("\e[0;34m""###     #");
  printf("\e[0;35m""((((");
  printf("\e[0;34m""#");
  printf("\e[0;35m""((,.     (((((( \n");
  // 23
  printf("\e[0;34m""#######     .##        ");
  printf("\e[0;95m""*/   //    */*");
  printf("\e[0;34m""#   ");
  printf("\e[0;95m""(//     //     .");
  printf("\e[0;34m""#####");
  printf("\e[0;35m""(((,    /");
  printf("\e[0;34m""###    ");
  printf("\e[0;35m"".%((,  ");
  printf("\e[0;34m""#");
  printf("\e[0;35m""((/*    *((/(( \n");
  // 24
  printf("\e[0;34m""#######");
  printf("\e[0;95m""/     //  /*     *  //.    *.  ,/////     //.     ,////,//,    /");
  printf("\e[0;34m""#");
  printf("\e[0;35m""(");
  printf("\e[0;34m""#");
  printf("\e[0;35m""     ,(((,  ./*    .");
  printf("\e[0;34m""#");
  printf("\e[0;35m""..(/( \n");
  // 25
  printf("\e[0;34m""########        ");
  printf("\e[0;95m""///       *//     /");
  printf("\e[0;34m""#");
  printf("\e[0;95m""(///////     ///          *//,    *(");
  printf("\e[0;34m""###&(/(#((#(/###*/##");
  printf("\e[0;35m""(((((((( \n");
  // 26
  printf("\e[0;34m""#########      ");
  printf("\e[0;95m"".(///      ///.      */*. */(      .");
  printf("\e[0;34m""###");
  printf("\e[0;95m""(*,,*/////////////");
  printf("\e[0;34m""###");
  printf("\e[0;35m""((((((((((/(((((((((((((( \n");
  // 27
  printf("\e[0;35m""((((((((((     ");
  printf("\e[0;95m""(/(//.    *////*        *");
  printf("\e[0;35m""(((((((");
  printf("\e[0;34m""#(#(");
  printf("\e[0;34m""###");
  printf("\e[0;95m""(/////////////////(");
  printf("\e[0;34m""##");
  printf("\e[0;35m""((((((((");
  printf("\e[0;34m""#");
  printf("\e[0;35m""(/(((((((((((((( \n");
  // 28
  printf("\e[0;35m""((((((((((*   *(((((");
  printf("\e[0;34m""#   ");
  printf("\e[0;95m"".////////");
  printf("\e[0;35m""((((((((");
  printf("\e[0;95m""(///////////");
  printf("\e[0;35m""((((((((((((((((((((((((((((((((((((((((((((((( \n");
  // 29
  printf("\e[0;35m""(((((((((((((((((((((((((((((");
  printf("\e[0;95m""(///////");
  printf("\e[0;35m""(");
  printf("\e[0;95m""(///////");
  printf("\e[0;32m""###################################################");
  printf("\e[0;35m""((( \n");
  // 30
  printf("\e[0;35m""((((((((((((((((((((((((((((");
  printf("\e[0;95m""(///////");
  printf("\e[0;35m""((");
  printf("\e[0;95m""(///////");
  printf("\e[0;32m""#                                                 #");
  printf("\e[0;35m""((( \n");
  // 31
  printf("\e[0;35m""(((((((((((((((((((((((((((");
  printf("\e[0;95m""(////////");
  printf("\e[0;35m""(");
  printf("\e[0;95m""(////////");
  printf("\e[0;32m""#  ******   ******** ********   ******    ******  #");
  printf("\e[0;35m""((( \n");
  // 32
  printf("\e[0;34m""############################");
  printf("\e[0;95m""(//////");
  printf("\e[0;35m""(");
  printf("\e[0;34m""#");
  printf("\e[0;95m""(////////");
  printf("\e[0;32m""# **    **     **       **     **    **  **    ** #");
  printf("\e[0;35m""((( \n");
  // 33
  printf("\e[0;34m""#############################");
  printf("\e[0;95m""(//////");
  printf("\e[0;34m""##");
  printf("\e[0;95m""////////");
  printf("\e[0;32m""# **    **     **       **     **    **   **      #");
  printf("\e[0;34m""### \n");
  // 34
  printf("\e[0;34m""#################################");
  printf("\e[0;35m""((((");
  printf("\e[0;34m""##");
  printf("\e[0;95m""(//////");
  printf("\e[0;32m""# **  **       **       **     **    **     **    #");
  printf("\e[0;34m""### \n");
  // 35
  printf("\e[0;34m""#########################################");
  printf("\e[0;95m""(////");
  printf("\e[0;32m""# **    **     **       **     **    **       **  #");
  printf("\e[0;34m""### \n");
  // 36
  printf("\e[0;34m""############################################");
  printf("\e[0;35m""((");
  printf("\e[0;32m""# **    **     **       **     **    **  **    ** #");
  printf("\e[0;34m""### \n");
  // 37
  printf("\e[0;35m""((((((((((((((((((((((((((((((((((((((((((((((");
  printf("\e[0;32m""# **    **     **       **      ******    ******  #");
  printf("\e[0;34m""### \n");
  // 38
  printf("\e[0;35m""((((((((((((((((((((((((((((((((((((((((((((((");
  printf("\e[0;32m""#                                                 #");
  printf("\e[0;34m""### \n");
  // 39
  printf("\e[0;35m""((((((((((((((((((((((((((((((((((((((((((((((");
  printf("\e[0;32m""###################################################");
  printf("\e[0;34m""### \n");
  // 40
  printf("\e[0;35m""((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((");
  printf("\e[0;34m""#################### \n""\e[0;37m");
  printf("\n");
  printf("\n");


   // 1) Initialize the support software by identifying the current
   //     MPX Module.  This will change with each module.
   // you will need to call mpx_init from the mpx_supt.c
 	 mpx_init(IO_MODULE);

   // 2) Check that the boot was successful and correct when using grub
   // Comment this when booting the kernel directly using QEMU, etc.
   if ( magic != 0x2BADB002 ){
     //kpanic("Boot was not error free. Halting.");
   }

   // 3) Descriptor Tables -- tables.c
   //  you will need to initialize the global
   // this keeps track of allocated segments and pages
   klogv("Initializing descriptor tables...");
	 init_gdt();

    // 4)  Interrupt vector table --  tables.c
    // this creates and initializes a default interrupt vector table
    // this function is in tables.c
    klogv("Interrupt vector table initialized!");
    init_pic();
    init_idt();
    init_irq();

   // 5) Virtual Memory -- paging.c  -- init_paging
   //  this function creates the kernel's heap
   //  from which memory will be allocated when the program calls
   // sys_alloc_mem UNTIL the memory management module  is completed
   // this allocates memory using discrete "pages" of physical memory
   // NOTE:  You will only have about 70000 bytes of dynamic memory
   klogv("Initializing virtual memory...");
	 init_paging();
   init_heap(25000);
   sys_set_malloc(AllocMem);
   sys_set_free(FreeMem);

   // 6) Call YOUR command handler -  interface method
   klogv("Transferring control to commhand...");
   // INSERT OS LAUNCH TEXT HERE
	//for R4 remove comhand from here this will become a process
	/*************************/
	 	// comHand();
	/*************************/
	 sysLoader();
	 yield();


   // 7) System Shutdown on return from your command handler
   klogv("Starting system shutdown procedure...");

   /* Shutdown Procedure */
   klogv("Shutdown complete. You may now turn off the machine. (QEMU: C-a x)");
   hlt();
}
