#include <boost/type_traits.hpp>
#include <assert.h>

template<class Target, class Source>
inline Target polymorphic_downcast(Source *source)
{
    assert( dynamic_cast<Target>(source) == source);
    return static_cast<Target>(source);
}

template<class Target, class Source>
inline Target polymorphic_downcast(Source &source)
{
    typedef typename boost::remove_reference<Target>::type type;
    assert( dynamic_cast<type*>(&source) == &source);
    return *static_cast<type*>(&source);
}

struct A { virtual ~A(){} };
struct B : public A {};

int main()
{
    B b;
    A *a_ptr = &b;
    B *b_ptr = polymorphic_downcast<B*>(a_ptr);

    A &a_ref = b;
    B &b_ref = polymorphic_downcast<B&>(a_ref);

    return 0;
}
