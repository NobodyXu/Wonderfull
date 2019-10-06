#ifndef  __Wonderfull_project_meta_as_t_HPP__
# define __Wonderfull_project_meta_as_t_HPP__

namespace meta {
/*!
 * The main usage of this alias is to create
 * temporary object of type `unsigned int/long`.
 */
template <class T>
using as_t = T;
} /* namespace meta */
#endif
