#include <iostream>
class Darn {};
struct Evil {
    Evil() {
        std::cout << "Evil::Evil()\n";
    }
    ~Evil() {
        std::cout << "Evil::~Evil()\n";
        throw Darn {};
    }
};
int main() {
    try {
        Evil e;
    } catch(Darn) {
        std::cerr << "darn...\n";
    }
}