#ifndef  __Wonderfull_week10_joystick_bitfield_HPP__
# define __Wonderfull_week10_joystick_bitfield_HPP__

# include <Arduino.h>

template <class T, size_t N>
struct bitfield {
    T value: N;

# define DEF_CMP_OP(OP)                                            \
    constexpr bool operator OP (const bitfield &other) const noexcept {\
        return value OP other.value;                                     \
    }

    DEF_CMP_OP(==)
    DEF_CMP_OP(!=)
    DEF_CMP_OP(<)
    DEF_CMP_OP(<=)
    DEF_CMP_OP(>)
    DEF_CMP_OP(>=)

# undef  DEF_CMP_OP

    explicit constexpr operator T () const noexcept {
        return value;
    }

    constexpr auto to_underlying_type() const noexcept {
        return value;
    }
};

#endif
