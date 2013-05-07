#include <boost/type_traits.hpp>
#include <iostream>

template<class X, bool value>
struct replace
{
};

template<class X>
struct replace<X, false>
{
};

template<class X>
struct replace<X, true>
{
    typedef X type;
};

template<class C, class X, class Y>
struct replace_type
{
};

template<class C, int N, class X, class Y>
struct replace_type<C*[N], X, Y>
{
    typedef typename replace<Y, boost::is_same<C,X>::value>::type* type[N];
};

template<class C, class X, class Y>
struct replace_type<C& (*) (C&), X, Y>
{
private:
    typedef typename replace<Y, boost::is_same<C,X>::value>::type replaced_type;
public:
    typedef replaced_type& (*type) (replaced_type&);
};

template<class C, class X, class Y>
struct replace_type<C& (*) (C&,C&), X, Y>
{
private:
    typedef typename replace<Y, boost::is_same<C,X>::value>::type replaced_type;
public:
    typedef replaced_type& (*type) (replaced_type&, replaced_type&);
};

template<class C, class N, class X, class Y>
struct replace_type<C& (*) (N&,C&), X, Y>
{
private:
    typedef typename replace<Y, boost::is_same<C,X>::value>::type replaced_type;
public:
    typedef replaced_type& (*type) (N&, replaced_type&);
};

template<class C, class N, class X, class Y>
struct replace_type<C& (*) (N&,N&), X, Y>
{
private:
    typedef typename replace<Y, boost::is_same<C,X>::value>::type replaced_type;
public:
    typedef replaced_type& (*type) (N&, N&);
};

//... etc

int main()
{
    std::cout << boost::is_same<replace_type<int const*[10], int const, long>::type, long*[10]>::value << std::endl;

    //It will not compile since boost::is_same will evaluate to false
    //std::cout << boost::is_same<replace_type<int const*[10], char const, long>::type, long*[10]>::value << std::endl;

    std::cout << boost::is_same<replace_type<char& (*) (char&), char, long>::type, long& (*) (long&)>::value << std::endl;
    std::cout << boost::is_same<replace_type<char& (*) (char&,char&), char, long>::type, long& (*) (long&,long&)>::value << std::endl;
    std::cout << boost::is_same<replace_type<char& (*) (int&,char&), char, long>::type, long& (*) (int&,long&)>::value << std::endl;

    return 0;
}
