/*****************************************************************
 * This file is part of CosmOS                                   *
 * Copyright (C) 2020 Tom Everett                              *
 * Released under the stated terms in the file LICENSE           *
 * See the file "LICENSE" in the source distribution for details *
 *****************************************************************/

#include <dev/pit/pit.h>
#include <asm/asm.h>
#include <devicemgr/devicemgr.h>
#include <console/console.h>
#include <collection/list/list.h>
#include <interrupts/interrupt_router.h>

// https://wiki.osdev.org/Programmable_Interval_Timer
// http://www.osdever.net/bkerndev/Docs/pit.htm

#define PIT_IRQ           0x00

#define PIT_PORT_0        0x40
#define PIT_PORT_1        0x41
#define PIT_PORT_2        0x42
#define PIT_PORT_COMMAND  0x43

struct list* pitEvents;

uint64_t tickcount=0;;

#define PIT_HZ 1 // 10 interrupts per second

// This is the perfect place to handle context switches.  Just saying.
void pit_handle_irq(stackFrame *frame) {
  //  kprintf("@");	
  tickcount=tickcount+1;
}

/*
* perform device instance specific init here
*/
/*
* According to: https://wiki.osdev.org/Programmable_Interval_Timer
* 
* "Typically during boot the BIOS sets channel 0 with a count of 65535 
*  or 0 (which translates to 65536), which gives an output frequency of 
*  18.2065 Hz (or an IRQ every 54.9254 ms)"
*/
void deviceInitPIT(struct device* dev){
    kprintf("Init %s at IRQ %llu\n",dev->description, PIT_IRQ);
    registerInterruptHandler(PIT_IRQ, &pit_handle_irq);
}

void pit_register_devices(){
    pitEvents = listNew();

    /*
	* register device
	*/
	struct device* deviceinstance = newDevice();
	deviceSetDescription(deviceinstance, "8253/8254 PIT");
	deviceinstance->devicetype = PIT;
	deviceinstance->init =  &deviceInitPIT;
	registerDevice(deviceinstance);
}

void pit_subscribe(PITEvent pitEvent) {
	listAdd(pitEvents, pitEvent);
}

uint64_t pit_tickcount() {
    return tickcount;
}
