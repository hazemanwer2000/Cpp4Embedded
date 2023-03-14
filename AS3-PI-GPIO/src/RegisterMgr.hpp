#ifndef REGISTERMGR_HPP
#define REGISTERMGR_HPP

#include <memory>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include "Register.hpp"

// Define the RegisterManager class
class RegisterManager
{
    public:
    // Define the RegisterManager constructor
    RegisterManager()
    {
        // Open /dev/mem
        int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
        if (mem_fd < 0)
        {
            std::cerr << "Failed to open /dev/mem\n";
            exit(-1);
        }

        // Map the register into memory
        reg_map = mmap(nullptr, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);
        if (reg_map == MAP_FAILED)
        {
            std::cerr << "Failed to map register: " <<  std::hex << GPIO_BASE << std::dec << std::endl;
            perror("mmap failed"); 
            std::cerr << "errno = " << errno << std::endl;
            exit(-1);
        }

        // Close /dev/mem
        close(mem_fd);

        std::cout << "Mapped GPIO base register at " <<  std::hex << reg_map << std::dec << std::endl;

        gpio_reg_map = reinterpret_cast<uint32_t*>(reg_map);
        
        std::cout << "reinterpret_cast GPIO base register at " <<  std::hex << gpio_reg_map << std::dec << std::endl;

        // Create and add the GPFSEL0 register
        registers["GPFSEL0"] = std::unique_ptr<Register>(new Register(gpio_reg_map, GPFSEL0_OFFSET));

        // Create and add the GPFSEL1 register
        registers["GPFSEL1"] = std::unique_ptr<Register>(new Register(gpio_reg_map, GPFSEL1_OFFSET));

        // Create and add the GPSET0 register
        registers["GPSET0"] = std::unique_ptr<Register>(new Register(gpio_reg_map, GPSET0_OFFSET));

        // Create and add the GPSET1 register
        registers["GPSET1"] = std::unique_ptr<Register>(new Register(gpio_reg_map, GPSET1_OFFSET));

        // Create and add the GPCLR0 register
        registers["GPCLR0"] = std::unique_ptr<Register>(new Register(gpio_reg_map, GPCLR0_OFFSET));

        // Create and add the GPCLR1 register
        registers["GPCLR1"] = std::unique_ptr<Register>(new Register(gpio_reg_map, GPCLR1_OFFSET));
    }

    ~RegisterManager()
    {
        // Clear the map of registers
        registers.clear();

        // Unmap the register from memory
        munmap(reg_map, BLOCK_SIZE);
    }

    // Read a register value by name
    uint32_t read(std::string name)
    {
        // Check if the register name exists in the map
        if (registers.find(name) != registers.end())
        {
            // Return the register value by calling the read function of the Register class
            return registers[name]->read();
        }
        else
        {
            // Return 0 if the register name does not exist
            return 0;
        }
    }

    // Write a register value by name
    void write(std::string name, uint32_t value)
    {
        // Check if the register name exists in the map
        if (registers.find(name) != registers.end())
        {
            std::cout << "Writing register " << name << std::endl;
            
            // Write the register value by calling the write function of the Register class
            registers[name]->write(value);
        }
    }

private:
    static constexpr uint32_t GPIO_BASE = 0x3F200000;
    static constexpr uint32_t GPFSEL0_OFFSET = 0x00;
    static constexpr uint32_t GPFSEL1_OFFSET = 0x01;
    static constexpr uint32_t GPSET0_OFFSET = 0x7;
    static constexpr uint32_t GPSET1_OFFSET = 0x8;
    static constexpr uint32_t GPCLR0_OFFSET = 0xA;
    static constexpr uint32_t GPCLR1_OFFSET = 0xB;

    // A pointer to the mapped memory block
    void* reg_map;
    uint32_t* gpio_reg_map;

    // Define the register size
    static constexpr unsigned long BLOCK_SIZE = (4*1024);

    // A map of register names and pointers
    std::unordered_map<std::string, std::unique_ptr<Register>> registers;
};

#endif