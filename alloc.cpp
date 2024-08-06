#include <iostream>
#include <vector>
// #include <memory>
#include <cassert>
#include <cstdlib>
#include <stdexcept>
#include <mutex>
#include <algorithm>

template <typename T>
class fixed_allocator {
private:
  T* _data;
  size_t _size;
  size_t _used;
  std::vector<std::pair<T*, size_t>> free_list; // track both pointer and size
  mutable std::mutex mtx; // for thread safety. Make the mutex mutable to use in const methods
public:
  fixed_allocator(size_t size);
  ~fixed_allocator();
  T* allocate(size_t n);
  void deallocate(T* ptr, size_t n);
  size_t available() const;
private:
  void merge_free_blocks();
};

template<typename T>
fixed_allocator<T>::fixed_allocator(size_t size) : _size(size), _used(0) {
  _data = static_cast<T*>(std::malloc(size * sizeof(T)));
  assert(_data != nullptr);
  // free_list.reserve(size);
}

template<typename T>
fixed_allocator<T>::~fixed_allocator() {
  std::free(_data);
}

template<typename T>
T* fixed_allocator<T>::allocate(size_t n) {
  std::lock_guard<std::mutex> lock(mtx);
  if(n == 0) return nullptr;

   if (!free_list.empty()) {
    auto& [ptr, size] = free_list.back();
    if (size >= n) {
      T* result = ptr;
      if (size > n) {
        ptr += n;
        size -= n;
      } else {
        free_list.pop_back();
      }
      return result;
    }
  }

  if (_used + n <= _size) {
    T* ptr = _data + _used;
    _used += n;
    return ptr;
  } else {
    throw std::bad_alloc();
  }
}

template<typename T>
void fixed_allocator<T>::deallocate(T* ptr, size_t n) {
  std::lock_guard<std::mutex> lock(mtx);
  if (ptr && n > 0) free_list.emplace_back(ptr, n);
  merge_free_blocks();
}

template<typename T>
size_t fixed_allocator<T>::available() const {
  std::lock_guard<std::mutex> lock(mtx);
  size_t free_size = 0;
  for (const auto& [ptr, size] : free_list) {
    free_size += size;
  }
  return _size - _used + free_size;
}

template<typename T>
void fixed_allocator<T>::merge_free_blocks() {
  // std::lock_guard<std::mutex> lock(mtx); // add if merge_free_blocks is used independently
  std::sort(free_list.begin(), free_list.end(), [](const auto& a, const auto& b) {
    return a.first < b.first;
  });

  std::vector<std::pair<T*, size_t>> merged_blocks;
  for(const auto & block : free_list) {
    if (merged_blocks.empty()) { merged_blocks.push_back(block); }
    else {
      auto& last = merged_blocks.back();
      if (last.first + last.second == block.first) {
        last.second += block.second;
      } else {
        merged_blocks.push_back(block);
      }
    }
  }
  free_list = std::move(merged_blocks);
}

int main() {
  fixed_allocator<int> allocator(100); // Preallocate memory for 100 ints

  int* p1 = allocator.allocate(10);
  int* p2 = allocator.allocate(20);

  for (int i = 0; i < 10; ++i) p1[i] = i;
  for (int i = 0; i < 20; ++i) p2[i] = i * 2;

  for (int i = 0; i < 10; ++i) std::cout << p1[i] << ' ';
  std::cout << '\n';
  for (int i = 0; i < 20; ++i) std::cout << p2[i] << ' ';
  std::cout << '\n';

  allocator.deallocate(p1, 10); // Deallocate the memory
  allocator.deallocate(p2, 20); // Deallocate the memory

  int* p3 = allocator.allocate(5); // Should reuse the memory from the free list
  for (int i = 0; i < 5; ++i) p3[i] = i + 100;
  for (int i = 0; i < 5; ++i) std::cout << p3[i] << ' ';
  std::cout << '\n';

  return 0;
}