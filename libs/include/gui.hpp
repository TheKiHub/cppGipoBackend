//
// Created by Kim Huber on 2/27/23.
//

#ifndef GIPOBACKEND_LIBS_INCLUDE_GUI_HPP_
#define GIPOBACKEND_LIBS_INCLUDE_GUI_HPP_

#include "imGuiCustom.h"
#include "gipoI2c.hpp"

class gui {
    gipoI2c m_i2cBackend;
    imGuiCustom m_gui;

 public:
    gui(uint8_t busAddress, uint8_t busNumber = 0);
};

#endif //GIPOBACKEND_LIBS_INCLUDE_GUI_HPP_
