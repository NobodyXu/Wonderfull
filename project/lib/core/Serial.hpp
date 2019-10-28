/*!
 * The functions in this file wrap over functions provided by 
 * HardwareSerial and SoftwareSerial so that they are more instinct.
 */
#ifndef  __Wonderfull_project_core_Serial_HPP__
# define __Wonderfull_project_core_Serial_HPP__

# include "digitalPin_t.hpp"
# include <Arduino.h>

namespace core::Comm {
template <class Serial_t>
class Serial {
    Serial_t serial;

public:
    Serial() = delete;
    Serial(const Serial&) = delete;
    Serial(Serial&&) = delete;

    Serial& operator = (const Serial&) = delete;
    Serial& operator = (Serial&&) = delete;

    Serial(pin_t RxD, pin_t TxD):
        serial{RxD, TxD}
    {}

    /*!
     * This is for makeHardwareSerial
     */
    Serial(HardwareSerial &s):
        serial{s}
    {}

    void begin(unsigned rate) {
        serial.begin(rate);
    }

    /*!
     * is_avilable() test whether serial has the next byte available.
     */
    bool is_available() {
        return serial.available();
    }
    
    /*!
     * getChar() is a blocking function call.
     * It will block until is_avilable(serial) == true and then
     * convert serial.read() to type char so that it can be latter printed.
     */
    char getChar() {
        while (!is_available())
            /* block */;

        return serial.read();
    }

    /*!
     * read(cnt) is for reading `cnt` number of characters
     * into the buffer and return it.
     */
    String read(unsigned cnt) {
        String ret;

        for (unsigned i = 0; i != cnt; ++i)
            ret += getChar();

        return ret;
    }
    
    /*!
     * print(objs...) will print all objects to serial.
     */
    template <class T, class ...Ts>
    void print(T &&t, Ts &&...ts) {
        serial.print(t);
        // Recursion
        print(ts...);
    }
    
    /*!
     * base case of recursion:
     *     no arguments is supplied (they are exhausted by recursion)
     */
    void print() {}
    
    /*!
     * println(serial, objs...) will print all objs to serial, along
     * with a trailing newline.
     */
    template <class ...Ts>
    void println(Ts &&...ts) {
        print(ts..., '\n');
    }

    void flush() {
        serial.flush();
    }
};
} /* namespace core::Comm */

#endif
