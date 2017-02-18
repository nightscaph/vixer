#ifndef XLOG_H
#define XLOG_H

#include <list>
#include <string>

class XLog
{
  enum class Type:unsigned char {
    INFO = 1,
    WARNING,
    ERROR
  };
public:
  static XLog &instance();
  void info(const char *fmt, ...);
  void warn(const char *fmt, ...);
  void error(const char *fmt, ...);

protected:
  explicit XLog();
  ~XLog();
  XLog(const XLog&) = delete;
  XLog &operator =(const XLog&) = delete;

  void push(Type type, const char *fmt, va_list argv);

private:
  std::list<std::string> _task;
};

#ifndef XLOG
#define XLOG XLog::instance()
#endif //XLOG

#endif // XLOG_H
