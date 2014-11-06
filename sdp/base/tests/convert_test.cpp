#include <sdp/base/convert.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace sdp;

int main(int argc, char* argv[]) {
  Convert<long> convert(200100000000128);
  
  cout<<convert.toInt()<<endl;
  cout<<convert.toString()<<endl;
  cout<<convert.toDouble()<<endl;
  cout<<convert.toLong()<<endl;
  cout<<convert.toLongLong()<<endl;
  
  return 0;
}
