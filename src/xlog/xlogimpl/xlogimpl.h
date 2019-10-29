//
//  xlogimpl.h
//  vixer
//
//  Created by ScarCold on 2018/3/10.
//

#ifndef xlogimpl_h
#define xlogimpl_h

#include <string>
#include <sstream>
#include <list>

class XLogImpl
{
public:
  XLogImpl();
  ~XLogImpl();
  
  void initial();
  void log(const char* type, const char* fmt, va_list& argv);
  
private:
  void get_current_time(tm& time);
  bool is_another_mon(tm& time, int mon);
  
  bool _active;
  int _loop_time_interval;    //ms
  std::list<std::string> _task;
  std::stringstream _sstream;
  std::mutex _mutex;
};

#endif /* xlogimpl_h */
