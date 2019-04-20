//
//  main.cpp
//  bounded_enum
//

#include <iostream>
#include "bounded_enum.hpp"

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    enum class alphabet{a,b,c,d,e,f,g,h};
    using alphabet_bt = bounded_enum<alphabet, alphabet::a, alphabet::h>;
    
    alphabet_bt abt{alphabet_bt::type::e};
    for(auto e: abt){
        std::cout << e << "\n";
    }
    
    std::cout << abt << "\n";
    
    alphabet_bt bbt{ alphabet_bt::type::d};
    alphabet_bt cbt{ abt + bbt };
    
    std::cout << abt << " + " << bbt << " = " << cbt <<"\n";
    return 0;
}
