/*
 * Copyright (C) 2026 Kenneth Looney
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef MEG_COMMON_H
#define MEG_COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum MegTarget {
    MEG_TARGET_X86_16,
    MEG_TARGET_X86_32,
    MEG_TARGET_X86_64, // Not going to be implement in this version
} MegTarget;

#endif // MEG_COMMON_H