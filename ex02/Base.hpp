#ifndef BASE_HPP_
#define BASE_HPP_

class Base {
 public:
	virtual ~Base();
};

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

class A : public Base {};
class B : public Base {};
class C : public Base {};

#endif
