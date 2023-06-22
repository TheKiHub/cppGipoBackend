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

i2cDevice &gipoManager::getI2cDevice(uint8_t bus, uint8_t address) {
    for (auto& i2cBus : m_i2CBusses) {
        if (i2cBus.getBusNumber() == bus) {
            return i2cBus.getDevice(address);
        }
    }
    auto& newBus = m_i2CBusses.emplace_back(bus);
    return newBus.getDevice(address);
}

gipoI2CBus &gipoManager::getI2cBuses(uint8_t bus) {
    for (auto& i2cBus : m_i2CBusses) {
        if (i2cBus.getBusNumber() == bus) {
            return i2cBus;
        }
    }
    return m_i2CBusses.emplace_back(bus);
}

#if USE_GUI
    void gipoManager::render() {
        static bool openNewPin = false;
        static size_t currentPin = 0;

        ImGui::Begin("GipoManager");
        ImGui::Separator();

        if(simulateIC) {
            if(m_usedPins.empty()) {
                ImGui::Begin("create Ic");
                static int numberOfPins;
                ImGui::InputInt("Number Of Pins", &numberOfPins);

                if(ImGui::Button("Ok")) {
                    m_usedPins.resize(static_cast<size_t>(numberOfPins));
                }
                ImGui::End();
            } else {
                ImGui::Text("Simulated IC");
                bool toggle = true;
                for (const auto & pair : m_usedPins) {
                    auto index = &pair - &m_usedPins[0];
                    switch (pair.first) {
                        case NONE:
                            if(ImGui::Button(fmt::format("+##{:d}", index).c_str())) {
                                openNewPin = true;
                                currentPin = static_cast<size_t>(index);
                            }
                            break;
                        case PWM:
                            ImGui::BeginDisabled();
                            ImGui::Button(("Current Value " + std::to_string(5)).c_str());
                            ImGui::EndDisabled();
                            break;
                        case I2C:
                            if (ImGui::Button(fmt::format("I2C Bus {:d}",m_i2CBusses.at(pair.second).getBusNumber()).c_str()))
                                m_i2CBusses.at(pair.second).m_shouldRender = true;
                            break;
                    }
                    if(toggle)
                        ImGui::SameLine();
                    toggle = !toggle;
                }

                for (auto& i2cBus : m_i2CBusses) {
                    i2cBus.render();
                }
            }
        } else {
            for (auto& i2cBus : m_i2CBusses) {
                if (ImGui::Button(fmt::format("I2C Bus {:d}", i2cBus.getBusNumber()).c_str())) {
                    i2cBus.m_shouldRender = true;
                }
                i2cBus.render();
                ImGui::SameLine();
            }
        }
        if(openNewPin) newPin(openNewPin, currentPin);
        ImGui::End();
    }

    void gipoManager::newI2C(bool &openBool) {
        ImGui::Begin("newI2C", &openBool);

        static int clPin{0}, dataPin{0}, busNumber{0};
        ImGui::InputInt("Physical clock pin number", &clPin);
        clPin = static_cast<uint8_t>(clPin);

        ImGui::InputInt("Physical data pin number", &dataPin);
        dataPin = static_cast<uint8_t>(dataPin);

        ImGui::InputInt("Bus number", &busNumber);
        busNumber = static_cast<uint8_t>(busNumber);
        if(ImGui::Button("Add")) {
            m_i2CBusses.emplace_back(static_cast<uint8_t>(busNumber));
            m_usedPins[static_cast<size_t>(clPin)] = std::make_pair(vectorType::I2C, m_i2CBusses.size() - 1);
            m_usedPins[static_cast<size_t>(dataPin)] = std::make_pair(vectorType::I2C, m_i2CBusses.size() - 1);
            openBool = false;
        }

        ImGui::End();
    }

    void gipoManager::newPWM(bool &openBool, size_t pin) {
        ImGui::Begin("newPWM", &openBool);

        static int gipoNumber = 0;
        ImGui::InputInt("PWM port Number", &gipoNumber);
        gipoNumber = static_cast<uint8_t>(gipoNumber);

        if(ImGui::Button("Add")) {
            m_pwmVector.emplace_back(gipoNumber);
            m_usedPins[pin] = std::make_pair(vectorType::PWM, m_usedPins.size() - 1);
            openBool = false;
        }

        ImGui::End();
    }

    void gipoManager::newPin(bool &openBool, size_t pin) {
        static bool showNewPwm, showNewI2c, showNewGipo, showNewNamedPin = false;
        ImGui::Begin(fmt::format("Config pin {:d}", pin).c_str(), &openBool);

        if(ImGui::Button("Add named pin"))
            showNewGipo = true;
        ImGui::SameLine();
        if(ImGui::Button("Add GIPO pin"))
            showNewNamedPin = true;
        if(ImGui::Button("Add PWM pin"))
            showNewPwm = true;
        ImGui::SameLine();
        if(ImGui::Button("Add I2C bus"))
            showNewI2c = true;

        if(showNewI2c) newI2C(showNewI2c);
        if(showNewPwm) newPWM(showNewPwm, pin);
        ImGui::End();
    }
#endif
