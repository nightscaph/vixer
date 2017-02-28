#include "xlog.h"

#include <cstdarg>
#include <thread>
#include <sys/time.h>
#include <fstream>
#include <list>

class XLog::_XLogImp
{
public:
  explicit _XLogImp()
  {
    std::thread work([&](){
      char fname[32] = {0};
      time_t t = time(0);
      int pos = strftime(fname, sizeof(fname), "%Y-%m-%d", localtime(&t));
      strcat(fname + pos, ".xlog");

      std::ofstream out(fname, std::ios_base::out|std::ios_base::app);
      if (out.is_open()) {
        while (true) {
          while(!_task.empty()) {
            out << _task.front() << std::endl;
            _task.pop_front();
          }
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        out.close();
      }
    });
    work.detach();
  }

  void _parse(const char *type, const char *fmt, va_list &argv)
  {
    do {
      char task[2048] = {0};
      const size_t size = sizeof(task);
      time_t t = time(0);
      int pos = strftime(task, size, "%H:%M:%S", localtime(&t));
      pos += snprintf(task + pos, size - pos, " [%s]: ", type);
      vsnprintf(task + pos, size - pos, fmt, argv);

      _task.emplace_back(task);
    } while (false);
  }
private:
    std::list<std::string> _task;
};


/******** class XLog **********/

XLog &XLog::instance()
{
  static XLog xlog;
  return xlog;
}

XLog::XLog():_xlogimp(new _XLogImp)
{
}

XLog::~XLog()
{
  if (_xlogimp != nullptr) {
    delete _xlogimp;
    _xlogimp = nullptr;
  }
}

void XLog::info(const char *fmt, ...)
{
  va_list argv;
  va_start(argv, fmt);
  _xlogimp->_parse("INFO", fmt, argv);
  va_end(argv);
}

void XLog::warn(const char *fmt, ...)
{
  va_list argv;
  va_start(argv, fmt);
  _xlogimp->_parse("CAUTION", fmt, argv);
  va_end(argv);
}

void XLog::error(const char *fmt, ...)
{
  va_list argv;
  va_start(argv, fmt);
  _xlogimp->_parse("ERROR", fmt, argv);
  va_end(argv);
}
