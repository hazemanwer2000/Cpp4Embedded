
#include "GPIO.hpp"
#include <unistd.h>

int main() {
    GPIO gpio;

    gpio.configure(GPIO::Pin14, GPIO::Output);

    while (1) {
        gpio.set(GPIO::Pin14);
        sleep(1000);
        gpio.clear(GPIO::Pin14);
        sleep(1000);
    }

    return 0;
}

























/*

// Include the RegisterManager class
#include "RegisterMgr.hpp"
#include <unistd.h>

// Define the main function
int main()
{
    // Initialize the register manager
    auto registerMgr = new(RegisterManager);

    // Set pin 8 to output mode -> GPIO14
    registerMgr->write("GPFSEL1", (1 << 12));

    // Loop forever
    while (true)
    {
        // Set pin 8 to high
        registerMgr->write("GPSET0", (1 << 14));
        std::cout << "LED is on\n";

        // Wait for 1 second
        sleep(1);

        // Set pin 8 to low
        registerMgr->write("GPCLR0", (1 << 14));
        std::cout << "LED is off\n";

        // Wait for 1 second
        sleep(1);
    }

    // Return 0 to indicate success
    return 0;
}


*/