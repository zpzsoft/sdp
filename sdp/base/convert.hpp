#ifndef SDP_BASE_CONVERT_H
#define SDP_BASE_CONVERT_H

#include <iostream>
#include <sstream>

namespace sdp {

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
  int* ret = dynamic_cast<int*>(&value_);

  if (ret != NULL)
    return *ret;
  
  return 0;
}

template <typename T>  
double Convert<T>::toDouble() const {
  double* ret = dynamic_cast<double*>(&value_);

  if (ret != NULL)
    return *ret;
  
  return 0;
}

template <typename T>  
long Convert<T>::toLong() const {
  long* ret = dynamic_cast<long*>(&value_);

  if (ret != NULL)
    return *ret;
  
  return 0;
}

template <typename T>  
long long Convert<T>::toLongLong() const {
  long long* ret = dynamic_cast<long long*>(&value_);

  if (ret != NULL)
    return *ret;
  
  return 0;
}

} //end of sdp namespace
#endif //end of SDP_BASE_CONVERT_H
