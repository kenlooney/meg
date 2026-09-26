#include "meg/realmode/memory.h"

uint32_t real_address(uint16_t segment, uint16_t offset) {
    return ((uint32_t)segment << 4) + offset;
}