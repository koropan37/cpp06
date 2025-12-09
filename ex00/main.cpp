#include "ScalarConverter.hpp"
#include <iostream>
#include <stdexcept>

int main (int argc, char *argv[]) {
    try {
        if(argc!= 2) 
            throw std::invalid_argument("Usage: ./Convert <...>");
        ScalarConverter::convert(static_cast<std::string>(argv[1]));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
      }
    return 0;
}
