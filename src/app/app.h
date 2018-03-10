#ifndef APP_APP_H
#define APP_APP_H
/**
 * @brief brief
 * @version 1.0
 * @author Night
 * @email email
 * @company company
 * @date 2018-02-27 06:17:50
 **/

class App
{
public:
  explicit App(int argc, char** argv);
  static App* instance();

  int exec(void);
  void quit(int = 0);

  ~App();
  App(const App&) = delete;
  App(const App&&) = delete;
  App& operator =(const App&) = delete;
  App& operator =(const App&&) = delete;
private:
  void work();
  
  bool _active;
  int _exec_value;

  static App* _self;
};

#endif // APP_APP_H
