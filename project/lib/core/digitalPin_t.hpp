#ifndef  __Wonderfull_project_core_digitalPin_t_HPP__
# define __Wonderfull_project_core_digitalPin_t_HPP__

# include <Arduino.h>
# include "types.hpp"

namespace core {
/*!
 * A low level RAII wrapper of pin, providing only digital io.
 *
 * The wrapper is created so that when the implementation of methods does not suit 
 * the application anymore, it can be changed easily by modifing the code in digitalPin_t.cpp.
 *
 * Also, it provides an easy way to implement a track on what pin is being used and 
 * how should the pin be configured when it is not used.
 */
class digitalPin_t {
public:
    enum class Mode: unsigned char {
        input = INPUT,
        input_pullup = INPUT_PULLUP,
        output = OUTPUT
    };

    enum class Level: bool {
        low = LOW,
        high = HIGH
    };

private:
    pin_t pin;

public:
    /*!
     * Default-initailizer will returns an object that is not 
     * usable, but rather as a placeholder.
     *
     * This is usefull for optional digital pin.
     */
    digitalPin_t() noexcept;
    digitalPin_t(pin_t pin_arg, Mode mode) noexcept;

    /*!
     * Check whether it contains a valid pin.
     */
    bool is_valid_pin() const noexcept;

    Level read() const noexcept;
    void write(Level) const noexcept;

    void tone(unsigned frequency) const noexcept;
    void tone(unsigned frequency, unsigned long duration) const noexcept;
    void noTone() const noexcept;

    void pulseIn(Level l) const noexcept;
    void pulseIn(Level l, unsigned timeout) const noexcept;

    void pulseInLong(Level l) const noexcept;
    void pulseInLong(Level l, unsigned timeout) const noexcept;

    pin_t raw() const noexcept;

    ~digitalPin_t() noexcept;
};
} /* namespace core */
#endif
