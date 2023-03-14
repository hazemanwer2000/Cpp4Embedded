#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <iostream>
#include <unordered_map>

// Define a class to represent a memory-mapped register
class Register
{
public:
    // Constructor
    Register(uint32_t * base_address, uint32_t offset)
    {
        // Get a pointer to the register
        reg = (base_address + offset);

        std::cout << std::hex << "base_address: " << base_address << " offset:" << offset << " Mapped register at " << reg << std::dec << std::endl;
    }

    // Get the value of the register
    uint32_t read()
    {
        return *reg;
    }

    // Set the value of the register
    void write(uint32_t value)
    {
        std::cout << std::hex << "Writing " << value << " into " << reg << std::endl;
        *reg = value;
    }

private:
    // A pointer to the register
    uint32_t *reg;
};

#endif