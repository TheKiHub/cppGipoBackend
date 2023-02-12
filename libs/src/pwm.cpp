//
// Created by kim on 8/24/21.
//

#include "pwm.hpp"

#if MRAA
pwm::pwm(int pin) : m_pwm{pin}{
    LOG_DEBUG(logger, "initialized pwm on pin {}", pin);
    m_pwm.enable(true);
}

void pwm::setValue(float value) {
    LOG_TRACE_L3(logger, "called pwm with {}", value);
    m_pwm.write(value);
}
#else
pwm::pwm(int pin) {
    LOG_DEBUG(logger, "initialized pwm on pin {}", pin);
}

void pwm::setValue(float value) {
    LOG_DEBUG(logger, "called pwm with {}", value);
}
#endif
