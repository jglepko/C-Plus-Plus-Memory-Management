#include <iostream>
#include <cstdlib>
#include <new>

void* operator new(std::size_t n, const std::notthrow_t&) noexcept {
    return std::malloc(n);
}
void* operator new(std::size_t n) {
    auto p = operator new(n, std::nothrow);
    if(!p) throw std::bad_alloc{};
    return p;
}
void operator delete(void* p, const std::nothrow_t&) noexcept {
    std::free(p);
}
void operator delete(void* p) noexcept {
    operator delete(p, std::nothrow);
}
void operator delete(void* p, std::size_t) noexcept {
    operator delete(p, std::nothrow);
}
void* operator new[](std::size_t n, const std::nothrow_t&) noexcept {
    return std::malloc(n);
}
void* operator new[](std::size_t n) {
    auto p = operator new[](n, std::nothrow);
    if(!p) throw std::bad_alloc{};
    return p;
}
void operator delete[](void* p, const std::nothrow_t&) noexcept {
    std::free(p);
}
void operator delete[](void* p) noexcept {
    operator delete[](p, std::nothrow);
}
void operator delete[](void* p, std::size_t) noexcept {
    operator delete[](p, std::nothrow);
}

int main() {
    using std::nothrow;
    auto p = new (nothrow) int{ 3 };
    delete p;
    p = new (nothrow) int[10];
    delete[]p;
}