#include <iostream>

#include "lib/codel.h"
#include "lib/color.h"
#include "lib/image.h"

int main() {
    piet::image img = piet::read_image(".\\samples\\Piet_hello.png");

    std::cout<<"Image read_image: "<<img.get_width()<<"x"<<img.get_height()<<"\n";

//    for(int i=0;i<img.get_width();i++){
//        piet::pixel pixel = img.get_pixel(0, i);
//        piet::color pixel_color{pixel};
//        std::cout<<"[0 "<<i<<"]: "<<pixel<<" "<<pixel_color<<"\n";
//    }

    piet::codel_grid grid{img};

    return 0;
}
