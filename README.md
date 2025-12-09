# dangling-pointer-demo
Demonstration of undefined behavior in C++ using raw pointers.

# Dangling Pointer Demonstration in C++

This repository contains a simple and educational C++ program that demonstrates **dangling pointers** and **undefined behavior** when using raw dynamic memory.

The example shows how two pointers can reference the same allocated memory, and how deleting the memory through one pointer makes the other pointer invalid (dangling).

---

##  What This Program Demonstrates

- Allocation of an integer on the heap with `new`
- Copying the pointer (two pointers referencing the same memory)
- Deleting memory through one pointer
- How the second pointer becomes a **dangling pointer**
- Dereferencing a dangling pointer → **undefined behavior**

This is a fundamental concept in low-level memory management and helps explain why C++ offers modern alternatives like `std::unique_ptr`.

---

##  Source Code

```cpp
#include <iostream>

// Demonstration of dangling pointers and undefined behavior.
// This example intentionally shows what happens when two raw pointers
// point to the same memory, and the memory is deleted through one of them.

int main() {
    
    int* pointer1 = new int{67};
    int* pointer2 = pointer1;  // both pointers refer to the same integer
    
    // Basic null check (good practice before dereferencing)
    if (pointer1 != nullptr){
        std::cout << "Allocation succeeded.\n";
        std::cout << "pointer1: " << pointer1 << " -> " << *pointer1 << std::endl;
        std::cout << "pointer2: " << pointer2 << " -> " << *pointer2 << std::endl;
    }

    delete pointer1;           // free the memory
    pointer1 = nullptr;        // reset pointer1

    // pointer2 is now a dangling pointer!
    // Dereferencing pointer2 is undefined behavior.
    std::cout << "pointer2 after delete: " << pointer2 
              << " -> " << *pointer2 
              << "  (undefined behavior — for demonstration only!)" 
              << std::endl;

    return 0;
}

##How to compile and run

Using g++

g++ dangling_pointer.cpp -o dangling_pointer
./dangling_pointer

