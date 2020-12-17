//*****************************************************************
// This file is part of CosmOS                                    *
// Copyright (C) 2020 Tom Everett                                 *
// Released under the stated terms in the file LICENSE            *
// See the file "LICENSE" in the source distribution for details  *
// ****************************************************************

#include <display/display.h>
#include <interrupts/interrupt_router.h>
#include <asm/asm.h>
#include <pci/pci.h>
#include <console/console.h>
#include <devicemgr/devicemgr.h>

/*
* perform device instance specific init here
*/
void deviceInitDisplay(struct device* dev){
    struct pci_device* pci_dev = (struct pci_device*) dev->deviceData;
    kprintf("Init %s at IRQ %llu\n",dev->description, pci_dev->irq);
}


void DisplaySearchCB(struct pci_device* dev){
    /*
    * register device
    */
    struct device* deviceinstance = newDevice();
    deviceinstance->init =  &deviceInitDisplay;
    deviceinstance->deviceData = dev;
    deviceSetDescription(deviceinstance, "VGA Display");
    registerDevice(deviceinstance);
}

/**
* find all Display devices and register them
*/
void display_register_devices() {
    pci_search_devicetype(PCI_CLASS_DISPLAY,PCI_DISPLAY_SUBCLASS_VGA, &DisplaySearchCB);
}
