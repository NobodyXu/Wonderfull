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
    SoftSerial(pin_t RxD, pin_t TxD, unsigned bitrate);

    bool is_available();

    /*!
     * read in one character, blocks if is_available() == false.
     */
    char getchar();

    void print() noexcept {}

    template <class T, class ...Ts>
    void print(T &&obj, Ts &&...objs);

    template <class ...Ts>
    void println(Ts &&...objs);

    void flush();
};

template <class T, class ...Ts>
void SoftSerial::print(T &&obj, Ts &&...objs) {
    serial.print(obj);
    print(objs...);
}

template <class ...Ts>
void SoftSerial::println(Ts &&...objs) {
    print(objs..., '\n');
}
} /* namespace core::Comm */

#endif
