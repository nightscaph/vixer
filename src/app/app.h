#ifndef APP_H
#define APP_H

class App
{
public:
    explicit App(int argc, char **argv);
    static App *instance();
    
    int exec(void);
    void quit(int = 0);
    
    ~App();
    App(const App &) = delete;
    App(const App &&) = delete;
    App &operator =(const App &) = delete;
    App &operator =(const App &&) = delete;
private:
    bool _active;
    int _exec_value;
    
    static App *_self;
};

#endif // APP_H
