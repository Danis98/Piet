#include "color.h"
#include "image.h"

piet::color piet::color::BLACK{piet::color::color_category::BLACK};
piet::color piet::color::WHITE{piet::color::color_category::WHITE};

const piet::color::color_category piet::color::get_color_category(uint32_t hex){
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
        case 0xC000C0:  return color::color_category::COLOR;
        case 0xFFFFFF:  return color::color_category::WHITE;
        case 0x000000:
        default:        return color::color_category::BLACK;
    }
}

const piet::hue::hue_trait& piet::color::get_color_hue(uint32_t hex){
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

const piet::brightness::brightness_trait& piet::color::get_color_brightness(uint32_t hex){
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
