#ifndef SDP_BASE_CONVERT_H
#define SDP_BASE_CONVERT_H

#include <iostream>
#include <sstream>
#include <typeinfo>

namespace sdp {

//only support integral type and string.
template <typename T>
class Convert {
public:
  Convert(T& value);

  Convert(T value):value_(value) {}

  ~Convert();

  std::string toString() const;

  int toInt() const;

  double toDouble() const;

  long toLong() const;

  long long toLongLong() const;

  void printType();

private:
  Convert(){}

private:
  T value_;
};

//implement of template class can't be separate from it's definition.
template <typename T>
Convert<T>::Convert(T& value)
  :value_(value) {

}

template <typename T>  
Convert<T>::~Convert() {

}

template <typename T>
std::string Convert<T>::toString() const {
  std::stringstream stream;
  stream<<value_;
  
  return stream.str();
}

template <typename T>  
int Convert<T>::toInt() const {
  return static_cast<int>(value_);
}

template <typename T>  
double Convert<T>::toDouble() const {
  return static_cast<double>(value_);
}

template <typename T>  
long Convert<T>::toLong() const {
  return static_cast<long>(value_);
}

template <typename T>  
long long Convert<T>::toLongLong() const {
  return static_cast<long long>(value_);
}

template <typename T>
void Convert<T>::printType() {
  std::cout<<typeid(value_).name()<<std::endl;
}
  
} //end of sdp namespace
#endif //end of SDP_BASE_CONVERT_H
