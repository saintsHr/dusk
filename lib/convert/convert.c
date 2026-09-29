#include "lib/convert/convert.h"

#define CONVERT_USIZE_MAX ((usize_t)~(usize_t)0)
#define CONVERT_ISIZE_MAX ((usize_t)(CONVERT_USIZE_MAX >> 1))

static int convert_digit_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return -1;
}

static bool convert_to_str(usize_t num, bool negative, char* buf, usize_t buf_size, uint32_t base) {
    if (buf == 0 || buf_size == 0) return false;
    if (base < 2 || base > 36) return false;

    buf[0] = '\0';

    char tmp[65];
    usize_t len = 0;

    do {
        uint32_t digit = (uint32_t)(num % base);
        tmp[len++] = (char)(digit < 10 ? '0' + digit : 'A' + (digit - 10));
        num /= base;
    } while (num != 0);

    usize_t total = len + (negative ? 1 : 0) + 1;
    usize_t pos = 0;

    if (total > buf_size) return false;
    if (negative) buf[pos++] = '-';

    while (len > 0) buf[pos++] = tmp[--len];

    buf[pos] = '\0';
    return true;
}

bool convert_str_to_unsigned(const char* str, usize_t* out, uint32_t base) {
    if (str == 0 || out == 0) return false;
    if (base < 2 || base > 36) return false;
    if (*str == '\0') return false;

    usize_t result = 0;

    for (; *str != '\0'; str++) {
        int digit = convert_digit_value(*str);

        if (digit < 0 || (uint32_t)digit >= base) return false;
        if (result > (CONVERT_USIZE_MAX - (usize_t)digit) / base) return false;

        result = result * base + (usize_t)digit;
    }

    *out = result;
    return true;
}

bool convert_str_to_signed(const char* str, isize_t* out, uint32_t base) {
    if (str == 0 || out == 0) return false;

    bool negative = false;

    if (*str == '-') {
        negative = true;
        str++;
    } else if (*str == '+') {
        str++;
    }

    usize_t magnitude;
    if (!convert_str_to_unsigned(str, &magnitude, base)) return false;

    if (negative) {
        if (magnitude > CONVERT_ISIZE_MAX + 1) return false;
        *out = (isize_t)(0 - magnitude);
    } else {
        if (magnitude > CONVERT_ISIZE_MAX) return false;
        *out = (isize_t)magnitude;
    }

    return true;
}

bool convert_unsigned_to_str(usize_t num, char* buf, usize_t buf_size, uint32_t base) {
    return convert_to_str(
        num, false, buf,
        buf_size, base
    );
}

bool convert_signed_to_str(isize_t num, char* buf, usize_t buf_size, uint32_t base) {
    if (num < 0) {
        return convert_to_str(
            0 - (usize_t)num,
            true, buf, buf_size, base
        );
    }

    return convert_to_str(
        (usize_t)num, false,
        buf, buf_size, base
    );
}
