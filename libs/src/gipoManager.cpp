//
// Created by Kim Huber on 6/12/23.
//

#include "gipoManager.hpp"

gipoManager& gipoManager::getInstance() {
    static gipoManager instance;
    return instance;
}

gipoPwmPin &gipoManager::pwm(uint8_t pin) {
    for (auto& pwmPin : m_pwmVector) {
        if (pwmPin.getPin() == pin) {
            return pwmPin;
        }
    }
    return m_pwmVector.emplace_back(pin);
}

i2cDevice &gipoManager::i2c(uint8_t bus, uint8_t address) {
    for (auto& i2cBus : m_i2CBusses) {
        if (i2cBus.getBusNumber() == bus) {
            return i2cBus.getDevice(address);
        }
    }
    auto& newBus = m_i2CBusses.emplace_back(bus);
    return newBus.getDevice(address);
}
