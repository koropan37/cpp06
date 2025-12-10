#include "Serializer.hpp"

uintptr_t Serializer::serialize(Data* ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
  return reinterpret_cast<Data*>(raw);
}

// 使用用途(危険なため、奥の手の変換) ... コンパイル時に行う
// 1.ポインタのアドレス値を整数型の変数に格納
// 2.double * から int * など違う型のポインタの変換
