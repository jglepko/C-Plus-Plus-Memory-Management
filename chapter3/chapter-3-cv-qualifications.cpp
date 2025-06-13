const int N = 3;

class X {
    int n;
public:
    X(int n) : n{ n } {
    }
    int g() {
        return n += N;
    }
    int f() const {
        return n + 1;
    }
};

int f(const int &n) {
    return X{ n }.f() + 1;
}

int main() {
    int a = 4;
    a = f(a);
}