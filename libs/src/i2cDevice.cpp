//
// Created by kim on 4/10/21.
//

#include "i2cDevice.hpp"

#if MRAA
i2cDevice::i2cDevice(uint8_t busAddress, mraa::I2c &i2c) : m_i2c{i2c}, m_i2cAddress{busAddress} {
    LOG_TRACE_L1(m_logger, "I2C Pin initialized using address: {}", busAddress);
}

uint8_t i2cDevice::I2CRead() {
    LOG_TRACE_L3(m_logger, "I2C read byte on address: {}", m_i2cAddress);
    m_i2c.address(m_i2cAddress);
    return m_i2c.readByte();
}

uint8_t i2cDevice::I2CReadReg8(uint8_t reg) {
    LOG_TRACE_L3(m_logger, "I2C read register: {} on address: {}", reg, m_i2cAddress);
    m_i2c.address(m_i2cAddress);
    return m_i2c.readReg(reg);
}

uint8_t i2cDevice::I2CWrite (uint8_t data) {
    LOG_TRACE_L3(m_logger, "I2C writing data: {} on address: {}", data, m_i2cAddress);
    m_i2c.address(m_i2cAddress);
    return m_i2c.writeByte(data);
}

uint8_t i2cDevice::I2CWriteReg8 (uint8_t reg, uint8_t data) {
    LOG_TRACE_L3(m_logger, "I2C writing data: {} on register: {} on address: {}", data, reg, m_i2cAddress);
    m_i2c.address(m_i2cAddress);
    return m_i2c.writeReg(reg, data);
}

#else
    i2cDevice::i2cDevice(uint8_t busAddress) : m_i2cAddress{busAddress} {
        LOG_TRACE_L1(m_logger, "I2C ready on address: {}", busAddress);
    }

    uint8_t i2cDevice::I2CWrite(uint8_t data) {
        LOG_TRACE_L3(m_logger, "I2CWrite address: {} data: {}", m_i2cAddress, data);
        return 0;
    }

    uint8_t i2cDevice::I2CWriteReg8(uint8_t reg, uint8_t data) {
        LOG_TRACE_L3(m_logger, "I2CWriteReg8 address: {} register: {} data: {}", m_i2cAddress, reg, data);
        return 0;
    }

    uint8_t i2cDevice::I2CRead() {
        if (simulatedBytes.empty()) {
            LOG_TRACE_L3(m_logger, "I2C read not simulated byte: 0 on address: {}", m_i2cAddress);
            return 0;
        }

        uint8_t firstEntry = simulatedBytes.front();
        if(loop)
            simulatedBytes.emplace_back(*simulatedBytes.begin());
        simulatedBytes.erase(simulatedBytes.begin());
        LOG_TRACE_L3(m_logger, "I2C read simulated byte: {} on address: {}", firstEntry, m_i2cAddress);
        return firstEntry;
    }

    uint8_t i2cDevice::I2CReadReg8(uint8_t reg) {
        if (simulatedBytes.empty()) {
            LOG_TRACE_L3(m_logger, "I2C read not simulated register: {} on address: {} got byte: 0", reg, m_i2cAddress);
            return 0;
        }

        uint8_t firstEntry = simulatedBytes.front();
        simulatedBytes.erase(simulatedBytes.begin());
        LOG_TRACE_L3(m_logger, "I2C read simulated register: {} on address: {} got byte: {}", reg, m_i2cAddress, firstEntry);
        return firstEntry;
    }
#endif

uint8_t i2cDevice::getAddress() const {
    return m_i2cAddress;
}

#if USE_GUI
    void i2cDevice::render() {
        if(!m_shouldRender) return;
        ImGui::Begin(fmt::format("i2cDevice on address {:d}", m_i2cAddress).c_str(), &m_shouldRender);

        ImGui::InputInt("Byte", &inputByte);
        if (ImGui::Button("Write Byte"))
            I2CWrite(static_cast<uint8_t>(inputByte));

        ImGui::Text("Simulate");
        ImGui::Separator();

        constexpr ImU8 u8_min  = 0, u8_max = 255;
        ImGui::SliderScalar("Byte value", ImGuiDataType_U8, &simulatedByte, &u8_min, &u8_max, "%u");
        if (ImGui::Button("Push byte"))
            simulatedBytes.emplace_back(simulatedByte);

        ImGui::Checkbox("Loop", &loop);
        ImGui::End();
    }
#endif
