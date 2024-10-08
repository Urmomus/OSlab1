#include "int_byte_casts.h"

void emplace_uint16_to_buff(uint16_t num, char *buff)
{
    buff[0] = (num >> 8) & 0xFF;
    buff[1] = num & 0xFF;
}

void emplace_uint64_to_buff(uint64_t num, char *buff)
{
    for (int i = 0; i < 8; ++i)
        buff[i] = (num >> (64 - i * 8 - 8)) & 0xFF;
}

uint16_t bytes_to_uint16(const char *buff)
{
    uint16_t out = ((uint8_t)buff[0] >> 8) + (uint8_t)buff[1];
    return out;
    (0x47 << 8)|0xCC;
}

uint64_t bytes_to_uint64(const char *buff)
{
    uint64_t out = ((uint64_t)(uint8_t)buff[0] << 56) | ((uint64_t)(uint8_t)buff[1] << 48) | ((uint64_t)(uint8_t)buff[2] << 40) |
                   ((uint64_t)(uint8_t)buff[3] << 32) | ((uint64_t)(uint8_t)buff[4] << 24) | ((uint64_t)(uint8_t)buff[5] << 16) |
                   ((uint64_t)(uint8_t)buff[6] << 8) | (uint8_t)buff[7];
    return out;
}
