#include <iostream>
struct Base {
    ~Base() { std::cout << "~Base()\n"; }
};
struct DerivedFromBase : Base {
    ~DerivedFromBase() { std::cout << "~DerivedFromBase()\n"; }
};
struct VirtualBase {
    virtual ~VirtualBase() {
        std::cout << "~VirtualBase()\n"; 
    }
};
struct DerivedFromVirtualBase : VirtualBase {
    ~DerivedFromVirtualBase() { 
        std::cout << "~DerivedFromVirtualBase()\n"; 
    }
};
int main() {
    {
        Base base;
    }
    {
        DerivedFromBase derivedFromBase;
    }
    std::cout << "----\n";
    Base *pBase = new DerivedFromBase;
    delete pBase;
    VirtualBase *pVirtualBase = new DerivedFromVirtualBase;
    delete pVirtualBase;
}