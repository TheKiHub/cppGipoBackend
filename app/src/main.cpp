#include "gipoManager.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    quill::start();
    quill::get_logger()->set_log_level(quill::LogLevel::TraceL3);

    auto pwm = gipoManager::getInstance().pwm(5);
    pwm.setValue(10);

    auto pwm2 = gipoManager::getInstance().pwm(50);
    pwm2.setValue(10);


    auto i2cDevice = gipoManager::getInstance().i2c(1, 75);
    LOG_INFO(quill::get_logger(), "Read byte: {}", i2cDevice.I2CRead());

    return 0;
}
