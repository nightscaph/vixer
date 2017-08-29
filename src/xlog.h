#ifndef XLOG_H
#define XLOG_H


class XLog
{
public:
    static XLog &instance();
    void info(const char *fmt, ...);
    void caution(const char *fmt, ...);
    void error(const char *fmt, ...);
    
private:
    explicit XLog();
    ~XLog();
    
    XLog(const XLog &) = delete;
    XLog(const XLog &&) = delete;
    XLog &operator =(const XLog &) = delete;
    XLog &operator =(const XLog &&) = delete;
    
    class _XLogImp;
    _XLogImp *_xlogimp;
};

#ifndef XLOG
#define XLOG XLog::instance()
#endif //XLOG

#endif // XLOG_H
