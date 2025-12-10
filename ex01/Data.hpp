#ifndef DATA_HPP_
#define DATA_HPP_

#include <ostream>

class Data {
 private:
	int data_;

 public:
	Data(int data = 0);
	Data(const Data& other);
	Data& operator=(const Data& other);
	~Data();

	int getData(void) const;
};

std::ostream &operator<<(std::ostream &os, const Data& data);

#endif
