#include "Base.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

//#include <typeinfo>

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
	std::srand(std::time(0)); //rand()を初期化する。これがないと乱数が同じになりやすい
	printColor("Identify from Pointer", CYAN);
	{
		Base* a = new A;
		Base* b = new B;
		Base* c = new C;
		identify(a);
		identify(b);
		identify(c);
		delete a;
		delete b;
		delete c;
		Base* p = NULL;
		identify(p);
		std::cout << std::endl;
	}
	printColor("Identify from Reference", GREEN);
	{
		A a;
		B b;
		C c;
		Base base;
		identify(a);
		identify(b);
		identify(c);
		identify(base);
		std::cout << std::endl;
	}
	{
		Base* a = new A;
		Base* b = new B;
		Base* c = new C;
		identify(*a);
		identify(*b);
		identify(*c);
		delete a;
		delete b;
		delete c;
		std::cout << std::endl;
	}
	printColor("Generator", MAGENTA);
	{
		for (int i = 0; i < 5; ++i) {
			Base* p = generate();
			identify(p);
			delete p;
		}
		std::cout << std::endl;
	}

	// printColor("dynamic_cast tests", B_CYAN);
    // {
    //     Base* p = new A;
    //     std::cout << "dynamic_cast<B*>(A*) -> "
    //               << (dynamic_cast<B*>(p) ? "succeeded" : "failed (nullptr)") << std::endl;
    //     try {
    //         (void)dynamic_cast<A&>(*p);
    //         std::cout << "dynamic_cast<A&>(*p) -> succeeded" << std::endl;
    //     } catch (const std::bad_cast&) {
    //         std::cout << "dynamic_cast<A&>(*p) -> bad_cast" << std::endl;
    //     }
    //     try {
    //         (void)dynamic_cast<B&>(*p);
    //         std::cout << "dynamic_cast<B&>(*p) -> succeeded" << std::endl;
    //     } catch (const std::bad_cast&) {
    //         std::cout << "dynamic_cast<B&>(*p) -> bad_cast (as expected)" << std::endl;
    //     }
    //     delete p;
    // }
}
