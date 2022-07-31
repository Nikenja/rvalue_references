#include <iostream>
#include <boost/format.hpp>
#include <boost/type_index.hpp>

static boost::format function("function: %1%\n");
static boost::format t_type("T's type: %1%\n");
static boost::format param_type("param's type: %1%\n");

template <typename T>
void reference(T& param)
{
    std::cout << (function % __FUNCTION__).str();
    std::cout << (t_type % boost::typeindex::type_id_with_cvr<T>().pretty_name()).str();
    std::cout << (param_type % boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name()).str();
}

template <typename T>
void const_reference(const T& param)
{
    std::cout << (function % __FUNCTION__).str();
    std::cout << (t_type % boost::typeindex::type_id_with_cvr<T>().pretty_name()).str();
    std::cout << (param_type % boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name()).str();
}

template <typename T>
void value(T param)
{
    std::cout << (function % __FUNCTION__).str();
    std::cout << (t_type % boost::typeindex::type_id_with_cvr<T>().pretty_name()).str();
    std::cout << (param_type % boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name()).str();
}
