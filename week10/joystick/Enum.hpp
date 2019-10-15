#ifndef  __Wonderfull_week10_joystick_joystick_HPP__
# define __Wonderfull_week10_joystick_joystick_HPP__

template <class T = int>
struct Enum {
    T value;

    using value_type = T;

# define DEF_CMP_OP(OP)                                            \
    constexpr bool operator OP (const Enum &other) const noexcept {\
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

# define Enumerator static constexpr const auto

#endif
