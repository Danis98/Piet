#include <iostream>
#include <codel.h>
#include <color.h>
#include <image_read.h>

int main() {
//    image::image_type img = image::read(R"(C:\Users\danie\CLionProjects\Piet\samples\Piet_hello.png)");
//
//    std::cout<<"Image read: "<<img.get_width()<<"x"<<img.get_height()<<"\n";
//    std::cout<<img.get_pixel(0, 0)<<"\n";

    std::cout<<"Setup done"<<std::endl;

    const piet::color& test_col{piet::color::color_category::BLACK};

    std::cout<<test_col<<"\n";

    piet::codel test_codel{};

    std::cout<<test_codel<<"\n"<<(test_codel == piet::NULL_CODEL)<<"\n";

    return 0;
}
