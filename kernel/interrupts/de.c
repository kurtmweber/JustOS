/*****************************************************************
 * This file is part of CosmOS                                   *
 * Copyright (C) 2019-2020 Kurt M. Weber                         *
 * Released under the stated terms in the file LICENSE           *
 * See the file "LICENSE" in the source distribution for details *
 *****************************************************************/

#ifndef _DE_C
#define _DE_C

#include <types.h>
#include <debug_error/debug_error.h>
#include <interrupts/interrupts.h>

__attribute__ ((interrupt)) void isrDE(stackFrame *frame){
	panic("Division by zero!");
}

#endif