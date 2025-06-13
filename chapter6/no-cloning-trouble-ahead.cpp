struct X { int n; }
struct B {
    int n;
    B(int n) : n{ n } {}
    virtual ~B() = default;
};
struct D0 : B {
    D0(int n) : B{ n } { }
};
struct D1 : B {
    D1(int n) : B{ n } { }
};
// precondition: p != nullptr (to keep things simple)
X* duplicate(X *p) {
    return new X{ *p };
}
// precondition: p != nullptr (to keep things simple)
B* duplicate(B *p) {
    return new B{ *p }; // Bad idea!
}

#include <memory>
int main() {
    using std::unique_ptr;
    X x{ 3 };
    unique_ptr<X> px { duplicate(&x) };
    D0 d0{ 4 };
    unique_ptr<B> pb{ duplicate(&d0) };
}