//
// Created by kim on 8/24/21.
//

#include "gipoPwmPin.hpp"

#if MRAA
gipoPwmPin::gipoPwmPin(int pin) : m_pwm{pin}, m_pin{pin}{
    LOG_DEBUG(logger, "initialized pwm on pin {}", pin);
    m_pwm.enable(true);
}

void gipoPwmPin::setValue(float value) {
    LOG_TRACE_L3(logger, "called pwm with {}", value);
    m_pwm.write(value);
}
#else
gipoPwmPin::gipoPwmPin(int pin) : m_pin{pin} {
    LOG_DEBUG(logger, "initialized pwm on pin {}", pin);
}

void gipoPwmPin::setValue(float value) {
    LOG_DEBUG(logger, "called pwm with {}", value);
}
#endif

int gipoPwmPin::getPin() const {
    return m_pin;
}
