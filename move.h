#include <boost/format.hpp>
#include <boost/type_index.hpp>
#include <type_traits>
#include <iostream>

// A& & becomes A&
// A& && becomes A&
// A&& & becomes A&
// A&& && becomes A&&

// create own remove_reference and move function
namespace RmNs
{

template <typename T>
struct remove_reference
{
    typedef T type;
};

template <typename T>
struct remove_reference<T&>
{
    typedef T type;
};

template <typename T>
struct remove_reference<T&&>
{
    typedef T type;
};

} // namespace RmNs

namespace MoveNs
{

template <typename T>
typename RmNs::remove_reference<T>::type&& move(T&& param)
{
    std::cout << "T's type: " << boost::typeindex::type_id_with_cvr<T>().pretty_name() <<
        ", param's type: " << boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name();
    std::cout << '\n';
    return static_cast<typename RmNs::remove_reference<T>::type&&>(param);
}

} // namespace MoveNs
