//
//  xlogimpl.cpp
//  vixer
//
//  Created by ScarCold on 2018/3/10.
//

#include <thread>
#include <fstream>
#ifndef _WIN32
#include <sys/time.h>
#else //_WIN32
#endif //_WIN32

#include "xlogimpl.h"

void XLogImpl::initial()
{
  std::thread work([&](){
    while (true) {
      char fname[32] = {0};
      tm current_time = {0};
      
      get_current_time(current_time);
      int pos = strftime(fname, sizeof(fname), "%y-%m", &current_time);
      strcat(fname + pos, ".xlog");
      
      int start_mon = current_time.tm_mon;
      
      std::ofstream out(fname, std::ios_base::out|std::ios_base::app);
      if (out.is_open()) {
        while (!is_another_mon(current_time, start_mon)) {
          while(!_task.empty()) {
#ifndef _WIN32
            out << _task.front() << std::endl;
#else //_WIN32
            out << _task.front().data() << std::endl;
#endif //_WIN32
            _task.pop_front();
          }
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
      }
      out.close();
    }
  });
  work.detach();
}

void XLogImpl::log(const char *type, const char *fmt, va_list &argv)
{
  char task[1024] = {0};
  const size_t size = sizeof(task);
  tm current_time = {0};
  get_current_time(current_time);
  
  int pos = snprintf(task, size, "[%s]", type);
  pos += strftime(task + pos, size - pos, " %d-%H:%M:%S: ", &current_time);
  vsnprintf(task + pos, size - pos, fmt, argv);
  
  _task.emplace_back(task);
}



void XLogImpl::get_current_time(tm &time)
{
  time_t t = ::time(nullptr);
#ifndef _WIN32
  localtime_r(&t, &time);
#else
  localtime_s(&time, &t);
#endif //_WIN32
}

bool XLogImpl::is_another_mon(tm &time, int mon)
{
  get_current_time(time);
  return time.tm_mon != mon;
}
