#include "tests.h"
#include <color.h>

void test_trait_diffs(){
    std::cout<<"\tTesting color trait difference calcs...";
    // hue
    for(int i=0;i<hue::NUM_HUES;i++)
        for(int j=0;j<hue::NUM_HUES;j++){
            const hue::hue_type& from = hue::hue_type::get_instance(i);
            const hue::hue_type& to = hue::hue_type::get_instance(j);
            assert(to - from == (j-i+hue::NUM_HUES) % hue::NUM_HUES);
        }
    // brightness
    for(int i=0;i<brightness::NUM_BRIGHTNESS;i++)
        for(int j=0;j<brightness::NUM_BRIGHTNESS;j++){
            const brightness::brightness_type& from = brightness::brightness_type::get_instance(i);
            const brightness::brightness_type& to = brightness::brightness_type::get_instance(j);
            assert(to - from == (j-i+brightness::NUM_BRIGHTNESS) % brightness::NUM_BRIGHTNESS);
        }

    std::cout<<"Done\n";
}

void test_trait_singleton(){
    std::cout<<"\tTesting color trait singleton functionality...";

    assert(&hue::RED    == &hue::hue_type::get_instance(0));
    assert(&hue::YELLOW == &hue::hue_type::get_instance(1));
    assert(&hue::GREEN  == &hue::hue_type::get_instance(2));
    assert(&hue::CYAN   == &hue::hue_type::get_instance(3));
    assert(&hue::BLUE   == &hue::hue_type::get_instance(4));
    assert(&hue::MAGENTA == &hue::hue_type::get_instance(5));

    assert(&brightness::DARK    == &brightness::brightness_type::get_instance(0));
    assert(&brightness::NORMAL  == &brightness::brightness_type::get_instance(1));
    assert(&brightness::BRIGHT  == &brightness::brightness_type::get_instance(2));

    std::cout<<"Done\n";
}

void test_trait_comparison(){
    std::cout<<"\tTesting color trait comparison...";
    // hue
    for(int i=0;i<hue::NUM_HUES;i++)
        for(int j=0;j<hue::NUM_HUES;j++){
            const hue::hue_type& a = hue::hue_type::get_instance(i);
            const hue::hue_type& b = hue::hue_type::get_instance(j);
            assert((a == b) == (i == j));
        }
    // brightness
    for(int i=0;i<brightness::NUM_BRIGHTNESS;i++)
        for(int j=0;j<brightness::NUM_BRIGHTNESS;j++){
            const brightness::brightness_type& a = brightness::brightness_type::get_instance(i);
            const brightness::brightness_type& b = brightness::brightness_type::get_instance(j);
            assert((a == b) == (i == j));
        }

    std::cout<<"Done\n";
}

void test_color_comparison(){
    std::cout<<"\tTesting color type comparison...";

    color::color_type white(color::color_type::color_category_type::WHITE);
    color::color_type white2(color::color_type::color_category_type::WHITE);
    color::color_type black(color::color_type::color_category_type::BLACK);
    color::color_type black2(color::color_type::color_category_type::BLACK);
    color::color_type bright_red(hue::RED, brightness::BRIGHT);
    color::color_type bright_red2(hue::RED, brightness::BRIGHT);
    color::color_type dark_blue(hue::BLUE, brightness::DARK);
    assert(white == white2);
    assert(black == black2);
    assert(white != black);
    assert(white != bright_red);
    assert(black != bright_red);
    assert(white == color::color_type::color_category_type::WHITE);
    assert(black == color::color_type::color_category_type::BLACK);
    assert(bright_red == color::color_type::color_category_type::COLOR);
    assert(bright_red == bright_red2);
    assert(bright_red != dark_blue);

    std::cout<<"Done\n";
}