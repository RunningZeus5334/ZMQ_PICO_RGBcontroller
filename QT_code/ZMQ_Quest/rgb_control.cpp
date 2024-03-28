#include "rgb_control.h"
#include <iostream>
RGB_Control::RGB_Control() {}


void RGB_Control::change_red(){
    std::cout << "Red led is on" << std::endl;
}

void RGB_Control::change_green(){
    std::cout << "Green led is on" << std::endl;
}

void RGB_Control::change_blue(){
    std::cout << "Blue led is on" << std::endl;
}
