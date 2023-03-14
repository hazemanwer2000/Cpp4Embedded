
#include "GPIO.hpp"
#include <unistd.h>

int main() {
    GPIO gpio;

    try {
        GPIO gpio;
    } catch (GPIOException &e) {
        std::cout << e.msg;
    }

    gpio.configure(GPIO::Pin15, GPIO::Output);

    while (1) {
        gpio.set(GPIO::Pin15);
        sleep(1);
        gpio.clear(GPIO::Pin15);
        sleep(1);
    }

    return 0;
}