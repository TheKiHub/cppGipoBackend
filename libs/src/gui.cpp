//
// Created by Kim Huber on 2/27/23.
//

#include "gui.hpp"

gui::gui(uint8_t busAddress, uint8_t busNumber) :
    m_i2cBackend(busAddress, busNumber)
    {
    if (m_gui.createWindow() != 0) {
        return;
    }
    while(m_gui.checkWindow()) {
        imGuiCustom::createFrame();
        m_gui.renderFrame();
    }
}
