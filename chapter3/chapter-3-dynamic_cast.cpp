struct B0 {
    virtual int f() const = 0;
    virtual ~B0() = default;
};
struct B1 {
    virtual int g() const = 0;
    virtual ~B1() = default;
}
class D0 : public B0 {
    public: int g() const override { return 4; }
};
class D : public D0, public D1 {};
int f(D *p) {
    return p ? p->f() + p->g() : -1; // Ok
}

int g(D0 &d0) {
    D1 &d1 = dynamic_cast<D1&>(d0);
    return d1.g();
}

#include <iostream>
int main() {
    D d;
    f(&d);
    g(d);
    D0 d0;
    std::cout << f(dynamic_cast<D*>(&d0)) << '\n'; // -1
    try {
        g(d0); // compiles but will throw bad_cast
    } catch(std::bad_cast&) {
        std::cerr << "Nice try\n";
    }
}