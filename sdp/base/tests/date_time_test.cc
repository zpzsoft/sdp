#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include <sdp/base/date_time.h>

using namespace std;

int main(void) {
  time_t seconds = time((time_t*)NULL);
  struct timeval tv;
  struct timezone tz;

  int ret = gettimeofday(&tv, &tz);

  sdp::DateTime time;

  std::cout<<time.toString()<<std::endl;
  cout<<"day of week:"<<time.get_day_of_week()<<endl;
  cout<<"day of year:"<<time.get_day_of_year()<<endl;
  cout<<"time zone is:"<<time.get_time_zone()<<endl;
  
  sdp::DateTime time1;

  cout<<time1 - time<<endl;

  time1 = time;

  cout<<time1 - time<<endl;
  cout<<time1.toString()<<endl;
  
  return 1;
}
