#include <iostream>
#include <codel.h>
#include <color.h>

int main() {
    codel::codel_type codel{{1, 2}, {hue::RED, brightness::BRIGHT}};
    std::cout<<codel<<"\n";
    return 0;
}
