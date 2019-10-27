#ifndef  __Wonderfull_project_core_Comm_SoftSerial_HPP__
# define __Wonderfull_project_core_Comm_SoftSerial_HPP__

# include "digitalPin_t.hpp"

# include <Arduino.h>
# include <SoftwareSerial.h>

namespace core::Comm {
/*!
 * This is a wrapper over SoftwareSerial,
 * to make using it easier.
 */
class SoftSerial {
    SoftwareSerial serial;

public:
    SoftSerial(pin_t RxD, pin_t TxD, unsigned bitrate):
        serial{RxD, TxD}
    {
        serial.begin(bitrate);
    }

    bool is_available() {
        return serial.available();
    }

    /*!
     * read in one character, blocks if !is_available().
     */
    char read() {
        while (!is_available())
            /* block */;
        return serial.read();
    }

    /*!
     * This is a *blocking* call utilizing read().
     *
     * Read characters into the buffer until !F(buffer).
     */
    template <class F>
    auto read(F &&f) -> String {
        String buffer;

        do {
            buffer += read();
        } while (!f(buffer));
        
        return buffer;
    }

    void print() noexcept {}

    template <class T, class ...Ts>
    void print(T &&obj, Ts &&...objs) {
        serial.print(obj);
        print(objs...);
    }

    template <class ...Ts>
    void println(Ts &&...objs) {
        print(objs..., '\n');
    }

    void flush() {
        serial.flush();
    }
};
} /* namespace core::Comm */

#endif
