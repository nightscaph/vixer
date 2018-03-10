/**
 * @brief brief
 * @version 1.0
 * @author Night
 * @email email
 * @company company
 * @date 2018-02-27 06:18:07
 **/

#include "app/app.h"
#include <iostream>

int main(int argc, char **argv)
{
  std::set_unexpected([]{
    std::cerr << "Exit(code 1) with unspecified exception" << std::endl;
    exit(1);
  });
    
  try {
    App app(argc, argv);
    return app.exec();
  } catch (...) {
    std::unexpected();
  }
}
