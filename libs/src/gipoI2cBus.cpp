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

std::shared_ptr<i2cDevice> gipoI2CBus::getDevice(uint8_t address) {
    for (auto& device : m_I2CDevices) {
        if (device->getAddress() == address) {
            return device;
        }
    }
#if MRAA
    return m_I2CDevices.emplace_back(std::make_shared<i2cDevice>(address, m_i2c));
#else
    return m_I2CDevices.emplace_back(std::make_shared<i2cDevice>(i2cDevice(address)));
#endif
}

#if USE_GUI
    void gipoI2CBus::render() {
        if(!m_shouldRender) return;

        ImGui::Begin((fmtquill::format("I2c bus number{:d}", m_busNumber).c_str()), &m_shouldRender);

        static int address = 0;
        ImGui::InputInt("Address", &address);
        address = static_cast<uint8_t>(address);

        if(ImGui::Button("Add I2C Device"))
            getDevice(static_cast<uint8_t>(address));

        for (auto& device : m_I2CDevices) {
            if (ImGui::Button(("Address " + std::to_string(device->getAddress())).c_str()))
                device->m_shouldRender = true;

            device->render();
            ImGui::SameLine();
        }

        ImGui::End();
    }
#endif
