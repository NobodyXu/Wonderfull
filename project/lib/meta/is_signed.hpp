#ifndef  __Wonderfull_project_meta_is_signed_HPP__
# define __Wonderfull_project_meta_is_signed_HPP__

namespace meta {
template <class T>
static constexpr const inline bool is_signed_v = false;

# define DEF_SPECIALIZATION(type)                           \
template <>                                                 \
static constexpr const inline bool is_signed_v<type> = true

DEF_SPECIALIZATION(signed char);
DEF_SPECIALIZATION(signed short);
DEF_SPECIALIZATION(signed int);
DEF_SPECIALIZATION(signed long);
DEF_SPECIALIZATION(signed long long);
# undef  DEF_SPECIALIZATION
} /* namespace meta */

#endif
