#include "xlog.h"

#include <cstdarg>
#include <thread>
#include <sys/time.h>
#include <fstream>

XLog &XLog::instance()
{
  static XLog xlog;
  return xlog;
}

void XLog::info(const char *fmt, ...)
{
  va_list argv;
  va_start(argv, fmt);
  va_end(argv);
  push(Type::INFO, fmt, argv);
}

void XLog::warn(const char *fmt, ...)
{
  va_list argv;
  va_start(argv, fmt);
  va_end(argv);
  push(Type::WARNING, fmt, argv);
}

void XLog::error(const char *fmt, ...)
{
  va_list argv;
  va_start(argv, fmt);
  va_end(argv);
  push(Type::ERROR, fmt, argv);
}

void XLog::push(Type type, const char *fmt, va_list argv)
{
  char date[32] = {0};
  time_t t = time(0);
  strftime(date, sizeof(date), "%H:%M:%S", localtime(&t));

  char data[1024] = {0};
  vsprintf(data, fmt, argv);

  std::string task(date);  
  switch (type) {
    case Type::INFO:{
      task.append("[INFO]:");
      break;
    }
    case Type::WARNING:{
      task.append("[WARNING]:");
      break;
    }
    case Type::ERROR:{
      task.append("[ERROR]:");
      break;
    }
    default:{
      return;
    }
  }
  task.append(data);

  _task.emplace_back(std::move(task));
}

XLog::XLog()
{
  std::thread work([&](){
    char date[32] = {0};
    time_t t = time(0);
    strftime(date, sizeof(date), "%Y-%m-%d", localtime(&t));
    std::string fname(date);
    fname.append(".xlog");

    std::ofstream out;
    out.open(fname.c_str(), std::ios_base::out|std::ios_base::app);
    if (out.is_open()) {
      while (true) {
        while(!_task.empty()) {
          out << _task.front() << std::endl;
          _task.pop_front();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
      out.close();
    }
  });
  work.detach();
}

XLog::~XLog()
{
}


