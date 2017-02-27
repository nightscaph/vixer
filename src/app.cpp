#include "app.h"
#include "xlog.h"

#include <thread>

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
  XLOG.info("Application start with: [%s]", arguments.data());
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
  while (_active) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  return _exec_value;
}

void App::quit(int val)
{
  _exec_value = val;
  _active = false;
}
