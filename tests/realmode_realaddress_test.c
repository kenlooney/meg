/*
 * Copyright (C) 2026 Kenneth Looney
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "meg/realmode/memory.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    uint16_t cs = 0x1000;
    uint16_t ip = 0x0000;
    uint16_t sp = 0x7C00;

    printf("CS:IP=%04X:%04X physical=0x%08X SP=0x%04X\n", cs, ip,
           (unsigned)real_address(cs, ip), sp);
    return real_address(cs, ip) == 0x10000u ? 0 : 1;
}