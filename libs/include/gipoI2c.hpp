//
// Created by kim on 4/10/21.
//

#ifndef LIBS_INCLUDE_GIPO_I2C_HPP_
#define LIBS_INCLUDE_GIPO_I2C_HPP_

#include "quill/Quill.h"

#if MRAA
    #include "mraa/common.hpp"
    #include "mraa/i2c.hpp"
#endif

class gipoI2c {
#if MRAA
  mraa::I2c m_i2c;
#endif

  quill::Logger *m_logger = quill::get_logger();
  uint8_t m_i2cAddress;

 public:
  /***
   * Class for communicating with the i2c bus interface.
   * @param busAddress The i2c bus address to communicate on. This depends on the peripheral device and is defined by the manufacturer.
   */
  explicit gipoI2c(uint8_t busAddress);

  /***
  * Class for communicating with the i2c bus interface.
  * @param busAddress The i2c bus address to communicate on. This depends on the peripheral device and is defined by the manufacturer.
  * @param busNumber The i2c bus number if there are multiple busses. If there is only one bus 0 should be used in most cases.
  */
  gipoI2c(uint8_t busAddress, uint8_t busNumber);

  /***
   * Read one byte from the bus
   * @return The read byte
   */
  uint8_t I2CRead();

  /***
   * Read one byte from an specific i2c register
   * @param reg The i2c register which will be read
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
 * Write one byte to an specific i2c register
 * @param reg The i2c register which will be written to
 * @param data The byte which will be send
 * @return Result of operation
 */
  uint8_t I2CWriteReg8(uint8_t reg, uint8_t data);
#if USE_GUI
  int inputByte {0};
  std::vector<uint8_t> buf {'c'};
  void render();
#endif
};

#endif //LIBS_INCLUDE_GIPO_I2C_HPP_
