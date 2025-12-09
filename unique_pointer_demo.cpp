#include <iostream>
#include <memory>

// Demonstration of safe memory management using std::unique_ptr.
// No dangling pointers or manual delete needed.

int main() {
    // Create a unique_ptr to an integer
    std::unique_ptr<int> pointer1 = std::make_unique<int>(67);

    // You can access the value like a normal pointer
    std::cout << "pointer1 -> " << pointer1.get() 
              << " : value = " << *pointer1 << std::endl;

    // Move ownership to another unique_ptr
    std::unique_ptr<int> pointer2 = std::move(pointer1);

    if (!pointer1) {
        std::cout << "pointer1 is now null after move\n";
    }

    std::cout << "pointer2 -> " << pointer2.get() 
              << " : value = " << *pointer2 << std::endl;

    // Memory is automatically freed when pointer2 goes out of scope
    return 0;
}
