#include "Base.hpp"
#include <iostream>
#include <cstdlib>

Base::~Base() {}

Base* generate(void) {
	try {
		switch (rand() % 3)
		{
		case 0:
		    std::cout << "A generated" << std::endl;
			return new A;
		case 1:
		    std::cout << "B generated" << std::endl;
			return new B;
		case 2:
		    std::cout << "C generated" << std::endl;
			return new C;
		default:
			return NULL;
		}
	} catch (std::bad_alloc()) {
		return NULL;
	}
}

void identify(Base* p) {
  if (dynamic_cast<A*>(p)) {
    std::cout << "A" << std::endl;
  } else if (dynamic_cast<B*>(p)) {
    std::cout << "B" << std::endl;
  } else if (dynamic_cast<C*>(p)) {
    std::cout << "C" << std::endl;
  } else {
    std::cout << "Nothing" << std::endl;
  }
}

void identify(Base& p) {
	try {
		(void)dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
		return ;
	} catch (std::exception& e) {}
	try {
		(void)dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
		return ;
	} catch (std::exception& e) {}
	try {
		(void)dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
		return ;
	} catch (std::exception& e) {}
	std::cout << "Nothing" << std::endl;
}

// dynamic_cast... 動的(実行時)に行う
// クラスにおいて、安全な up/ down/ side の型変換に使う
// 失敗したとき、pointer版はNULL, 参照版は例外(bad_cast)
// クラスにVTable(仮想関数)がある必要がある = Polymorphic objects
