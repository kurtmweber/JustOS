
//*****************************************************************
// This file is part of CosmOS                                    *
// Copyright (C) 2020 Tom Everett                                 *
// Released under the stated terms in the file LICENSE            *
// See the file "LICENSE" in the source distribution for details  *
// ****************************************************************

#include <dev/dev.h>

/*
* Note that devices are initialized in the order they are registered.
*/
void dev_devicemgr_register_devices(){
	/*
	* scan the PCI bus first
	*/
	pci_init();
	/*
	* set up the pic next
	*/
	pic_devicemgr_register_devices();
	/* 
	* and then RS232
	*/
	serial_devicemgr_register_devices();
	/*
	* and the then the PIT
	*/
	pit_devicemgr_register_devices();
	/*
	* rest of this stuff can really happen in any order
	*/
	rtc_devicemgr_register_devices();
	keyboard_devicemgr_register_devices();
	display_devicemgr_register_devices();
	usb_devicemgr_register_devices();
	network_devicemgr_register_devices();
	bridge_devicemgr_register_devices();
	ata_devicemgr_register_devices(); 
    mouse_devicemgr_register_devices();
    floppy_devicemgr_register_devices();
    speaker_devicemgr_register_devices();
	sb16_devicemgr_register_devices();
	ac97_devicemgr_register_devices();
}
