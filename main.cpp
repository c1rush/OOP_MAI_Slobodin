#include <iostream>
#include <string>
#include "include/swap.h"

int main(){
    std::string str;
    std::cin >> str;
    
    std::cout << swap(str) << std::endl;

    return 0;
}