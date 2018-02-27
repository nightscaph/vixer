#ifndef XLOG_XLOG_H
#define XLOG_XLOG_H
/**
 * @brief brief
 * @version 1.0
 * @author Night
 * @email email
 * @company company
 * @date 2018-02-27 06:18:02
 **/


class XLog
{
  class _XLogImp;
public:
  static XLog &instance();
  void log(const char *type, const char * fmt, ...);
    
private:
  explicit XLog();
  ~XLog();

  XLog(const XLog &) = delete;
  XLog(const XLog &&) = delete;
  XLog &operator =(const XLog &) = delete;
  XLog &operator =(const XLog &&) = delete;

  _XLogImp *_xlogimp;
};

#ifndef XLOG
#define XLOG XLog::instance()
#endif //XLOG

#endif // XLOG_XLOG_H
