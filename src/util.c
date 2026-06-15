#include "util.h"

#include <string.h>

#define UTF8_MULTIBYTE_BIT    BIT(7)
#define STATUS2D_COLOR_LENGTH 10  // ^c#rrggbb^
#define STATUS2D_RESET_LENGTH 3   // ^d^

unsigned int gcd(unsigned int a, unsigned int b) {
    while (b > 0) {
        const unsigned int temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}

size_t truncate_utf8_string(char* const buffer, const size_t size,
                            const size_t char_limit) {
    size_t char_count = 0;
    size_t i = 0;
    while (char_count < char_limit) {
        char ch = buffer[i];
        if (ch == '\0') {
            break;
        }

        unsigned short skip = 1;
        unsigned short printable = 1;

        // Multibyte unicode character.
        if ((ch & UTF8_MULTIBYTE_BIT) != 0) {
            // Skip continuation bytes.
            ch <<= 1;
            while ((ch & UTF8_MULTIBYTE_BIT) != 0) {
                ch <<= 1;
                ++skip;
            }
        }

        // Skip status2d control sequences
        if (ch == '^') {
            if (strncmp(buffer + i, "^d^", 3) == 0) {
                skip = STATUS2D_RESET_LENGTH;
                printable = 0;
            } else if ((strncmp(buffer + i, "^b#", 3) == 0 ||
                        strncmp(buffer + i, "^c#", 3) == 0) &&
                       buffer[i + STATUS2D_COLOR_LENGTH - 1] == '^') {
                skip = STATUS2D_COLOR_LENGTH;
                printable = 0;
            }
        }

        // Avoid buffer overflow.
        if (i + skip >= size) {
            break;
        }

        if (printable) {
            ++char_count;
        }

        i += skip;
    }

    // Copy truncated status2d control characters
    size_t ci = i;
    while (i < size && ci < size) {
        char ch = buffer[ci];
        if (ch == '^') {
            if (strncmp(buffer + ci, "^d^", 3) == 0) {
                memmove(buffer + i, buffer + ci, STATUS2D_RESET_LENGTH);
                ci += STATUS2D_RESET_LENGTH;
                i += STATUS2D_RESET_LENGTH;
            } else if ((strncmp(buffer + ci, "^b#", 3) == 0 ||
                        strncmp(buffer + ci, "^c#", 3) == 0) &&
                       buffer[ci + STATUS2D_COLOR_LENGTH - 1] == '^') {
                memmove(buffer + i, buffer + ci, STATUS2D_COLOR_LENGTH);
                ci += STATUS2D_COLOR_LENGTH;
                i += STATUS2D_COLOR_LENGTH;
            }
        } else {
            ++ci;
        }
    }

    buffer[i] = '\0';
    return i + 1;
}
