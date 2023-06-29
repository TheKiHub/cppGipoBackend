//
// Created by kim on 4/10/21.
//

#ifndef LIBS_INCLUDE_GIPO_I2C_HPP_
#define LIBS_INCLUDE_GIPO_I2C_HPP_

#include "quill/Quill.h"
#include <memory>

#if MRAA
    #include "mraa/i2c.hpp"
#endif
#if USE_GUI
    #include <imgui.h>
#endif

class i2cDevice {
#if MRAA
  mraa::I2c& m_i2c;
#else
  std::vector<std::uint8_t> simulatedBytes;
    bool loop = false;
#endif

  quill::Logger *m_logger = quill::get_logger();
  uint8_t m_i2cAddress;

 public:
  [[nodiscard]] uint8_t getAddress() const;

#if MRAA
  /***
   * Class for communicating with the i2c bus interface.
   * @param busAddress The i2c bus address to communicate on. This depends on the peripheral device and is defined by the manufacturer.
   */
  i2cDevice(uint8_t busAddress, mraa::I2c& getI2cDevice);
#else
  explicit i2cDevice(uint8_t busAddress);
#endif


  /***
   * Read one byte from the bus
   * @return The read byte
   */
  uint8_t I2CRead();

  /***
   * Read one byte from an specific getI2cDevice register
   * @param reg The getI2cDevice register which will be read
   * @return The read byte
   */
  uint8_t I2CReadReg8(uint8_t reg);

  /***
   * Write one byte on the bus
   * @param data The byte which will be written
   * @return Result of operation
   */
  uint8_t I2CWrite(uint8_t data);

  /***
 * Write one byte to an specific getI2cDevice register
 * @param reg The getI2cDevice register which will be written to
 * @param data The byte which will be send
 * @return Result of operation
 */
  uint8_t I2CWriteReg8(uint8_t reg, uint8_t data);

#if USE_GUI
  void render();
  int inputByte {0};
  bool m_shouldRender {false};
  std::unordered_map<uint8_t, std::vector<std::uint8_t>> allSimulatedBytes;
  ImU8 simulatedByte{0};
#endif
};

#endif //LIBS_INCLUDE_GIPO_I2C_HPP_
