/*****************************************************************
 * This file is part of CosmOS                                   *
 * Copyright (C) 2019-2020 Kurt M. Weber                         *
 * Released under the stated terms in the file LICENSE           *
 * See the file "LICENSE" in the source distribution for details *
 *****************************************************************/

#ifndef _MM_PHYS_ALLOC_C
#define _MM_PHYS_ALLOC_C

#include <types.h>
#include <mm/mm.h>

mem_block *phys_alloc_slab(uint64_t size, uint64_t align){
    mem_block *tmp;
    void *t_base, *t_base_adj;
    uint64_t t_len;
    uint64_t mod;

    tmp = usable_phys_blocks;

    do {
        if (tmp->used){
            continue;
        }
        t_base = tmp->base;

        mod = (uint64_t)t_base % align;
        if (mod){
            t_base_adj = t_base + (align - mod);    // the next aligned address after t_base
        } else {
            t_base_adj = t_base;                    // already aligned properly, no need to adjust
        }

        // check to see if the aligned start location + requested size will fit within the current block
        // if so, split off the requested slab and return; otherwise continue
        if ((t_base_adj + size) <= (t_base + tmp->len)){
            return phys_split_block(tmp, t_base_adj, size);
        }
    } while (tmp = tmp->next);

    // unable to find a block of the needed size, return NULL
    return NULL;
}

mem_block *phys_split_block(mem_block *src, void *base, uint64_t size){
    // this function does NOT set owner or used, this should be done upstream
    mem_block *new;

    new = kmalloc(sizeof(mem_block));
    if (!new){
        return NULL;
    }

    src->len = (uint64_t)(base - src->base);
    if (src->next){
        src->next->prev = new;
        new->next = src->next;
    }
    src->next = new;
    new->prev = src;

    new->base = base;
    new->len = size;

    return new;
}

#endif