#if !defined(INT_BYTE_CASTS_H)
#define INT_BYTE_CASTS_H

#include <inttypes.h>

void emplace_uint16_to_buff(uint16_t num, char *buff);
void emplace_uint64_to_buff(uint64_t num, char *buff);
uint16_t bytes_to_uint16(const char *buff);
uint64_t bytes_to_uint64(const char *buff);

#endif // INT_BYTE_CASTS_H
