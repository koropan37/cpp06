#include "Data.hpp"
#include "Serializer.hpp"
#include <iostream>


#define BLACK   "\033[0;30m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"
#define WHITE   "\033[0;37m"
#define RESET   "\033[0m"
#define B_RED	"\033[1;31m"
#define B_GREEN "\033[1;32m"
#define B_CYAN  "\033[1;36m"

void printColor(std::string const& str, std::string const& color) {
    std::cout
	<< RESET << "======="
	<< color << str
	<< RESET << "=======" << color << std::endl;
}

int main(void) {
	printColor("Reinterpret_cast", CYAN);
	{
		Data data(42);
		std::cout << "data: " << data << std::endl;
		std::cout << "data ptr: " << &data << std::endl;
		std::cout << std::endl;

		uintptr_t serial = Serializer::serialize(&data);
		std::cout << "address(pointer) to integer(uintptr_t)" << std::endl;
		std::cout << "serial: " << serial << std::endl;
		std::cout << std::endl;

		Data *deserial = Serializer::deserialize(serial);
		std::cout << "integer(uintptr_t) tp address(pointer)" << std::endl;
		std::cout << "deserial ptr: " << deserial << std::endl;
		std::cout << "deserial data: " << *deserial << std::endl;
		std::cout << std::endl;

	}
  	{
		Data data(-10);
		std::cout << "data: " << data << std::endl;
		std::cout << "data ptr: " << &data << std::endl;
		std::cout << std::endl;

		uintptr_t serial = Serializer::serialize(&data);
		std::cout << "address(pointer) to integer(uintptr_t)" << std::endl;
		std::cout << "serial: " << serial << std::endl;
		std::cout << std::endl;

		Data *deserial = Serializer::deserialize(serial);
		std::cout << "integer(uintptr_t) tp address(pointer)" << std::endl;
		std::cout << "deserial ptr: " << deserial << std::endl;
		std::cout << "deserial data: " << *deserial << std::endl;
		std::cout << std::endl;
  	}

}
