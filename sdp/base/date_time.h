#ifndef SDP_BASE_DATETIME_H
#define SDP_BASE_DATETIME_H

#include <iostream>

#include <sdp/base/error_code.h>

namespace sdp {
  
class DateTime {
public:
  DateTime();

  ~DateTime();
  
  inline int year() const { return year_month_day_.year;}

  inline int month() const { return year_month_day_.month;}

  inline int day() const { return year_month_day_.day;}

  inline int hour() const { return hour_minute_seconds_.hour;}
  
  inline int minute() const { return hour_minute_seconds_.minute;}

  inline int seconds() const { return hour_minute_seconds_.seconds;}

  inline int useconds() const { return hour_minute_seconds_.useconds;}

  inline int get_day_of_week() const { return day_of_week_;}

  inline int get_day_of_year() const { return day_of_year_;}

  inline int get_time_zone() const { return time_zone_;}

  inline long get_from1970_01_01() const { return from1970_01_01_;}

  //in microseconds (1/1000000 s).
  long long refresh(void);

  std::string toString() const;

  bool isValid() const;

  //difference between times in microseconds.
  long long operator- (const DateTime& time);

  void operator= (const DateTime& time);

  bool operator== (const DateTime& time) const;
  
public:
  struct YearMonthDay {
    int year;
    int month;
    int day;
  };
  
  struct HourMinuteSeconds {
    int hour;
    int minute;
    int seconds;
    int useconds;
  };
  
private:
  struct YearMonthDay year_month_day_;
  
  struct HourMinuteSeconds hour_minute_seconds_;

  long from1970_01_01_;//The number of seconds from 1970-01-01 00:00:00

  int day_of_week_;//The number of days since Sunday,[0,6]

  int day_of_year_;//The number of days since January 1,[0, 365]

  int time_zone_;//Type of DST correction
};  
}
#endif
