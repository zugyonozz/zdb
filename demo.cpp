#include <iostream>
#include <cassert>
#include "zdb.h"

using namespace zdb;

void demo_node_operations() {
    std::cout << "=== Demo Node Operations ===" << std::endl;
    
    // Test Node with integers
    impl::Node<0, int> intNode;
    std::cout << "Initial node size: " << intNode.size() << std::endl;
    
    // Push some values
    intNode.push(10).push(20).push(30);
    std::cout << "After pushing 10, 20, 30 - size: " << intNode.size() << std::endl;
    
    // Access elements
    std::cout << "Elements: ";
    for (unsigned i = 0; i < intNode.size(); i++) {
        std::cout << intNode[i] << " ";
    }
    std::cout << std::endl;
    
    // Test iterator
    std::cout << "Using iterators: ";
    for (auto it = intNode.begin(); it != intNode.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test erase
    intNode.erase(1); // Remove element at index 1 (value 20)
    std::cout << "After erasing index 1: ";
    for (unsigned i = 0; i < intNode.size(); i++) {
        std::cout << intNode[i] << " ";
    }
    std::cout << std::endl;
    
    // Test pop
    intNode.pop();
    std::cout << "After pop: ";
    for (unsigned i = 0; i < intNode.size(); i++) {
        std::cout << intNode[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << std::endl;
}

void demo_varchar_operations() {
    std::cout << "=== Demo Varchar Operations ===" << std::endl;
    
    // Test varchar
    varchar<20> str1("Hello");
    varchar<20> str2("World");
    
    std::cout << "str1: " << str1 << " (length: " << str1.len() << ")" << std::endl;
    std::cout << "str2: " << str2 << " (length: " << str2.len() << ")" << std::endl;
    
    // Test assignment
    str1 = "ZDB Library";
    std::cout << "After assignment str1: " << str1 << std::endl;
    
    // Test character access
    std::cout << "First character of str1: " << str1[0] << std::endl;
    
    // Test comparison
    if (str1 == "ZDB Library") {
        std::cout << "String comparison works!" << std::endl;
    }
    
    std::cout << std::endl;
}

void demo_date_operations() {
    std::cout << "=== Demo Date Operations ===" << std::endl;
    
	// Create date using constructor
	Date d1(15, 8, 2024);
	std::cout << "Date d1: " << static_cast<std::string>(d1) << std::endl;
	std::cout << "Day: " << static_cast<int>(d1.getDD()) << std::endl;
	std::cout << "Month: " << static_cast<int>(d1.getMM()) << std::endl;
	std::cout << "Year: " << d1.getYY() << std::endl;
	
	// Create date from string (DDMMYYYY format)
	varchar<8> dateStr("25122023");
	Date d2(dateStr);
	std::cout << "Date d2 from string: " << static_cast<std::string>(d2) << std::endl;
	
	// Test setters
	d1.setDD(25).setMM(12).setYY(2023);
	std::cout << "After setting d1: " << static_cast<std::string>(d1) << std::endl;
        
    
    std::cout << std::endl;
}

void demo_tuple_operations() {
    std::cout << "=== Demo Tuple Operations ===" << std::endl;
    
    // Create a tuple with different types
    Tuple<int, varchar<10>, float> tuple1(42, varchar<10>("test"), 3.14f);
    
    std::cout << "Tuple created with values: 42, 'test', 3.14" << std::endl;
    
    // Access tuple elements
    std::cout << "Element 0 (int): " << tuple1.get<0, 0>() << std::endl;
    std::cout << "Element 1 (varchar): " << tuple1.get<1, 0>() << std::endl;
    std::cout << "Element 2 (float): " << tuple1.get<2, 0>() << std::endl;
    
    // Test modification
    tuple1.get<0, 0>() = 100;
    std::cout << "After modifying element 0: " << tuple1.get<0, 0>() << std::endl;
    
    std::cout << std::endl;
}

// void demo_error_handling() {
//     std::cout << "=== Demo Error Handling ===" << std::endl;
    
//     try {
//         // Test out of range access
//         impl::Node<0, int> node;
//         node.push(10);
//         std::cout << "Trying to access index 5 in node with 1 element..." << std::endl;
//         int val = node[5]; // This should throw
//         std::cout << "Value: " << val << std::endl; // Won't reach here
//     } catch (const auto& e) {
//         std::cout << "Caught exception: " << e() << std::endl;
//     }
    
//     try {
//         // Test invalid date
//         std::cout << "Trying to create invalid date (32/13/2024)..." << std::endl;
//         date invalidDate(32, 13, 2024); // This should throw
//     } catch (const auto& e) {
//         std::cout << "Caught exception: " << e() << std::endl;
//     }
    
//     try {
//         // Test varchar out of range
//         varchar<5> shortStr("hello");
//         std::cout << "Trying to access index 10 in varchar<5>..." << std::endl;
//         char c = shortStr[10]; // This should throw
//         std::cout << "Character: " << c << std::endl; // Won't reach here
//     } catch (const auto& e) {
//         std::cout << "Caught exception: " << e() << std::endl;
//     }
    
//     std::cout << std::endl;
// }

void demo_node_memory_management() {
    std::cout << "=== Demo Node Memory Management ===" << std::endl;
    
    impl::Node<0, int> node;
    
    std::cout << "Initial capacity: " << node.cap() << std::endl;
    
    // Add elements to trigger capacity growth
    for (int i = 1; i <= 10; i++) {
        node.push(i * 10);
        std::cout << "After push " << i << ": size=" << node.size() 
                  << ", capacity=" << node.cap() << std::endl;
    }
    
    // Test reserve
    node.reserve(20);
    std::cout << "After reserve(20): capacity=" << node.cap() << std::endl;
    
    // Test shrink_to_fit
    node.shrink_to_fit();
    std::cout << "After shrink_to_fit: size=" << node.size() 
              << ", capacity=" << node.cap() << std::endl;
    
    std::cout << std::endl;
}

void demo_copy_and_move() {
    std::cout << "=== Demo Copy and Move Operations ===" << std::endl;
    
    // Test copy constructor
    impl::Node<0, int> original;
    original.push(1).push(2).push(3);
    
    impl::Node<0, int> copied(original);
    std::cout << "Original size: " << original.size() << std::endl;
    std::cout << "Copied size: " << copied.size() << std::endl;
    
    // Test move constructor
    impl::Node<0, int> moved(std::move(original));
    std::cout << "After move - Original size: " << original.size() << std::endl;
    std::cout << "After move - Moved size: " << moved.size() << std::endl;
    
    // Test assignment
    impl::Node<0, int> assigned;
    assigned = copied;
    std::cout << "Assigned size: " << assigned.size() << std::endl;
    
    std::cout << std::endl;
}

int main() {
    std::cout << "ZDB Library Demo" << std::endl;
    std::cout << "================" << std::endl << std::endl;
    
    demo_node_operations();
    demo_varchar_operations();
    demo_date_operations();
    demo_tuple_operations();
    // demo_error_handling();
    demo_node_memory_management();
    demo_copy_and_move();
    
    std::cout << "Demo completed successfully!" << std::endl;
    return 0;
}