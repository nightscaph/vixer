#include "app/app.h"
#include <iostream>

int main(int argc, char **argv)
{
    std::set_unexpected([]{
        std::cerr << "unexpected called\n";
        exit(1);
    });
    
    try {
        App app(argc, argv);
        return app.exec();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
