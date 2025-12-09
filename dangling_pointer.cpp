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

---

## License

MIT License — free for anyone to use, modify, and share.
