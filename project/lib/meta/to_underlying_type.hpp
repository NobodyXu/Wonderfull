#ifndef  __Wonderfull_project_meta_to_underlying_type_HPP__
# define __Wonderfull_project_meta_to_underlying_type_HPP__

# include <type_traits>

# include "as_t.hpp"

namespace meta {
template <class T>
constexpr auto to_underlying_type(T t) noexcept {
    static_assert(is_enum_v<T>);

    return static_cast<std::underlying_type_t<T>>(t);
}
} /* namespace meta */

namespace test::static_test {
enum class e1 {a = 1};
enum class e2: unsigned char {a = 255};

static_assert(utility::to_underlying_type(e1::a) == 1);
static_assert(utility::to_underlying_type(e2::a) == as_t<unsigned char>{255});
} /* namespace test::static_test */
#endif
