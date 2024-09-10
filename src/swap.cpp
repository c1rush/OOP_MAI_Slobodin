#include "../include/swap.h"

std::string swap(std::string str){
    for(int i = 0; i < str.length(); ++i){
        if (str[i] == 'a') {
            str[i] = 'b';
        } else if (str[i] == 'b') {
            str[i] = 'a';
        }
    }
    return str;
}