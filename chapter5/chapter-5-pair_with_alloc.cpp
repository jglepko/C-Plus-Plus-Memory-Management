#include <memory>
template <class T>
    class pair_with_alloc {
        std::unique_ptr<T> p0, p1;
    public:
        pair_with_alloc(const T &val0, const T &val1)
            : p0{ std::make_unique<T>(val0) },
              p1{ std::make_unique<T>(val1) } {
        }
    };

#include <string>
#include <random>
#include <iostream>
class risky {
    std::mt19937 prng{ std::random_device{}() };
    std::uniform_int_distribution<int> penny { 0,1 };
public:
    risky() = default;
    risky(const risky &) {
        if(penny(prng)) throw 3;
    }
    ~risky() {
        std::cout << "~risky()\n";
    }
};

int main() {
    if(std::string s0, s1; std::cin >> s0 >> s1) 
        try {
            pair_with_alloc a{ s0, s1 };
            pair_with_alloc b{ risky{}, risky{} };
        } catch(...) {
            std::cerr << "Something was thrown...\n";
        }
}