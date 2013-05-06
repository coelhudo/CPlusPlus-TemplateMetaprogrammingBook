#include <boost/type_traits.hpp>
#include <iostream>

template<class T>
struct add_const_ref
{
    typedef const T& type;
};

template<class T>
struct add_const_ref<const T&>
{
    typedef T type;
};

template<class T>
struct add_const_ref<T&>
{
    typedef T type;
};

int main()
{
    std::cout << boost::is_same<add_const_ref<int>::type, const int&>::value
              << std::endl;
    std::cout << boost::is_same<add_const_ref<const int>::type, const int&>::value
              << std::endl;
    std::cout << boost::is_same<add_const_ref<const int&>::type, int>::value
              << std::endl;
    std::cout << boost::is_same<add_const_ref<int&>::type, int>::value
              << std::endl;
    return 0;
}
