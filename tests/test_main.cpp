#include <iostream>
#include "tests.h"

int main(){
    std::cout<<"Testing color lib\n";

    std::cout<<"COLOR TRAIT TESTS\n";
    std::cout<<"--------------------\n";
    test_trait_diffs();
    test_trait_singleton();
    test_trait_comparison();
    std::cout<<"COLOR TYPE TESTS\n";
    std::cout<<"--------------------\n";
    test_color_comparison();

    std::cout<<"Tests passed\n";
}
