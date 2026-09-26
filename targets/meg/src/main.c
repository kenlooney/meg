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

#include "meg/byte_buffer.h"

#include <stdio.h>
#include <string.h>

void print_help() {
  puts("");
  puts("Options:");
  puts("  -h, --help    display this help and exit");
  puts("  -e, --endianess    set the byte order (little or big)");
}

MegEndianness endianness;
int main(int argc, char **argv) {
  if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
    print_help();
    return 0;
  }
  if (argc == 3 && (strcmp(argv[1], "--endianess") == 0 || strcmp(argv[1], "-e") == 0)) {
    if (strcmp(argv[2], "little") == 0) {
      // Set little endian
      endianness = MEG_LITTLE_ENDIAN;
    } else if (strcmp(argv[2], "big") == 0) {
      // Set big endian
      endianness = MEG_BIG_ENDIAN;
    } else {
      fprintf(stderr, "Invalid endianess: %s\n", argv[2]);
      return 1;
    }
  }
  return 0;
}
