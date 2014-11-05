#include <sdp/base/date_time.hpp>

#include <stdio.h>
#include <string.h>

#if defined(__linux) || defined(__APPLE__)
#include <sys/time.h>
#endif

namespace sdp {
  
DateTime::DateTime() :
  from1970_01_01_(0),
  time_zone_(0),
  day_of_week_(0),
  day_of_year_(0){
  year_month_day_.year = 1970;
  year_month_day_.month = 1;
  year_month_day_.day = 0;
  hour_minute_seconds_.hour = 0;
  hour_minute_seconds_.minute = 0;
  hour_minute_seconds_.seconds = 0;
  hour_minute_seconds_.useconds = 0;

  refresh();
}

DateTime::~DateTime() {

}

long long DateTime::refresh() {
#if defined(__linux) || defined(__APPLE__)
  struct timeval tv;
  struct timezone tz;
  long last_seconds = from1970_01_01_,
    last_useconds = hour_minute_seconds_.useconds;
  
  int ret = gettimeofday(&tv, &tz);
  if (ret == 0) {
    time_t time = tv.tv_sec;
    struct tm* date_time;
    date_time = localtime(&time);

    year_month_day_.year = date_time->tm_year + 1900;
    year_month_day_.month = date_time->tm_mon + 1;
    year_month_day_.day = date_time->tm_mday;
    hour_minute_seconds_.hour = date_time->tm_hour;
    hour_minute_seconds_.minute = date_time->tm_min;
    hour_minute_seconds_.seconds = date_time->tm_sec;
    hour_minute_seconds_.useconds = tv.tv_usec;

    from1970_01_01_ = time;
    time_zone_ = tz.tz_dsttime;
    day_of_week_ = date_time->tm_wday;
    day_of_year_ = date_time->tm_yday;
  } else {
    //get time faild,default 0.
    year_month_day_.year = 1970;
    year_month_day_.month = 1;
    year_month_day_.day = 0;
    hour_minute_seconds_.hour = 0;
    hour_minute_seconds_.minute = 0;
    hour_minute_seconds_.seconds = 0;
    hour_minute_seconds_.useconds = 0;
    
    from1970_01_01_ = 0;
    time_zone_ = 0;
    day_of_week_ = 0;
    day_of_year_ = 0;
  }
#endif

  long dif = (from1970_01_01_ - last_seconds)*1000000 +
    hour_minute_seconds_.useconds - last_useconds;

  return dif;
}

std::string DateTime::toString() const{
  char time_buf[64] = {0};

  sprintf(time_buf, "%4d-%02d-%02d %02d:%02d:%02d",
          year_month_day_.year,
          year_month_day_.month,
          year_month_day_.day,
          hour_minute_seconds_.hour,
          hour_minute_seconds_.minute,
          hour_minute_seconds_.seconds);
  return time_buf;
}

bool DateTime::isValid() const {
  return this->from1970_01_01_ >= 0;
}
  
long long DateTime::operator- (const DateTime& dt) {
  return (this->get_from1970_01_01() - dt.get_from1970_01_01())*1000 +
    this->useconds() - dt.useconds();
}

void DateTime::operator= (const DateTime& dt) {
  memcpy((void*)this, (void*)&dt, sizeof dt);
}
  
bool DateTime::operator== (const DateTime& dt) const {
  if (this->get_from1970_01_01() == dt.get_from1970_01_01()
      && this->useconds() == dt.useconds()
      && this->get_time_zone() == dt.get_time_zone())
    return true;

  return false;
}
}






  
