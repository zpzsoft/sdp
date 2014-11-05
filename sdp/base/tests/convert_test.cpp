#include <sdp/base/convert.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace sdp;

int main(int argc, char* argv[])
{
  Convert<int> convert(100);
  cout<<convert.toString()<<endl;
  
  return 0;
}
