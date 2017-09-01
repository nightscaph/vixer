#include "xlog.h"

#include <cstdarg>
#include <cstring>
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
            const time_t day_sec = 60 * 60 * 24;
            while (true) {
                char fname[32] = {0};
                const time_t time_secs = time(0);
                tm current_time = {0};
                int pos = strftime(fname, sizeof(fname), "%Y-%m-%d", localtime_r(&time_secs, &current_time));
                strcat(fname + pos, ".xlog");
                
                std::ofstream out(fname, std::ios_base::out|std::ios_base::app);
                if (out.is_open()) {
                    while (time(0) / day_sec == time_secs / day_sec) {
                        while(!_task.empty()) {
                            out << _task.front() << std::endl;
                            _task.pop_front();
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                        std::this_thread::yield();
                    }
                    out.close();
                }
            }
        });
        work.detach();
    }
    
    void _parse(const char *type, const char *fmt, va_list &argv)
    {
        char task[2048] = {0};
        const size_t size = sizeof(task);
        time_t t = time(0);
        tm current_time = {0};
        int pos = strftime(task, size, "%Y-%m-%d %H:%M:%S", localtime_r(&t, &current_time));
        pos += snprintf(task + pos, size - pos, " [%s]: ", type);
        vsnprintf(task + pos, size - pos, fmt, argv);
        
        _task.emplace_back(task);
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

void XLog::caution(const char *fmt, ...)
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
