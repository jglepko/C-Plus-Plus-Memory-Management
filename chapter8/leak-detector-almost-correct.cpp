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
