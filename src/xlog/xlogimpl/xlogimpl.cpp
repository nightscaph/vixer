//
//  xlogimpl.cpp
//  vixer
//
//  Created by ScarCold on 2018/3/10.
//

#include <thread>
#include <fstream>
#include <memory>

#include "xlogimpl.h"
#include "iostream"

XLogImpl::XLogImpl() : _active(true)
{
}

XLogImpl::~XLogImpl()
{
  _active = false;
}

void XLogImpl::initial()
{
  std::thread work([&](){
    while (_active) {
      char fname[32] = {0};
      tm current_time = {0};
      get_current_time(current_time);
      
      int pos = strftime(fname, sizeof(fname), "%y-%m", &current_time);
      ::memmove(fname + pos, ".xlog", sizeof(".xlog"));
      
      int start_mon = current_time.tm_mon;
      std::unique_ptr<std::FILE, decltype(&std::fclose)> fp(std::fopen(fname, "a"), &std::fclose);
      if (nullptr != fp) {
        while (!is_another_mon(current_time, start_mon)) {
          while(!_task.empty()) {
            ::fputs(_task.front().data(), fp.get());
            _task.pop_front();
          }
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
      }
    }
  });
  work.detach();
}

void XLogImpl::log(const char* type, const char* fmt, va_list& argv)
{
  char task[1024] = {0};
  const size_t size = sizeof(task);
  int pos = ::snprintf(task, size, "[%s]", type);
  
  tm current_time = {0};
  get_current_time(current_time);
  pos += ::strftime(task + pos, size - pos, " %d-%H:%M:%S: ", &current_time);
  ::vsnprintf(task + pos, size - pos, fmt, argv);
  
  _task.emplace_back(task);
}



void XLogImpl::get_current_time(tm& time)
{
  time_t t = ::time(nullptr);
#ifndef _WIN32
  ::localtime_r(&t, &time);
#else
  ::localtime_s(&time, &t);
#endif //_WIN32
}

bool XLogImpl::is_another_mon(tm& time, int mon)
{
  get_current_time(time);
  return time.tm_mon != mon;
}
