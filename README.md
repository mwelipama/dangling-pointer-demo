# Dangling Pointer Demonstration in Modern C++

> **Executive Summary:**  
> This repository demonstrates **memory safety pitfalls** in C++ using raw pointers and contrasts them with **modern smart pointer approaches** (`std::unique_ptr`).  
> It is designed to highlight **ownership, lifetime, and undefined behavior**, core concepts every professional C++ engineer must understand.

---

## Motivation

Manual memory management with `new` and `delete` can lead to:

- Dangling pointers  
- Undefined behavior  
- Memory leaks  
- Hard-to-debug runtime errors  

Modern C++ uses **RAII (Resource Acquisition Is Initialization)** and **smart pointers** to eliminate these problems.  
Understanding these issues is critical for writing **robust, secure, and maintainable C++ code**.

**References:**  
- [cppreference: unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr)  
- [Undefined Behavior in C++](https://en.cppreference.com/w/cpp/language/ub)

---

## What This Project Demonstrates

| Concept                        | Raw Pointer                | std::unique_ptr         |
|--------------------------------|----------------------------|-------------------------|
| Ownership                      | Ambiguous                  | Exclusive               |
| Automatic Cleanup              | No                         | Yes (RAII)              |
| Dangling Pointer Risk          | High                       | None                    |
| Copy Semantics                 | Shallow copy               | Move-only               |
| Safety                         | Low                        | High                    |

---

## Memory Layout Illustration

**Raw Pointer Example**  
```
pointer1 ---> [ 67 ]
pointer2 -----^ (both point to same memory)

After delete(pointer1):
pointer1 -> nullptr
pointer2 ---> X (dangling)
```

**Unique Pointer Example**  
```
pointer1 ---> [ 67 ] (owns)
std::move(pointer1) ---> pointer2
pointer1 -> nullptr
pointer2 ---> [ 67 ] (owns, auto cleanup)
```

---

## Build Instructions

Compile and run with g++ (C++17):

```bash
# Raw pointer example with warnings
g++ -std=c++17 -Wall -Wextra -Wpedantic raw_pointer_demo.cpp -o raw_demo
./raw_demo

# Smart pointer example
g++ -std=c++17 -Wall -Wextra -Wpedantic unique_ptr_demo.cpp -o unique_demo
./unique_demo

# With AddressSanitizer for runtime memory checks
g++ -std=c++17 -fsanitize=address -g raw_pointer_demo.cpp -o raw_demo_asan
./raw_demo_asan
```

---

## Expected Output

### Raw Pointer Example
```
pointer1: 0x55... -> 67
pointer2: 0x55... -> 67
pointer2 after delete: 0x55... -> 0 (or garbage, or crash)
```

### Smart Pointer Example
```
pointer1 -> 0x55... : value = 67
pointer1 is null after move
pointer2 -> 0x55... : value = 67
```

---

## Source Code

### 1. Raw Pointer Example (Dangling Pointer)
```cpp
#include <iostream>

int main() {
    int* pointer1 = new int{67};
    int* pointer2 = pointer1;  // two pointers to same memory

    std::cout << "pointer1: " << pointer1 << " -> " << *pointer1 << "\n";
    std::cout << "pointer2: " << pointer2 << " -> " << *pointer2 << "\n";

    delete pointer1;
    pointer1 = nullptr;

    // pointer2 now points to freed memory
    std::cout << "pointer2 after delete: " << pointer2
              << " -> " << *pointer2
              << " (undefined behavior — demo only!)\n";

    return 0;
}
```

### 2. Safe Pointer Example (`std::unique_ptr`)
```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> pointer1 = std::make_unique<int>(67);

    std::cout << "pointer1 -> " << pointer1.get()
              << " : value = " << *pointer1 << "\n";

    std::unique_ptr<int> pointer2 = std::move(pointer1);

    if (!pointer1) {
        std::cout << "pointer1 is null after move\n";
    }

    std::cout << "pointer2 -> " << pointer2.get()
              << " : value = " << *pointer2 << "\n";

    return 0;
}
```

---

## Troubleshooting

- If the program doesn't crash when dereferencing the dangling pointer:  
  - Some compilers may not immediately reuse memory  
  - The value may appear unchanged or 0  
  - This is **still undefined behavior**  

---

## Recommended Tools

- **AddressSanitizer** (`-fsanitize=address`)  
- **Valgrind** (`valgrind ./raw_demo`)  
- **Static Analyzers**: Clang-Tidy, Cppcheck  
- **Compiler Warnings**: Always use `-Wall -Wextra -Wpedantic`  

---

## GitHub Actions Example (Optional CI)

```yaml
name: C++ CI

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v3
    - name: Install g++
      run: sudo apt-get install g++-12
    - name: Build raw pointer example
      run: g++ -std=c++17 -Wall -Wextra -Wpedantic raw_pointer_demo.cpp -o raw_demo
    - name: Run raw pointer example
      run: ./raw_demo
    - name: Build unique_ptr example
      run: g++ -std=c++17 -Wall -Wextra -Wpedantic unique_ptr_demo.cpp -o unique_demo
    - name: Run unique_ptr example
      run: ./unique_demo
```

---

## Key Takeaways

- Raw pointers require careful manual management  
- Dangling pointers cause undefined behavior and potential security issues  
- `std::unique_ptr` enforces exclusive ownership and automatic cleanup  
- Modern C++ practices reduce bugs, improve maintainability, and increase safety  

---

## License

MIT License — free to use, modify, and share.
