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
#ifndef MEG_BYTE_BUFFER_H
#define MEG_BYTE_BUFFER_H

#include "meg/common.h"

typedef enum MegEndianness {
    MEG_LITTLE_ENDIAN,
    MEG_BIG_ENDIAN
} MegEndianness;

typedef struct MegByteBuffer {
    uint8_t *data;
    size_t length;
    size_t capacity;
    MegEndianness endianness;
} MegByteBuffer;

bool meg_bytes_init(MegByteBuffer *buffer, MegEndianness endianness);
void meg_bytes_destroy(MegByteBuffer *buffer);
bool meg_bytes_reserve(MegByteBuffer *buffer, size_t extra);
bool meg_bytes_u8(MegByteBuffer *buffer, uint8_t value);
bool meg_bytes_u16(MegByteBuffer *buffer, uint16_t value);
bool meg_bytes_u32(MegByteBuffer *buffer, uint32_t value);
bool meg_bytes_u64(MegByteBuffer *buffer, uint64_t value);
bool meg_bytes_patch_u16(MegByteBuffer *buffer, size_t offset, uint16_t value);
bool meg_bytes_patch_u32(MegByteBuffer *buffer, size_t offset, uint32_t value);
bool meg_bytes_patch_u64(MegByteBuffer *buffer, size_t offset, uint64_t value);
/* data must not point into buffer->data. */
bool meg_bytes_append(MegByteBuffer *buffer, const uint8_t *data, size_t length);
#endif // MEG_BYTE_BUFFER_H
