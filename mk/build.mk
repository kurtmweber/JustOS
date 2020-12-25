#*****************************************************************
# This file is part of CosmOS                                    *
# Copyright (C) 2020 Tom Everett                                 *
# Released under the stated terms in the file LICENSE            *
# See the file "LICENSE" in the source distribution for details  *
# ****************************************************************

NASM=nasm
NASMARGS=-O0
RM=rm -f
MAKE=make
DD=dd
MAPFILE=cosmos.map
LINKER_SCRIPT=cosmos.ld

SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

# detect build platform
UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
include $(SELF_DIR)/gcc-darwin.mk

# not quite yet
#include $(SELF_DIR)/clang-darwin.mk
else
include $(SELF_DIR)/gcc-linux.mk
endif

# qemu
QEMU=qemu-system-x86_64
QEMUARGS=                                                 \
  -accel tcg,thread=single                                \
  -cpu core2duo                                           \
  -m 1024                                                 \
  -no-reboot                                              \
  -drive format=raw,file=hda.img                          \
  -smp 1                                                  \
  -nic user,ipv6=off,model=ne2k_isa,mac=52:54:98:76:54:32 \
  -serial stdio                                           \
  -machine pcspk-audiodev=audio0                          \
  -audiodev coreaudio,id=audio0                           \
  -monitor telnet::45454,server,nowait                    \
  -device floppy,drive=f0                                 \
  -blockdev driver=file,node-name=f0,filename=hda.img     \
  -device usb-ehci                                        \
  -device sb16,audiodev=audio0                            \
  -nic user,model=virtio-net-pci                          \
  -drive if=virtio,file=hda.img,format=raw
  
# note that we're mounting the hda.img as a floppy image. good enough for now.
# the first bytes are FA B4 00 B0 03 CD 10 88 16 7C 7C B8 01 24 CD 15

# to list devices:
# qemu-system-x86_64 -device ?

# -device AC97,audiodev=audio0
# -device adlib,audiodev=audio0

