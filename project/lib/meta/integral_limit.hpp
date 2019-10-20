#ifndef  __Wonderfull_project_meta_integral_limit__HPP__
# define __Wonderfull_project_meta_integral_limit__HPP__

# include "is_signed.hpp"

namespace meta {
template <class T>
struct integral_limit {
    static constexpr T min() noexcept {
        if constexpr (is_signed<T>)
            return 1 << (sizeof(T) * 8 - 1);
        else
            return 0;
    }

    static constexpr T max() noexcept {
        return min() - 1;
    }
};
} /* namespace meta */

#endif
