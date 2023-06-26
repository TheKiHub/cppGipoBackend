//
// Created by Kim Huber on 6/12/23.
//

#ifndef GIPOBACKEND_LIBS_INCLUDE_GIPOMANAGER_HPP_
#define GIPOBACKEND_LIBS_INCLUDE_GIPOMANAGER_HPP_

#include "gipoPwmPin.hpp"
#include "i2cDevice.hpp"
#include "gipoI2cBus.hpp"

#if USE_GUI
    #include <imgui.h>
#endif

class gipoManager {
  gipoManager() = default; // Private constructor to prevent instantiation

  std::vector<std::shared_ptr<gipoPwmPin>> m_pwmVector;
  std::vector<std::shared_ptr<gipoI2CBus>> m_i2CBusses;

#if USE_GUI
  enum vectorType{NONE, PWM, I2C};
  std::vector<std::pair<vectorType, size_t>> m_usedPins{};
  bool simulateIC = true;
  void newPin(bool &openBool, size_t pin);
  void newI2C(bool &openBool);
  void newPWM(bool &openBool, size_t pin);
#endif

 public:
  gipoManager(const gipoManager&) = delete; // Deleting copy constructor
  gipoManager& operator=(const gipoManager&) = delete; // Deleting assignment operator

  static gipoManager& getInstance();
  std::shared_ptr<gipoPwmPin> pwm(uint8_t pin);
  std::shared_ptr<i2cDevice> getI2cDevice(uint8_t bus, uint8_t address);
  std::shared_ptr<gipoI2CBus> getI2cBuses(uint8_t bus);

#if USE_GUI
  void render();
#endif
};

#endif //GIPOBACKEND_LIBS_INCLUDE_GIPOMANAGER_HPP_
