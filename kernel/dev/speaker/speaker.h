//*****************************************************************
// This file is part of CosmOS                                    *
// Copyright (C) 2020 Tom Everett                                 *
// Released under the stated terms in the file LICENSE            *
// See the file "LICENSE" in the source distribution for details  *
// ****************************************************************

#ifndef _SPEAKER_H
#define _SPEAKER_H

#include <types.h>

void speaker_register_devices();
void speaker_beep(uint32_t frequency, uint32_t milliseconds);
#endif