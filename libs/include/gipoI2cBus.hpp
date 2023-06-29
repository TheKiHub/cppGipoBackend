//
// Created by Kim Huber on 6/12/23.
//

#ifndef GIPOBACKEND_LIBS_INCLUDE_GIPOI2CBUS_HPP_
#define GIPOBACKEND_LIBS_INCLUDE_GIPOI2CBUS_HPP_

#if MRAA
    #include "mraa/common.hpp"
    #include "mraa/i2c.hpp"
#endif


class gipoI2CBus {
#if MRAA
  mraa::I2c m_i2c;
#endif
    uint8_t m_busNumber;
    std::vector<std::shared_ptr<i2cDevice>> m_I2CDevices;

    public:

      /***
      * Class for communicating with the getI2cDevice bus interface.
      * @param busNumber The getI2cDevice bus number if there are multiple busses. If there is only one bus 0 should be used in most cases.
      */
      explicit gipoI2CBus(uint8_t busNumber);


      [[nodiscard]] uint8_t getBusNumber() const;

      /***
      * returns the reference to a communication device connected on the address
      * @param busAddress The getI2cDevice bus address to communicate on. This depends on the peripheral device and is defined by the manufacturer.
      */
      std::shared_ptr<i2cDevice> getDevice(uint8_t address);

#if USE_GUI
    void render();
    bool m_shouldRender {false};
#endif

};

#endif //GIPOBACKEND_LIBS_INCLUDE_GIPOI2CBUS_HPP_
