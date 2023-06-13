//
// Created by Kim Huber on 6/12/23.
//

#include "gipoI2cBus.hpp"

#if MRAA
    gipoI2CBus::gipoI2CBus(uint8_t busNumber) : m_i2c{busNumber}, m_busNumber{busNumber} {}
#else
    gipoI2CBus::gipoI2CBus(uint8_t busNumber) : m_busNumber{busNumber} {}
#endif

uint8_t gipoI2CBus::getBusNumber() const {
    return m_busNumber;
}

i2cDevice &gipoI2CBus::getDevice(uint8_t address) {
    for (auto& device : m_I2CDevices) {
        if (device.getAddress() == address) {
            return device;
        }
    }
#if MRAA
    return m_I2CDevices.emplace_back(address, m_i2c);
#else
    return m_I2CDevices.emplace_back(address);
#endif
}
