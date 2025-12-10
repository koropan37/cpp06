#include "Data.hpp"

Data::Data(int data) : data_(data) {}

Data::Data(const Data& other) : data_(other.data_) {}

Data& Data::operator=(const Data& other) {
	if(this != &other)
		data_ = other.data_;
	return *this;
}

Data::~Data() {}

int Data::getData(void) const { return data_; }

std::ostream &operator<<(std::ostream &os, const Data& data) {
	os << "Data: " << data.getData();
	return os;
}
