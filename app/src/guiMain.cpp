#include "gipoPwmPin.hpp"
#include "i2cDevice.hpp"
#include "imGuiCustom.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    imGuiCustom gui;
    gui.programName = "Gipo";
    quill::start(true);
    quill::get_logger()->set_log_level(quill::LogLevel::TraceL3);
    if (gui.createWindow() != 0) {
        return -1;
    }
    auto i2c = gipoI2c(75);

    // Create a thread
    std::thread t([&]() {
      while (gui.checkWindow()) {
          i2c.I2CRead();
          std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
    });

    while(gui.checkWindow()) {
        imGuiCustom::createFrame();
        i2c.render();
        gui.renderFrame();
    }

    // Join the thread
    t.join();
    return 0;
}
