# SKVector

Lightweight, fixed-capacity vector container for embedded C++ systems.
Provides a minimal alternative to `std::vector` without dynamic memory allocation.

---

## Features

* Static allocation (no heap usage)
* Deterministic memory footprint
* Header-only implementation
* Low overhead, suitable for MCUs
* Familiar API inspired by `std::vector`

---

## Motivation

In embedded environments, dynamic memory allocation is often avoided due to fragmentation and non-deterministic behavior.
`SKVector` offers a predictable, fixed-capacity container with a simple interface similar to `std::vector`.

---

## Basic Usage

```cpp
#include "SKVector.hpp"

SKVector<int, 10> vec;

vec.push_back(1);
vec.push_back(2);
vec.push_back(3);

for (size_t i = 0; i < vec.size(); ++i) {
    printf("%d\n", vec[i]);
}
```

---

## Template Parameters

```cpp
template<typename T, size_t Capacity>
class SKVector;
```

| Parameter  | Description                                        |
| ---------- | -------------------------------------------------- |
| `T`        | Element type                                       |
| `Capacity` | Maximum number of elements stored in the container |

---

## API Overview

### Capacity

```cpp
size_t size() const;
constexpr size_t capacity() const;
bool empty() const;
bool full() const;
```

---

### Element Access

```cpp
T& operator[](size_t index);
const T& operator[](size_t index) const;

T& at(size_t index);
const T& at(size_t index) const;

T& front();
T& back();
```

* `operator[]` does not perform bounds checking
* `at()` may include bounds checking depending on implementation

---

### Modifiers

```cpp
void push_back(const T& value);
void pop_back();

void clear();
void resize(size_t newSize);

template<typename... Args>
T& emplace_back(Args&&... args);
```

* `push_back()` adds an element at the end if capacity allows
* `pop_back()` removes the last element
* `resize()` adjusts logical size (may construct or remove elements)

---

### Iterators

```cpp
T* begin();
T* end();

const T* begin() const;
const T* end() const;
```

Supports range-based for loops:

```cpp
for (auto& v : vec) {
    // use v
}
```

---

## Behavior Notes

* The container **never reallocates memory**

* Exceeding capacity results in implementation-defined behavior:

  * assertion, or
  * ignored insertion

* `clear()` resets size but does not erase underlying memory

* Elements are stored in contiguous memory

---

## Example (Embedded Use Case)

```cpp
SKVector<uint16_t, 32> samples;

void collect() {
    if (!samples.full()) {
        samples.push_back(readAdc());
    }
}

uint16_t average() {
    uint32_t sum = 0;

    for (auto v : samples) {
        sum += v;
    }

    return samples.size() ? (sum / samples.size()) : 0;
}
```

---

## Memory Model

Internal layout:

```cpp
T m_data[Capacity];
size_t m_size;
```

* Fixed-size buffer allocated at compile time
* No heap usage
* Predictable memory consumption: `sizeof(T) * Capacity`

---

## Limitations

* Capacity is fixed at compile time
* No dynamic resizing
* No allocator support
* Behavior on overflow depends on implementation
* Not fully STL-compliant

---

## When to Use

Use `SKVector` when:

* working on microcontrollers (STM32, ESP32, AVR)
* heap allocation is restricted or disabled
* deterministic memory usage is required
* small to medium bounded datasets are sufficient

---

## When NOT to Use

Avoid when:

* container size must grow dynamically
* large or unbounded datasets are expected
* full compatibility with STL containers is required

---

## License

MIT

---

## Author

Sebastian Koczur
