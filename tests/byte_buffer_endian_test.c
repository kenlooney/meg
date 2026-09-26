/*
 * Copyright (C) 2026 Kenneth Looney
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "byte_buffer.h"

#include <stdio.h>
#include <string.h>

static int verify_bytes(const MegByteBuffer *buffer,
                        const uint8_t *expected,
                        size_t expected_length,
                        const char *stage) {
    if (buffer->length != expected_length) {
        fprintf(stderr, "%s length: expected %zu, got %zu\n",
                stage, expected_length, buffer->length);
        return 1;
    }
    if (memcmp(buffer->data, expected, expected_length) != 0) {
        fprintf(stderr, "%s bytes do not match expected byte order\n", stage);
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    static const uint8_t little_written[] = {
        0xAA, 0x22, 0x11, 0x66, 0x55, 0x44, 0x33,
        0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77
    };
    static const uint8_t big_written[] = {
        0xAA, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
        0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE
    };
    static const uint8_t little_patched[] = {
        0xAA, 0xB2, 0xA1, 0xF6, 0xE5, 0xD4, 0xC3,
        0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01
    };
    static const uint8_t big_patched[] = {
        0xAA, 0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6,
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
    };
    MegEndianness endianness;
    const uint8_t *written;
    const uint8_t *patched;
    MegByteBuffer buffer;
    int result = 1;

    if (argc != 2) {
        fprintf(stderr, "usage: %s little|big\n", argv[0]);
        return 2;
    }
    if (strcmp(argv[1], "little") == 0) {
        endianness = MEG_LITTLE_ENDIAN;
        written = little_written;
        patched = little_patched;
    } else if (strcmp(argv[1], "big") == 0) {
        endianness = MEG_BIG_ENDIAN;
        written = big_written;
        patched = big_patched;
    } else {
        fprintf(stderr, "unknown byte order: %s\n", argv[1]);
        return 2;
    }

    if (!meg_bytes_init(&buffer, endianness)) {
        fputs("failed to initialize byte buffer\n", stderr);
        return 1;
    }
    if (!meg_bytes_u8(&buffer, UINT8_C(0xAA)) ||
        !meg_bytes_u16(&buffer, UINT16_C(0x1122)) ||
        !meg_bytes_u32(&buffer, UINT32_C(0x33445566)) ||
        !meg_bytes_u64(&buffer, UINT64_C(0x778899AABBCCDDEE))) {
        fputs("failed to append values\n", stderr);
        goto done;
    }
    if (verify_bytes(&buffer, written, sizeof(little_written), "write") != 0) {
        goto done;
    }

    if (!meg_bytes_patch_u16(&buffer, 1, UINT16_C(0xA1B2)) ||
        !meg_bytes_patch_u32(&buffer, 3, UINT32_C(0xC3D4E5F6)) ||
        !meg_bytes_patch_u64(&buffer, 7, UINT64_C(0x0102030405060708))) {
        fputs("failed to patch values\n", stderr);
        goto done;
    }
    if (verify_bytes(&buffer, patched, sizeof(little_patched), "patch") != 0) {
        goto done;
    }

    result = 0;

done:
    meg_bytes_destroy(&buffer);
    return result;
}
