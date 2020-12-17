//*****************************************************************
// This file is part of CosmOS                                    *
// Copyright (C) 2020 Tom Everett                                 *
// Released under the stated terms in the file LICENSE            *
// See the file "LICENSE" in the source distribution for details  *
// ****************************************************************

#include <devicemgr/devicemgr.h>
#include <console/console.h>
#include <collection/list/list.h>
#include <mm/mm.h>
#include <string/string.h>
#include <panic/panic.h>

struct list* devices;

void device_registry_init() {
    devices = listNew();    
}

void registerDevice(struct device* dev) {
    if (0==dev){
        panic("Attempt to register null device\n");
    }
    if (0==dev->description){
        panic("Attempt to register device without description\n");
    }
    if (0==dev->devicetype){
        kprintf(dev->description);
        panic("Attempt to register device without deviceType\n");
    }
    if (0==dev->init){
        kprintf(dev->description);
        panic("Attempt to register device without init function\n");
    }
    listAdd(devices, dev);
}

uint16_t deviceCount() {
    return listCount(devices);
}

struct device* getDevice(uint16_t idx){
    if ((idx>0) && (idx<listCount(devices))) {
        return listGet(devices, idx);
    } else {
        panic("invalid device index passed to getDevice\n");
    }
}

void initDevices(){
    kprintf("Initializing Devices\n");
    for (uint16_t i=0; i<listCount(devices);i++){
        struct device* dev = (struct device*) listGet(devices, i);
        if (0!=dev){
            dev->init(dev);
        } else {
            panic("um. why is there a null device?");
        }
    }
}

struct device* newDevice() {
    struct device* ret= (struct device*) kmalloc(sizeof(struct device));
    ret->description=0;
    ret->init=0;
    ret->deviceData=0;
    ret->name=0;
    return ret;
}

void deviceSetDescription(struct device* dev, int8_t* description) {
    if ((0!=description) && (0!=dev)){
        uint32_t size = strlen(description);
        if (0!=dev->description){
            kfree(dev->description);
        }
        dev->description = kmalloc(size+1);
        strcpy(dev->description, description);
    } else {
        panic("Invalid device or description passed to deviceSetDescription\n");
    }
}

/*
* search for devices by type
*/
void search_device(enum deviceType devicetype, deviceSearchCallback cb) {
    if (0!=cb){
        for (uint16_t i=0; i<listCount(devices);i++){
            struct device* dev = (struct device*) listGet(devices, i);
            if (0!=dev){
                if (dev->devicetype == devicetype){
                    (*cb)(dev);
                }
            } else {
                panic("um. why is there a null device?\n");
            }
        }
    } else {
        panic("Invalid function pointer passed to deviceSetDescription\n");
    }
}
