//
// Created by kim on 8/24/21.
//

#ifndef GIPO_LIBS_INCLUDE_PWM_HPP_
#define GIPO_LIBS_INCLUDE_PWM_HPP_

#include "quill/Quill.h"

#if MRAA
    #include "mraa/common.hpp"
    #include "mraa/pwm.hpp"
#endif

class gipoPwmPin {
#if MRAA
  mraa::Pwm m_pwm;
#endif

  quill::Logger *logger = quill::get_logger();
  int m_pin;

 public:
  explicit gipoPwmPin(int pin);
  void setValue(float value);
  [[nodiscard]] int getPin() const;
};

#endif //GIPO_LIBS_INCLUDE_PWM_HPP_
