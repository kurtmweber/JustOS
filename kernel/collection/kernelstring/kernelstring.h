//*****************************************************************
// This file is part of CosmOS                                    *
// Copyright (C) 2020 Tom Everett                                 *
// Released under the stated terms in the file LICENSE            *
// See the file "LICENSE" in the source distribution for details  *
// ****************************************************************

#ifndef _KERNELSTRING_H
#define _KERNELSTRING_H

#include <types.h>

/**
 *  a simple string based on an array. The string is null terminated, but stores a length 
 */
typedef struct kernelstring {
	uint8_t* str;
    uint16_t length;
} kernelstring_t;

struct kernelstring* stringNew();
void stringDelete(struct kernelstring* str);
uint16_t stringLength(struct kernelstring* str);
#endif