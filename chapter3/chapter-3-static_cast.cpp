struct B { virtual ~B() = default; };
struct D0 : B { };
struct D1 : B { };
class X {
public:
    X(int, double) {}
};
void f(D0&){}
void f(D1*){}
int main() {
    const float x = 3.14159f;
    int n = static_cast<int>(x);
    X x0{ 3, 3.5 };
    X x1(3.5, 0);
    X x3{ static_cast<int>(x), 3 };
    D0 d0;

    B *b = static_cast<B*>(&d0);

    f(*static_cast<D0*>(b));
    f(*static_cast<D1*>(b));
}