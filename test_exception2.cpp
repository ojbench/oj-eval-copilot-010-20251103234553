#include "list.hpp"
#include <iostream>

int main() {
    sjtu::list<int> myList, otherList;
    sjtu::list<int>::iterator it = myList.end();
    
    std::cout << "it is at end(), list is empty" << std::endl;
    std::cout << "Trying it--..." << std::endl;
    it--;
    std::cout << "After it--, trying to dereference..." << std::endl;
    try {
        int x = *it;
        std::cout << "  No exception, value: " << x << std::endl;
    } catch (...) {
        std::cout << "  Caught exception on dereference" << std::endl;
    }
    
    std::cout << "Trying it++..." << std::endl;
    it++;
    std::cout << "After it++, trying to dereference..." << std::endl;
    try {
        int x = *it;
        std::cout << "  No exception, value: " << x << std::endl;
    } catch (...) {
        std::cout << "  Caught exception on dereference" << std::endl;
    }
    
    return 0;
}
