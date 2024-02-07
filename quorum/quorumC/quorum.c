#include "quorum.h"

const char *index_to_string(uint64_t i) {
    static char buffer[21]; // buffer size for uint64_t
    if (i == UINT64_MAX) {
        return "∞";
    }
    snprintf(buffer, sizeof(buffer), "%" PRIu64, (uint64_t)i);
    return buffer;
}