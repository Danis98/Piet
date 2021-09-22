#include <color.h>
#include <image.h>


constexpr char piet::hue::STR_RED[] = "RED";
constexpr char piet::hue::STR_YELLOW[] = "YELLOW";
constexpr char piet::hue::STR_GREEN[] = "GREEN";
constexpr char piet::hue::STR_CYAN[] = "CYAN";
constexpr char piet::hue::STR_BLUE[] = "BLUE";
constexpr char piet::hue::STR_MAGENTA[] = "MAGENTA";

constexpr char piet::brightness::STR_DARK[] = "DARK";
constexpr char piet::brightness::STR_NORMAL[] = "NORMAL";
constexpr char piet::brightness::STR_BRIGHT[] = "BRIGHT";

piet::color piet::color::BLACK{piet::color::color_category::BLACK};
piet::color piet::color::WHITE{piet::color::color_category::WHITE};

piet::color::color_category piet::color::get_color_category(uint32_t hex){
    switch(hex){
        case 0xFFC0C0:
        case 0xFF0000:
        case 0xC00000:
        case 0xFFFFC0:
        case 0xFFFF00:
        case 0xC0C000:
        case 0xC0FFC0:
        case 0x00FF00:
        case 0x00C000:
        case 0xC0FFFF:
        case 0x00FFFF:
        case 0x00C0C0:
        case 0xC0C0FF:
        case 0x0000FF:
        case 0x0000C0:
        case 0xFFC0FF:
        case 0xFF00FF:
        case 0xC000C0:  return piet::color::color_category::COLOR;
        case 0xFFFFFF:  return piet::color::color_category::WHITE;
        case 0x000000:
        default:        return piet::color::color_category::BLACK;
    }
}

piet::hue::hue_ptr piet::color::get_color_hue(uint32_t hex){
    switch(hex){
        case 0xFFC0C0:
        case 0xFF0000:
        case 0xC00000:  return hue::RED;
        case 0xFFFFC0:
        case 0xFFFF00:
        case 0xC0C000:  return hue::YELLOW;
        case 0xC0FFC0:
        case 0x00FF00:
        case 0x00C000:  return hue::GREEN;
        case 0xC0FFFF:
        case 0x00FFFF:
        case 0x00C0C0:  return hue::CYAN;
        case 0xC0C0FF:
        case 0x0000FF:
        case 0x0000C0:  return hue::BLUE;
        case 0xFFC0FF:
        case 0xFF00FF:
        case 0xC000C0:
        default:        return hue::MAGENTA;
    }
}

piet::brightness::brightness_ptr piet::color::get_color_brightness(uint32_t hex){
    switch(hex){
        case 0xFFC0C0:
        case 0xFFFFC0:
        case 0xC0FFC0:
        case 0xC0FFFF:
        case 0xC0C0FF:
        case 0xFFC0FF:  return brightness::BRIGHT;
        case 0xFF0000:
        case 0xFFFF00:
        case 0x00FF00:
        case 0x00FFFF:
        case 0x0000FF:
        case 0xFF00FF:  return brightness::NORMAL;
        case 0xC00000:
        case 0xC0C000:
        case 0x00C000:
        case 0x00C0C0:
        case 0x0000C0:
        case 0xC000C0:
        default:        return brightness::DARK;
    }
}