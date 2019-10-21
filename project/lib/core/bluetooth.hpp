#ifndef  __Wonderfull_project_core_bluetooth_HPP__
# define __Wonderfull_project_core_bluetooth_HPP__

# include <SoftwareSerial.h>
# include "digitalPin_t.hpp"

namespace core::Control {
class Bluetooth {
protected:
    SoftwareSerial blueToothSerial;
    digitalPin_t ConnectionStatus;

    Bluetooth(pin_t RxD, pin_t TxD, pin_t ConnectionStatus_pin) noexcept;

    void setupBlueToothConnection(const char *mode, const char *Cmd_str, const char *AdditionalConfigurationCmd, int shieldPairNumber);
    auto getSlaveAddress(int shieldPairNumber, const char *slaveName) -> String;
    void makeConnection(String slaveAddr);

public:
    /*!
     * Create a master bluetooth
     *
     * Make sure Serial is open for output before calling this function.
     */
    static auto master(pin_t RxD, pin_t TxD, pin_t ConnectionStatus_pin, int shieldPairNumber) noexcept -> Bluetooth;

    /*!
     * Create a slave bluetooth
     *
     * Make sure Serial is open for output before calling this function.
     */
    static auto slave(pin_t RxD, pin_t TxD, pin_t ConnectionStatus_pin, int shieldPairNumber) noexcept -> Bluetooth;

    bool is_connected() const noexcept;

    auto print() noexcept -> Bluetooth& {
        return *this;
    }

    template <class T, class ...Ts>
    auto print(T &&obj, Ts &&...objs) -> Bluetooth& {
        blueToothSerial.print(obj);
        return print(objs...);
    }

    template <class ...Ts>
    auto println(Ts &&...objs) -> Bluetooth& {
        return print(objs..., '\n');
    }

    /*!
     * read in one character, blocks if !is_available().
     */
    char read();

    /*!
     * returns whether at least one character is ready for read.
     */
    bool is_available() const noexcept;

    /*!
     * read characters into the Buffer until
     * F(buffer) == true.
     *
     * @ return the buffer
     */
    template <class F>
    String read(F &&f) {
        String buffer;

        do {
            buffer += read();
        } while (!f(buffer));

        return buffer;
    }

    void flush();
};
} /* namespace core::Control */

#endif
