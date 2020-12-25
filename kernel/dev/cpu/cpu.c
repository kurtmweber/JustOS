//*****************************************************************
// This file is part of CosmOS                                    *
// Copyright (C) 2020 Tom Everett                                 *
// Released under the stated terms in the file LICENSE            *
// See the file "LICENSE" in the source distribution for details  *
// ****************************************************************

#include <dev/cpu/cpu.h>
#include <asm/asm.h>
#include <devicemgr/devicemgr.h>
#include <console/console.h>
#include <devicemgr/deviceapi/deviceapi_cpu.h>

void cpu_manufacturer_id(uint8_t* cpuid);

/*
* perform device instance specific init here
*/
void deviceInitCPU(struct device* dev){
    kprintf("Init %s (%s)\n",dev->description, dev->name);
}

// https://prodevsblog.com/questions/441449/checking-if-cpu-supports-rdrand/
void invokeCPUID(unsigned int  function, unsigned int  subfunction, unsigned int* pEAX, unsigned int* pEBX, unsigned int* pECX, unsigned int* pEDX) {
    asm volatile("cpuid"
        :   "=a" (*pEAX),
            "=b" (*pEBX),
            "=c" (*pECX),
            "=d" (*pEDX)
        :   "a" (function),
            "c" (subfunction)
        );
}

void cpu_get_features(struct cpu_id* id) {    
    invokeCPUID(1,0, &(id->eax),&(id->ebx),&(id->ecx),&(id->edx));
}

/* 
* https://en.wikipedia.org/wiki/CPUID
*/
bool has_apic_function() {
    struct cpu_id id;
    cpu_get_features(&id);
    return ((id.edx & CPUID_FEAT_EDX_APIC)>0);
}

void cpu_manufacturer_id(uint8_t* cpuid) {
    struct cpu_id id;
    invokeCPUID(0,0, &(id.eax),&(id.ebx),&(id.ecx),&(id.edx));

    cpuid[3]= (id.ebx & 0xFF000000)>>24;
    cpuid[2]= (id.ebx & 0x00FF0000)>>16;
    cpuid[1]= (id.ebx & 0x0000FF00)>>8;
    cpuid[0]= (id.ebx & 0x000000FF)>>0;
    cpuid[7]= (id.edx & 0xFF000000)>>24;
    cpuid[6]= (id.edx & 0x00FF0000)>>16;
    cpuid[5]= (id.edx & 0x0000FF00)>>8;
    cpuid[4]= (id.edx & 0x000000FF)>>0;
    cpuid[11]= (id.ecx & 0xFF000000)>>24;
    cpuid[10]= (id.ecx & 0x00FF0000)>>16;
    cpuid[9]=  (id.ecx & 0x0000FF00)>>8;
    cpuid[8]=  (id.ecx & 0x000000FF)>>0;
    cpuid[12]= 0;
}

void cpu_devicemgr_register_devices(){
    /*
	* register device
	*/
	struct device* deviceinstance = devicemgr_new_device();
	devicemgr_set_device_description(deviceinstance, "CPU");
	deviceinstance->devicetype = CPU;
	deviceinstance->init =  &deviceInitCPU;
	/*
	* device api
	*/
	struct deviceapi_cpu* api = (struct deviceapi_cpu*) kmalloc (sizeof(struct deviceapi_cpu));
	api->features = &cpu_get_features;
    api->apic = &has_apic_function;
    api->manufacturer = &cpu_manufacturer_id;
	deviceinstance->api = api;
    /*
    * register
    */ 
	devicemgr_register_device(deviceinstance);
}