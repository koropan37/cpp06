#ifndef SERIALIZER_HPP_
#define SERIALIZER_HPP_

#include <inttypes.h>
#include "Data.hpp"

class Serializer {
 private:
	Serializer();
	Serializer(const Serializer& other);
	Serializer& operator=(Serializer const &other);
	~Serializer();

 public:
	static uintptr_t serialize(Data* ptr);
	 static Data* deserialize(uintptr_t raw);

};

#endif
