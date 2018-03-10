/**
 * @brief brief
 * @version 1.0
 * @author Night
 * @email email
 * @company company
 * @date 2018-02-27 06:17:57
 **/

#include "xlog.h"
#include "xlogimpl/xlogimpl.h"

#include <cstdarg>

XLog& XLog::instance()
{
  static XLog xlog;
  return xlog;
}

XLog::XLog():_impl(new XLogImpl)
{
  _impl->initial();
}

XLog::~XLog()
{
  delete _impl;
}

void XLog::log(const char* type, const char* fmt, ...)
{
  va_list argv;
  va_start(argv, fmt);
  _impl->log(type, fmt, argv);
  va_end(argv);
}
