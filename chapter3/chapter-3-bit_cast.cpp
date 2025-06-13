#include <bit>
struct A { int a; double b; };
struct B { unsigned int c; double d; };
int main() {
    constexpr A a{ 3, 3.5 };
    constexpr B b == std::bit_cast<B>(a);
    static_assert(a.a == b.c && a.b == b.d);
    static_assert((void*)&a != (void*)&b);
}