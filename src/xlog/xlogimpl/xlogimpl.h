//
//  xlogimpl.h
//  vixer
//
//  Created by ScarCold on 2018/3/10.
//

#ifndef xlogimpl_h
#define xlogimpl_h

#include <string>
#include <list>

struct tm;
class XLogImpl
{
public:
  void initial();
  void log(const char *type, const char *fmt, va_list &argv);
  
private:
  void get_current_time(tm &time);
  bool is_another_mon(tm &time, int day);
  
  std::list<std::string> _task;
};

#endif /* xlogimpl_h */
