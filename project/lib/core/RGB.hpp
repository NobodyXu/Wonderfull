#ifndef  __Wonderfull_project_core_Effect_RGB_HPP__
# define __Wonderfull_project_core_Effect_RGB_HPP__

# include "types.hpp"
# include "digitalPin_t.hpp"

namespace core::Effect {
class RGB {
    digitalPin_t Red;
    digitalPin_t Gre;
    digitalPin_t Blu;

public:
    RGB(pin_t red_pin, pin_t green_pin, pin_t blue_pin);

    void setRed();
    void setGre();
    void setBlu();

    void unsetRed();
    void unsetGre();
    void unsetBlu();
};
} /* namespace core::Effect */

#endif
