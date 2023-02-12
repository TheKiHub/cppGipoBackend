#include "pwm.hpp"
#include<unistd.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    pwm p(5);
    p.setValue(10);
    usleep(20 * 1000000);
    return 0;
}
