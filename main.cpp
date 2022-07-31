#include <iostream>
#include <string>
#include <type_traits>
#include <boost/type_index.hpp>

#include "move.h"
#include "type_deduction.h"

class TestSubject
{
};

TestSubject get_test_subject()
{
    return TestSubject();
}

void test_move()
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

    std::cout << '\n';
}

void test_type_deduction()
{
    {
        std::cout << "with lvalue\n";
        TestSubject lvalue;
        reference(lvalue);
        std::cout << '\n';
    }

    {
        std::cout << "with lvalue&\n";
        TestSubject temp;
        TestSubject& lvalue(temp);
        reference(lvalue);
        std::cout << '\n';
    }

    {
        std::cout << "with lvalue\n";
        TestSubject lvalue;
        const_reference(lvalue);
        std::cout << '\n';
    }

    {
        std::cout << "with rvalue\n";
        const_reference(get_test_subject());
        std::cout << '\n';
    }

    {
        std::cout << "with lvalue\n";
        TestSubject lvalue;
        value(lvalue);
        std::cout << '\n';
    }

    {
        std::cout << "with lvalue&\n";
        TestSubject temp;
        TestSubject& lvalue = temp;
        value(lvalue);
        std::cout << '\n';
    }

    {
        std::cout << "with rvalue\n";
        value(get_test_subject());
        std::cout << '\n';
    }

}

int main()
{
    test_move();
    test_type_deduction();
    return 0;
}
