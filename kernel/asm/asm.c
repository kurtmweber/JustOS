/*****************************************************************
 * This file is part of JustOS                                   *
 * Copyright (C) 2019 Kurt M. Weber                              *
 * Released under the terms of the Social Justice License        *
 * See the file "LICENSE" in the source distribution for details *
 *****************************************************************/

#include <types.h>
#include <mm/mm.h>

void asm_hlt(){
	asm volatile(
		"hlt"
	    );
	
	return;
}

void asm_cli(){
	asm volatile(
		"cli"
	    );
	
	return;
}

void asm_sti(){
	asm volatile(
		"sti"
	    );
	
	return;
}

pttentry asm_cr3_read(){
	pttentry cr3;
	
	asm volatile(
		"mov %0, cr3"
		: "=r" (cr3)
	    );
	
	return cr3;
}