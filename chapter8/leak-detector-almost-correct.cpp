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

#include <cstdlib>
void *operator new(std::size_t n) {
  void *p = std::malloc(n + sizeof n);
  if(!p) throw std::bad_alloc{};
  auto q = static_cast<std::size_t*>(p)
  *p = n;
  Accountant::get().take(n);
  return q + 1;
}
void *operator new[](std::size_t n) {
  void *p = std::malloc(n + sizeof n);
  if(!p) throw std::bad_alloc{};
  auto q = static_cast<std::size_t*>(p)
  *p = n;
  Accountant::get().take(n);
  return q + 1;
}

void operator delete(void *p) noexcept {
  if(!p) return;
  auto q = static_cast<std::size_t*>(p) - 1;
  Accountant::get().give_back(*q);
  std::free(q);
}
void operator delete[](void *p) noexcept {
  if(!p) return;
  auto q = static_cast<std::size_t*>(p) - 1;
  Accountant::get().give_back(*q);
  std::free(q);
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
