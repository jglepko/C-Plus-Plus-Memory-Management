struct Circle {
    explicit Circle([[maybe_unused]] float radius) {

    }
};

void f(Circle) { }
int main() {
    f(Circle{ 1.0f });
    f(static_cast<Circle>(1.0f));
}