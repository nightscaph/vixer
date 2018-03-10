/**
 * @brief brief
 * @version 1.0
 * @author Night
 * @email email
 * @company company
 * @date 2018-02-27 06:17:42
 **/

#include <thread>
#include <string>

#include "app.h"
#include "xlog/xlog.h"

App* App::_self = nullptr;

App::App(int argc, char** argv):_active(false), _exec_value(0)
{
  char** arg = argv;
  std::string arguments;
  if (argc != 0 && argv != nullptr) {
    while (*arg != nullptr) {
      arguments.append(*arg++);
    }
  }
  _self = this;
  XLOG.log("INFO", "Application start with: [%s]", arguments.data());
}

App::~App()
{
  _active = false;
}

App* App::instance()
{
  return App::_self;
}

int App::exec(void)
{
  _active = true;
  while (_active) {
    work();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  return _exec_value;
}

void App::quit(int val)
{
    _exec_value = val;
    _active = false;
}

void App::work()
{
  static int i = 0;
  if (++i >= 500) {
    _exec_value = 3;
    _active = false;
  }
}
