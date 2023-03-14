
#include <iostream>
#include <iomanip>

#include "std_types.h"

/* After a series of implementations, utilizing primarily 'std::map', a custom implementation
        proved to be much more efficient. */

uint32_t registerBank[32];

class EasyAccess {
    uint32_t *rBank;

public:
    EasyAccess(uint32_t *rBank) : rBank(rBank) {}

    uint32_t & command(uint8_t c, uint8_t i) {
        return rBank[((c - 'A') * 8 + i)];
    }

    uint8_t & control(uint8_t c) {
        return (uint8_t &) rBank[((c - 'A') * 8 + 4)];
    }

    uint8_t & status(uint8_t c) {
        return (uint8_t &) rBank[((c - 'A') * 8 + 5)];
    }

    uint16_t & option(uint8_t c, uint8_t i) {
        return (uint16_t &) rBank[((c - 'A') * 8 + i + 6)];
    }
};

int main() {
    EasyAccess easy{registerBank};
    uint32_t i = 0;

    easy.command('A', 0) = 255;
    easy.command('B', 1) = 255;
    easy.option('D', 1) = 255;

    for (i = 0; i < 32; i++) {
        std::cout << '[' << std::setfill('0') << std::setw(2) << i << "]: " << registerBank[i] << '\n';
    }
}