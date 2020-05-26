/*****************************************************************
 * This file is part of JustOS                                   *
 * Copyright (C) 2019 Kurt M. Weber                              *
 * Released under the terms of the Social Justice License        *
 * See the file "LICENSE" in the source distribution for details *
 *****************************************************************/

#ifndef _ASM_H
#define _ASM_H

#include <types.h>
#include <mm/mm.h>

void asm_cli();
void asm_hlt();
void asm_sti();

pttentry asm_cr3_read();

#endif