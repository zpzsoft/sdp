#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include <sdp/base/date_time.hpp>

using namespace std;

int main(void) {
  sdp::DateTime time;

  for (int i = 0;i < 20;i++) {
    sleep(1);
    cout<<"sleep cost :"<<time.refresh()/1000000.0<<" s"<<endl;
  }

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
