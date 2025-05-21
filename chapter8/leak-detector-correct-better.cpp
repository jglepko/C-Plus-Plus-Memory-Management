#ifndef LEAK_DETECTOR_H
#define LEAK_DETECTOR_H
#include <cstddef>
#include <atomic>
#include <new>

class Accountant {
  std::atomic<long long> cur;
  Accountant() : cur{ 0LL } {
  }
public:
  Accountant(const Accountant&) = delete;
  Accountant& operator=(const Accountant&) = delete;
  static auto& get() {
    static Accountant singleton;
    return singleton;
  }

  void take(std::size_t n) { cur += n; }
  void give_back(std::size_t n) { cur -= n; }
  std::size_t how_much() const { return cur.load(); }
};

void *operator new(std::size_t); 
void *operator new[](std::size_t);
void operator delete(void*) noexcept;
void operator delete[](void*) noexcept;
#endif

// ------------------------------
// leak_detector.cpp
// ------------------------------
// #include "leak_detector.h"
#include <cstdlib>
void *operator new(std::size_t n) {
  void *p = std::malloc(n);
  if(!p) throw std::bad_alloc{};
  Accountant::get().take(n);
  return p;
}
void *operator new[](std::size_t n) {
  void *p = std::malloc(n);
  if(!p) throw std::bad_alloc{};
  Accountant::get().take(n);
  return p;
}

void operator delete(void *p, std::size_t n) noexcept {
  if(!p) return;
  Accountant::get().give_back(n);
  std::free(p);
}
void operator delete[](void *p, std::size_t n) noexcept {
  if(!p) return;
  Accountant::get().give_back(n);
  std::free(p);
}

#include <iostream>
int main() {
  auto pre = Accountant::get().how_much();
  { // BEGIN
    int *p = new int{ 3 };
    int *q = new int[10]{ };
    delete p;
  } // END
  auto post = Accountant::get().how_much();
  if(post != pre) 
    std::cout << "Leaked " << (post - pre) << " bytes\n";
}
