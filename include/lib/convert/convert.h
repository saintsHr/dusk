#ifndef DUSK_LIB_CONVERT_CONVERT_H
#define DUSK_LIB_CONVERT_CONVERT_H

#include "lib/std/stdint.h"
#include "lib/std/stdbool.h"

bool convert_str_to_unsigned(const char* str, usize_t* out, uint32_t base);
bool convert_str_to_signed(const char* str, isize_t* out, uint32_t base);

bool convert_unsigned_to_str(usize_t num, char* buf, usize_t buf_size, uint32_t base);
bool convert_signed_to_str(isize_t num, char* buf, usize_t buf_size, uint32_t base);

#endif
