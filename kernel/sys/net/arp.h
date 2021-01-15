//*****************************************************************
// This file is part of CosmOS                                    *
// Copyright (C) 2021 Tom Everett                                 *
// Released under the stated terms in the file LICENSE            *
// See the file "LICENSE" in the source distribution for details  *
// ****************************************************************

// https://wiki.osdev.org/Address_Resolution_Protocol

#ifndef _ARP_H
#define _ARP_H

#include <types.h>

#define ARP_HLEN 6
#define ARP_PLEN 4
#define ARP_ETHERNET 0x01
#define ARP_IP 0x0800
#define ARP_REQUEST 0x0001
#define ARP_REPLY 0x0002

struct arp {
    uint16_t htype = ARP_ETHERNET;  // Hardware type
    uint16_t ptype = ARP_IP;        // Protocol type
    uint8_t hlen = ARP_HLEN;        // Hardware address length (Ethernet = 6)
    uint8_t plen = ARP_PLEN;        // Protocol address length (IPv4 = 4)
    uint16_t opcode;                // ARP Operation Code
    uint8_t srchw[ARP_HLEN];        // Source hardware address - hlen bytes (see above)
    uint8_t srcpr[ARP_PLEN];        // Source protocol address - plen bytes (see above). If IPv4 can just be a "u32" type.
    uint8_t dsthw[ARP_HLEN];        // Destination hardware address - hlen bytes (see above)
    uint8_t dstpr[ARP_PLEN];        // Destination protocol address - plen bytes (see above). If IPv4 can just be a "u32" type.
};

#endif