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

#include "byte_buffer.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

static bool meg_endianness_is_valid(MegEndianness endianness) {
    return endianness == MEG_LITTLE_ENDIAN || endianness == MEG_BIG_ENDIAN;
}

static bool meg_checked_add_size(size_t left, size_t right, size_t *result) {
    if (result == NULL || right > SIZE_MAX - left) {
        return false;
    }
    *result = left + right;
    return true;
}

/**
 * Initialize a MegByteBuffer.
 *
 * @param buffer The buffer to initialize.
 * @param endianness The byte order to use for multi-byte values.
 * @return true if the buffer was initialized, false if an argument was invalid.
 */
bool meg_bytes_init(MegByteBuffer *buffer, MegEndianness endianness) {
    if (buffer == NULL || !meg_endianness_is_valid(endianness)) {
        return false;
    }
    *buffer = (MegByteBuffer){0};
    buffer->endianness = endianness;
    return true;
}

/**
 * Destroy a MegByteBuffer, freeing its internal data.
 *
 * @param buffer The buffer to destroy.
 */
void meg_bytes_destroy(MegByteBuffer *buffer) {
    if (buffer == NULL) {
        return;
    }
    free(buffer->data);
    *buffer = (MegByteBuffer){0};
}

/**
 * Ensure that a MegByteBuffer has enough capacity to accommodate additional data.
 *
 * @param buffer The buffer to check and potentially expand.
 * @param extra The additional number of bytes needed.
 * @return true if the buffer has enough capacity or was successfully expanded, false otherwise.
 */
bool meg_bytes_reserve(MegByteBuffer *buffer, size_t extra) {
    size_t needed, capacity;
    if (buffer == NULL || !meg_endianness_is_valid(buffer->endianness) ||
        buffer->length > buffer->capacity ||
        (buffer->capacity != 0 && buffer->data == NULL)) {
        return false;
    }
    if (!meg_checked_add_size(buffer->length, extra, &needed)) {
        return false;
    }
    capacity = buffer->capacity;
    if (needed > capacity) {
        size_t new_capacity = capacity ? capacity : 1;
        while (new_capacity < needed) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = needed;
                break;
            }
            new_capacity *= 2;
        }
        void *new_data = realloc(buffer->data, new_capacity);
        if (!new_data) {
            return false;
        }
        buffer->data = new_data;
        buffer->capacity = new_capacity;
    }
    return true;
}

/**
 * Append a single byte to a MegByteBuffer.
 *
 * @param buffer The buffer to append to.
 * @param value The byte value to append.
 * @return true if the byte was successfully appended, false otherwise.
 */
bool meg_bytes_u8(MegByteBuffer *buffer, uint8_t value) {
    if (!meg_bytes_reserve(buffer, 1)) {
        return false;
    }
    buffer->data[buffer->length] = value;
    buffer->length += 1;
    return true;
}

/**
 * Append a 16-bit unsigned integer to a MegByteBuffer, respecting its endianness.
 *
 * @param buffer The buffer to append to.
 * @param value The 16-bit unsigned integer value to append.
 * @return true if the value was successfully appended, false otherwise.
 */
bool meg_bytes_u16(MegByteBuffer *buffer, uint16_t value) {
    if (!meg_bytes_reserve(buffer, 2)) {
        return false;
    }
    if (buffer->endianness == MEG_LITTLE_ENDIAN) {
        buffer->data[buffer->length] = value & 0xFF;
        buffer->data[buffer->length + 1] = (value >> 8) & 0xFF;
    } else {
        buffer->data[buffer->length] = (value >> 8) & 0xFF;
        buffer->data[buffer->length + 1] = value & 0xFF;
    }
    buffer->length += 2;
    return true;
}
/**
 * Append a 32-bit unsigned integer to a MegByteBuffer, respecting its endianness.
 *
 * @param buffer The buffer to append to.
 * @param value The 32-bit unsigned integer value to append.
 * @return true if the value was successfully appended, false otherwise.
 */
bool meg_bytes_u32(MegByteBuffer *buffer, uint32_t value) {
    if (!meg_bytes_reserve(buffer, 4)) {
        return false;
    }
    if (buffer->endianness == MEG_LITTLE_ENDIAN) {
        buffer->data[buffer->length] = value & 0xFF;
        buffer->data[buffer->length + 1] = (value >> 8) & 0xFF;
        buffer->data[buffer->length + 2] = (value >> 16) & 0xFF;
        buffer->data[buffer->length + 3] = (value >> 24) & 0xFF;
    } else {
        buffer->data[buffer->length] = (value >> 24) & 0xFF;
        buffer->data[buffer->length + 1] = (value >> 16) & 0xFF;
        buffer->data[buffer->length + 2] = (value >> 8) & 0xFF;
        buffer->data[buffer->length + 3] = value & 0xFF;
    }
    buffer->length += 4;
    return true;
}

/**
 * Append a 64-bit unsigned integer to a MegByteBuffer, respecting its endianness.
 *
 * @param buffer The buffer to append to.
 * @param value The 64-bit unsigned integer value to append.
 * @return true if the value was successfully appended, false otherwise.
 */
bool meg_bytes_u64(MegByteBuffer *buffer, uint64_t value) {
    if (!meg_bytes_reserve(buffer, 8)) {
        return false;
    }
    if (buffer->endianness == MEG_LITTLE_ENDIAN) {
        buffer->data[buffer->length] = value & 0xFF;
        buffer->data[buffer->length + 1] = (value >> 8) & 0xFF;
        buffer->data[buffer->length + 2] = (value >> 16) & 0xFF;
        buffer->data[buffer->length + 3] = (value >> 24) & 0xFF;
        buffer->data[buffer->length + 4] = (value >> 32) & 0xFF;
        buffer->data[buffer->length + 5] = (value >> 40) & 0xFF;
        buffer->data[buffer->length + 6] = (value >> 48) & 0xFF;
        buffer->data[buffer->length + 7] = (value >> 56) & 0xFF;
    } else {
        buffer->data[buffer->length] = (value >> 56) & 0xFF;
        buffer->data[buffer->length + 1] = (value >> 48) & 0xFF;
        buffer->data[buffer->length + 2] = (value >> 40) & 0xFF;
        buffer->data[buffer->length + 3] = (value >> 32) & 0xFF;
        buffer->data[buffer->length + 4] = (value >> 24) & 0xFF;
        buffer->data[buffer->length + 5] = (value >> 16) & 0xFF;
        buffer->data[buffer->length + 6] = (value >> 8) & 0xFF;
        buffer->data[buffer->length + 7] = value & 0xFF;
    }
    buffer->length += 8;
    return true;
}

/**
 * Patch a 16-bit unsigned integer at a specific offset in a MegByteBuffer, respecting its endianness.
 *
 * @param buffer The buffer to patch.
 * @param offset The offset at which to patch the value.
 * @param value The 16-bit unsigned integer value to patch.
 * @return true if the value was successfully patched, false otherwise.
 */
bool meg_bytes_patch_u16(MegByteBuffer *buffer, size_t offset, uint16_t value) {
    if (buffer == NULL || !meg_endianness_is_valid(buffer->endianness) ||
        buffer->data == NULL || buffer->length < 2 ||
        offset > buffer->length - 2) {
        return false;
    }
    if (buffer->endianness == MEG_LITTLE_ENDIAN) {
        buffer->data[offset] = value & 0xFF;
        buffer->data[offset + 1] = (value >> 8) & 0xFF;
    } else {
        buffer->data[offset] = (value >> 8) & 0xFF;
        buffer->data[offset + 1] = value & 0xFF;
    }
    return true;
}

/**
 * Patch a 32-bit unsigned integer at a specific offset in a MegByteBuffer, respecting its endianness.
 *
 * @param buffer The buffer to patch.
 * @param offset The offset at which to patch the value.
 * @param value The 32-bit unsigned integer value to patch.
 * @return true if the value was successfully patched, false otherwise.
 */
bool meg_bytes_patch_u32(MegByteBuffer *buffer, size_t offset, uint32_t value) {
    if (buffer == NULL || !meg_endianness_is_valid(buffer->endianness) ||
        buffer->data == NULL || buffer->length < 4 ||
        offset > buffer->length - 4) {
        return false;
    }
    if (buffer->endianness == MEG_LITTLE_ENDIAN) {
        buffer->data[offset] = value & 0xFF;
        buffer->data[offset + 1] = (value >> 8) & 0xFF;
        buffer->data[offset + 2] = (value >> 16) & 0xFF;
        buffer->data[offset + 3] = (value >> 24) & 0xFF;
    } else {
        buffer->data[offset] = (value >> 24) & 0xFF;
        buffer->data[offset + 1] = (value >> 16) & 0xFF;
        buffer->data[offset + 2] = (value >> 8) & 0xFF;
        buffer->data[offset + 3] = value & 0xFF;
    }
    return true;
}

/**
 * Patch a 64-bit unsigned integer at a specific offset in a MegByteBuffer, respecting its endianness.
 *
 * @param buffer The buffer to patch.
 * @param offset The offset at which to patch the value.
 * @param value The 64-bit unsigned integer value to patch.
 * @return true if the value was successfully patched, false otherwise.
 */
bool meg_bytes_patch_u64(MegByteBuffer *buffer, size_t offset, uint64_t value) {
    if (buffer == NULL || !meg_endianness_is_valid(buffer->endianness) ||
        buffer->data == NULL || buffer->length < 8 ||
        offset > buffer->length - 8) {
        return false;
    }
    if (buffer->endianness == MEG_LITTLE_ENDIAN) {
        buffer->data[offset] = value & 0xFF;
        buffer->data[offset + 1] = (value >> 8) & 0xFF;
        buffer->data[offset + 2] = (value >> 16) & 0xFF;
        buffer->data[offset + 3] = (value >> 24) & 0xFF;
        buffer->data[offset + 4] = (value >> 32) & 0xFF;
        buffer->data[offset + 5] = (value >> 40) & 0xFF;
        buffer->data[offset + 6] = (value >> 48) & 0xFF;
        buffer->data[offset + 7] = (value >> 56) & 0xFF;
    } else {
        buffer->data[offset] = (value >> 56) & 0xFF;
        buffer->data[offset + 1] = (value >> 48) & 0xFF;
        buffer->data[offset + 2] = (value >> 40) & 0xFF;
        buffer->data[offset + 3] = (value >> 32) & 0xFF;
        buffer->data[offset + 4] = (value >> 24) & 0xFF;
        buffer->data[offset + 5] = (value >> 16) & 0xFF;
        buffer->data[offset + 6] = (value >> 8) & 0xFF;
        buffer->data[offset + 7] = value & 0xFF;
    }
    return true;
}

bool meg_bytes_append(MegByteBuffer *buffer, const uint8_t *data, size_t length) {
    if (buffer == NULL) {
        return false;
    }
    if (length == 0) {
        return meg_bytes_reserve(buffer, 0);
    }
    if (data == NULL) {
        return false;
    }
    if (!meg_bytes_reserve(buffer, length)) {
        return false;
    }
    memcpy(buffer->data + buffer->length, data, length);
    buffer->length += length;
    return true;
}
