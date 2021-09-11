#include <iostream>
#include <codel.h>
#include <color.h>
#include <image_read.h>

int main() {
    image::image_type img = image::read(R"(C:\Users\danie\CLionProjects\Piet\samples\Piet_hello.png)");

    std::cout<<"Image read: "<<img.get_width()<<"x"<<img.get_height()<<"\n";
    std::cout<<img.get_pixel(0, 0)<<"\n";
    return 0;
}
