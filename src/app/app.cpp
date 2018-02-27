/**
 * @brief brief
 * @version 1.0
 * @author Night
 * @email email
 * @company company
 * @date 2018-02-27 06:17:42
 **/

#include "app.h"
#include "xlog/xlog.h"

#include <thread>
#include <string>

App *App::_self = nullptr;

App::App(int argc, char **argv):_active(false), _exec_value(0)
{
  char **arg = argv;
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
}

App *App::instance()
{
  return App::_self;
}

int App::exec(void)
{
  _active = true;
  int i = 0;
  while (_active) {
    if (i == 100) {
      XLOG.log("ERR", "current step: %d", i);
      i = 0;
    }
    ++i;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  return _exec_value;
}

void App::quit(int val)
{
    _exec_value = val;
    _active = false;
}
