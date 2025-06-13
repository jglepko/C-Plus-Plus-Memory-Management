struct B0 { int n = 3; };
struct B1 { float f = 3.5f; };

class D : public B0, public B1 { };
#include <iostream>
int main() {
    D d;
    B0 *b0 = static_cast<B0*>(&d);
    B1 *b1 = static_cast<B1*>(&d);
    int n0 = b0->n;
    float f0 = b1->f;

    B0 *r0 = reinterpret_cast<B0*>(&d);

    std::cout << b0 << ' ' << r0 << '\n';
    B1 *r1 = reinterpret_cast<B1*>(&d);
    std::cout << b1 << ' ' << r1 << '\n';
    int nr0 = r0->n;
}