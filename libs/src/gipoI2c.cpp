//
// Created by kim on 4/10/21.
//

#include "gipoI2c.hpp"
#include "imgui.h"

#if MRAA
gipoI2c::gipoI2c(uint8_t busAddress) : m_i2c{mraa::I2c(0)} {
    LOG_TRACE_L3(m_logger, "I2C MRAA initialized using address: {}", busAddress);
    m_i2cAddress = busAddress;
    m_i2c.address(busAddress);
}

gipoI2c::gipoI2c (uint8_t busAddress, uint8_t busNumber) : m_i2c{mraa::I2c(busNumber)} {
    LOG_TRACE_L3(m_logger, "I2C MRAA initialized on bus: {} using address: {}", busNumber, busAddress);
    m_i2cAddress = busAddress;
    m_i2c.address(busAddress);
}

uint8_t gipoI2c::I2CRead() {
    LOG_TRACE_L3(m_logger, "I2C read byte on address: {}", m_i2cAddress);
    m_i2c.address(m_i2cAddress);
    return m_i2c.readByte();
}

uint8_t gipoI2c::I2CReadReg8(uint8_t reg) {
    LOG_TRACE_L3(m_logger, "I2C read register: {} on address: {}", reg, m_i2cAddress);
    m_i2c.address(m_i2cAddress);
    return m_i2c.readReg(reg);
}

uint8_t gipoI2c::I2CWrite (uint8_t data) {
    LOG_TRACE_L3(m_logger, "I2C writing data: {} on address: {}", data, m_i2cAddress);
    m_i2c.address(m_i2cAddress);
    return m_i2c.writeByte(data);
}

uint8_t gipoI2c::I2CWriteReg8 (uint8_t reg, uint8_t data) {
    LOG_TRACE_L3(m_logger, "I2C writing data: {} on register: {} on address: {}", data, reg, m_i2cAddress);
    m_i2c.address(m_i2cAddress);
    return m_i2c.writeReg(reg, data);
}
#else
    #if USE_GUI
        void gipoI2c::render() {
            ImGui::Begin("I2c");
            ImGui::Text("On channel = %d", m_i2cAddress);
            ImGui::InputInt("Byte", &inputByte);
            if (ImGui::Button("Write Byte"))
                I2CWrite(static_cast<uint8_t>(inputByte));

        }
    #endif
    gipoI2c::gipoI2c(uint8_t busAddress) {
        m_i2cAddress = busAddress;
        LOG_TRACE_L3(m_logger, "I2C ready on address: {}", busAddress);
    }

    gipoI2c::gipoI2c(uint8_t busAddress, uint8_t busNumber) {
        m_i2cAddress = busAddress;
        LOG_TRACE_L3(m_logger, "I2CSetup ready on bus: {} with address: {}", busNumber, busAddress);
    }

    uint8_t gipoI2c::I2CWrite(uint8_t data) {
        #if USE_GUI
            buf.emplace_back(data);
        #endif
        LOG_TRACE_L3(m_logger, "I2CWrite address: {} data: {}", m_i2cAddress, data);
        return 0;
    }

    uint8_t gipoI2c::I2CWriteReg8(uint8_t reg, uint8_t data) {
        LOG_TRACE_L3(m_logger, "I2CWriteReg8 address: {} register: {} data: {}", m_i2cAddress, reg, data);
        return 0;
    }

    uint8_t gipoI2c::I2CRead() {
        LOG_TRACE_L3(m_logger, "I2C read byte on address: {}", m_i2cAddress);
        return 0;
    }

    uint8_t gipoI2c::I2CReadReg8(uint8_t reg) {
        LOG_TRACE_L3(m_logger, "I2C read register: {} on address: {}", reg, m_i2cAddress);
        return 0;
    }
#endif