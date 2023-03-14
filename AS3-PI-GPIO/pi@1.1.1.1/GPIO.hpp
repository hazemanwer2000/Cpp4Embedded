
#ifndef __GPIO__
#define __GPIO__

#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <iostream>
#include <unistd.h>

#include "Std_Types.hpp"
#include "Bit_Utils.hpp"

#define GPIO_BASE               0x3F200000
#define BLOCK_SIZE              4096u                

#define GPIO_SET0_OFFSET        0x7
#define GPIO_CLR0_OFFSET        0xA
#define GPIO_LVL0_OFFSET        0xD

class GPIO {
    uint32_t *base;

public:
    enum PinType {
        Input = 0,
        Output = 1
    };

    enum PinNumber {
        Pin0 = 0,
        Pin1,
        Pin2,
        Pin3,
        Pin4,
        Pin5,
        Pin6,
        Pin7,
        Pin8,
        Pin9,

        Pin10,
        Pin11,
        Pin12,
        Pin13,
        Pin14,
        Pin15,
        Pin16,
        Pin17,
        Pin18,
        Pin19,
        
        Pin20,
        Pin21,
        Pin22,
        Pin23,
        Pin24,
        Pin25,
        Pin26,
        Pin27
    };

    enum PinState {
        Off = 0,
        On = 1
    };

    GPIO () {
        void *ptr;

        // Open /dev/mem
        int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
        if (mem_fd < 0) {
            std::cerr << "Failed to open /dev/mem\n";
            exit(-1);
        }

        // Map the register into memory
        ptr = mmap(nullptr, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);
        if (ptr == MAP_FAILED) {
            std::cerr << "Failed to map register: " <<  std::hex << GPIO_BASE << std::dec << std::endl;
            perror("mmap failed"); 
            std::cerr << "errno = " << errno << std::endl;
            exit(-1);
        }

        // Close /dev/mem
        close(mem_fd);
    
        base = reinterpret_cast<uint32_t *>(ptr);
    }

    void configure(PinNumber pinNumber, PinType pinType) {
        uint32_t *ptr = base + pinNumber / 10;

        std::cout << "Configuring...\n";
        *ptr = REPLACE_BIT(*ptr, 3 * (pinNumber % 10), pinType);
    }

    void set(PinNumber pinNumber) {
        std::cout << "Setting...\n";
        *(base + GPIO_SET0_OFFSET) = (1 << pinNumber);
    }

    void clear(PinNumber pinNumber) {
        std::cout << "Clearing...\n";
        *(base + GPIO_CLR0_OFFSET) = (1 << pinNumber);
    }

    PinState get(PinNumber pinNumber) {
        std::cout << "Getting...\n";
        return static_cast<PinState>(GET_BIT(*(base + GPIO_LVL0_OFFSET), pinNumber));
    }

    ~GPIO() {
        munmap(reinterpret_cast<void *>(base), BLOCK_SIZE);
    }
};

#endif /* __GPIO__ */