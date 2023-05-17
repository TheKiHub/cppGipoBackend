#include "pwm.hpp"
#include "gipoI2c.hpp"
#include<unistd.h>
#include "imGuiCustom.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    imGuiCustom gui;
    pwm p(5);
    quill::start(true);
    quill::get_logger()->set_log_level(quill::LogLevel::Debug);
    if (gui.createWindow() != 0) {
        return -1;
    }
    auto i2c = gipoI2c(75);
    while(gui.checkWindow()) {
        imGuiCustom::createFrame();
        i2c.render();
        gui.renderFrame();
    }
    return 0;
}
