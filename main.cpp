#include <iostream>
#include <string>
#include <type_traits>
#include <boost/type_index.hpp>

// create own move function

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
typename RmNs::remove_reference<T>::type&& move(T&& arg)
{
    std::cout << "arg's type: " <<
        boost::typeindex::type_id_with_cvr<decltype(arg)>().pretty_name() << '\n';
    return static_cast<typename RmNs::remove_reference<T>::type&&>(arg);
}

} // namespace MoveNs


class TestSubject
{
};

TestSubject get_test_subject()
{
    return TestSubject();
}

int main()
{
    {
        TestSubject lvalue;
        std::cout << "call move with lvalue, ";
        MoveNs::move(lvalue);

        std::cout << "returned type for move with lvalue: " <<
            boost::typeindex::type_id_with_cvr<decltype(MoveNs::move(lvalue))>().pretty_name();
        std::cout << '\n';
    }

    std::cout << '\n';

    {
        std::cout << "call move with rvalue, ";
        MoveNs::move(get_test_subject());

        std::cout << "returned type for move with rvalue: " <<
            boost::typeindex::type_id_with_cvr<decltype(MoveNs::move(get_test_subject()))>().pretty_name();
        std::cout << '\n';
    }

    return 0;
}
