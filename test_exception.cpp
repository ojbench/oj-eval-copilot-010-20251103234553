#include "list.hpp"
#include <iostream>

int main() {
    sjtu::list<int> myList, otherList;
    int ans = 0;

    std::cout << "Testing pop_back on empty list..." << std::endl;
    try{ myList.pop_back(); } catch (...) { ans++; std::cout << "  Caught exception" << std::endl; }
    
    std::cout << "Testing pop_front on empty list..." << std::endl;
    try{ myList.pop_front(); } catch (...) { ans++; std::cout << "  Caught exception" << std::endl; }
    
    std::cout << "Testing front on empty list..." << std::endl;
    try{ myList.front(); } catch (...) { ans++; std::cout << "  Caught exception" << std::endl; }
    
    std::cout << "Testing back on empty list..." << std::endl;
    try{ myList.back(); } catch (...) { ans++; std::cout << "  Caught exception" << std::endl; }
    
    sjtu::list<int>::iterator it = myList.end(), oit = otherList.end();
    
    std::cout << "Testing *it on end()..." << std::endl;
    try{ *it; } catch (...) { ans++; std::cout << "  Caught exception" << std::endl; }
    
    std::cout << "Testing it-- on end()..." << std::endl;
    try{ it--; } catch (...) { ans++; std::cout << "  Caught exception" << std::endl; }
    
    std::cout << "Testing it++ on end() (or result of it--)..." << std::endl;
    try{ it++; } catch (...) { ans++; std::cout << "  Caught exception" << std::endl; }
    
    std::cout << "Testing erase(it)..." << std::endl;
    try{ myList.erase(it); } catch (...) { ans++; std::cout << "  Caught exception" << std::endl; }
    
    std::cout << "Testing insert with wrong container iterator..." << std::endl;
    try{ myList.insert(oit, 0); } catch (...) { ans++; std::cout << "  Caught exception" << std::endl; }
    
    std::cout << "Total exceptions caught: " << ans << std::endl;
    std::cout << "Expected: 9" << std::endl;
    
    return 0;
}
