//
// Created by Kim Huber on 6/12/23.
//

#ifndef GIPOBACKEND_LIBS_INCLUDE_GIPOMANAGER_HPP_
#define GIPOBACKEND_LIBS_INCLUDE_GIPOMANAGER_HPP_

#include "gipoPwmPin.hpp"
#include "i2cDevice.hpp"
#include "gipoI2cBus.hpp"

class gipoManager {
  gipoManager() = default; // Private constructor to prevent instantiation

  std::vector<gipoPwmPin> m_pwmVector;
  std::vector<gipoI2CBus> m_i2CBusses;

 public:
  gipoManager(const gipoManager&) = delete; // Deleting copy constructor
  gipoManager& operator=(const gipoManager&) = delete; // Deleting assignment operator

  static gipoManager& getInstance();
  [[nodiscard]] gipoPwmPin& pwm(uint8_t pin);
  i2cDevice& i2c(uint8_t bus, uint8_t address);

};

#endif //GIPOBACKEND_LIBS_INCLUDE_GIPOMANAGER_HPP_
